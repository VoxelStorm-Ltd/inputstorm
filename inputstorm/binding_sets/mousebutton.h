#ifndef INPUTSTORM_BINDING_SETS_MOUSEBUTTON_H_INCLUDED
#define INPUTSTORM_BINDING_SETS_MOUSEBUTTON_H_INCLUDED

#include "base.h"

namespace inputstorm {
namespace binding_sets {

#define BINDING_SET_TYPE boost::bimap<boost::bimaps::unordered_multiset_of<T>, boost::bimaps::unordered_multiset_of<input::mousebutton::binding>>
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, mousebutton>

template<typename T>
class mousebutton : public BASE_TYPE {
  using controltype = T;

public:
  mousebutton(manager &input_manager, binding_manager<controltype> &parent_binding_manager);
  ~mousebutton();

  // bind and unbind controls to inputs
  virtual void unbind(std::string const &binding_name, controltype control) override final;
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type

  void bind(std::string const &binding_name,
            controltype control,
            input::mousebutton::buttontype this_button,
            input::key::modtype mods = input::key::modtype::NONE);
  void bind(controltype control,
            input::mousebutton::buttontype this_button,
            input::key::modtype mods = input::key::modtype::NONE);
  void bind(std::string const &binding_name,
            controltype control,
            input::mousebutton::binding const &binding);
  void bind(controltype control,
            input::mousebutton::binding const &binding);

  // update control-based bindings
  void update(std::string const &binding_name,
              input::mousebutton::binding const &binding);
  void update(input::mousebutton::binding const &binding);

  virtual void update_all(controltype control) override final;
};

template<typename T>
mousebutton<T>::mousebutton(manager &input_manager,
                            binding_manager<controltype> &parent_binding_manager)
  : BASE_TYPE(input_manager, parent_binding_manager) {
  /// Default constructor
}

template<typename T>
mousebutton<T>::~mousebutton() {
  /// Default destructor
}

//////////////////// bind and unbind controls to inputs ////////////////////////

template<typename T>
void mousebutton<T>::unbind(std::string const &binding_name, controltype control) {
  /// Erase a control binding from an input mousebutton relationship
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Unbinding mousebutton for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto &binding_set(this->binding_sets[binding_name]);
  auto const &binding_range(binding_set.left.equal_range(control));
  auto const binding_range_copy(binding_range);                                 // copy the binding range to update after

  binding_set.left.erase(control);                                              // clear the current associations with that control

  for(auto const &it : boost::make_iterator_range(binding_range_copy.first, binding_range_copy.second)) {
    update(it.second);                                                          // update each button that was affected by the change
  }
}

template<typename T>
void mousebutton<T>::bind(std::string const &binding_name,
                          controltype control,
                          input::mousebutton::buttontype this_button,
                          input::key::modtype mods) {
  /// Apply a new control binding to an input mousebutton relationship
  auto &binding_set(this->binding_sets[binding_name]);
  #ifdef DEBUG_INPUTSTORM
    std::stringstream ss;
    ss << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
                                                << " in set " << binding_name
                                                << ", mousebutton " << this_button
                                                << " (" << this->input.mousebutton.get_name(this_button) << ")";
  #endif // DEBUG_INPUTSTORM
  if(mods == input::key::modtype::NONE) {
    input::mousebutton::binding const binding{
      input::mousebutton::binding::bindtype::ANY_MOD,
      this_button,
      input::key::modtype::NONE
    };
    binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, binding));
    update(binding);
  } else {
    input::mousebutton::binding const binding{
      input::mousebutton::binding::bindtype::SPECIFIC,
      this_button,
      mods
    };
    binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, binding));
    update(binding);
    #ifdef DEBUG_INPUTSTORM
      ss << " mods " << input::key::get_mod_name(mods);
    #endif // DEBUG_INPUTSTORM
  }
  #ifdef DEBUG_INPUTSTORM
    std::cout << ss.str() << std::endl;
  #endif // DEBUG_INPUTSTORM
}
template<typename T>
void mousebutton<T>::bind(controltype control,
                          input::mousebutton::buttontype this_button,
                          input::key::modtype mods) {
  /// Wrapper to work on the selected control set
  bind(this->binding_selected_name, control, this_button, mods);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void mousebutton<T>::update(std::string const &binding_name,
                            input::mousebutton::binding const &binding) {
  /// Update all digital bindings for a specific mouse button
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating binding in set " << binding_name
                                                               << " for mousebutton " << binding.button
                                                               << " (" << this->input.mousebutton.get_name(binding.button) << ")" << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto const &binding_set(this->binding_sets.at(binding_name));
  auto const &control_range(binding_set.right.equal_range(binding));            // find all controls (and hence functions) that apply to this key
  std::vector<controltype> conts;                                               // generate a vector of controls
  for(auto const &this_control : boost::make_iterator_range(control_range.first, control_range.second)) {
    conts.emplace_back(this_control.second);                                    // store a list of all controls that use this key
  }
  std::sort(conts.begin(), conts.end());                                        // sort and unique the controls
  auto const &conts_new_end(std::unique(conts.begin(), conts.end()));           // this should be faster to do once than to use a set to insert
  conts.resize(std::distance(conts.begin(), conts_new_end));
  std::vector<std::function<void()>> funcs_press;                               // generate a vector of functions for when it's pressed
  std::vector<std::function<void()>> funcs_release;                             // generate a vector of functions for when it's released
  for(auto const &this_control : conts) {
    auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
    if(this_func.press) {
      funcs_press.emplace_back(this_func.press);
    }
    if(this_func.release) {
      funcs_release.emplace_back(this_func.release);
    }
  }
  std::function<void()> func_press_combined;
  if(funcs_press.empty()) {                                                     // don't bind if there's nothing to bind
    func_press_combined = nullptr;
  } else {
    if(funcs_press.size() == 1) {                                               // there's only one function, so bind it directly
      func_press_combined = funcs_press[0];
    } else {
      #ifdef DEBUG_INPUTSTORM
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for mousebutton press" << std::endl;
      #endif // DEBUG_INPUTSTORM
      func_press_combined = [funcs_press]{                                      // there are multiple functions, so create a function to iterate and call them all
        for(auto const &this_func : funcs_press) {
          this_func();
        }
      };
    }
  }
  std::function<void()> func_release_combined;
  if(funcs_release.empty()) {                                                   // don't bind if there's nothing to bind
    func_release_combined = nullptr;
  } else {
    if(funcs_release.size() == 1) {                                             // there's only one function, so bind it directly
      func_release_combined = funcs_release[0];
    } else {
      #ifdef DEBUG_INPUTSTORM
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for mousebutton release" << std::endl;
      #endif // DEBUG_INPUTSTORM
      func_release_combined = [funcs_release]{                                  // there are multiple functions, so create a function to iterate and call them all
        for(auto const &this_func : funcs_release) {
          this_func();
        }
      };
    }
  }
  if(func_press_combined || func_release_combined) {
    this->input.mousebutton.bind(binding, func_press_combined, func_release_combined);
  } else {
    this->input.mousebutton.unbind(binding);
  }
}
template<typename T>
void mousebutton<T>::update(input::mousebutton::binding const &binding) {
  /// Update all digital bindings for a specific mouse button
  update(this->binding_selected_name, binding);
}

template<typename T>
void mousebutton<T>::update_all(controltype control) {
  /// Update mouse button bindings for this control
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating all mousebutton bindings for control " << static_cast<unsigned int>(control) << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto const &binding_set(this->get_selected_binding_set());
  auto const &binding_range(binding_set.left.equal_range(control));
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
    update(it.second);
  }
}

#undef BINDING_SET_TYPE
#undef BASE_TYPE

}
}

#endif // INPUTSTORM_BINDING_SETS_MOUSEBUTTON_H_INCLUDED
