  auto const &binding_range(binding_set.left.equal_range(control));
  auto const binding_range_copy(binding_range);                                 // copy the binding range to update after

  binding_set.left.erase(control);                                              // clear the current associations with that control

  for(auto const &it : boost::make_iterator_range(binding_range_copy.first, binding_range_copy.second)) {
    update(it.second);                                                          // update each button that was affected by the change
  }
}

template<typename T>
void mousebutton<T>::bind(std::string const &binding_name,
#ifndef INPUTSTORM_BINDING_SETS_MOUSEBUTTON_H_INCLUDED
                          controltype control,
#define INPUTSTORM_BINDING_SETS_MOUSEBUTTON_H_INCLUDED
                          input::mousebutton::buttontype this_button,

                          input::key::modtype mods) {
#include "base.h"
  /// Apply a new control binding to an input mousebutton relationship
#include "inputstorm/input/mousebutton.h"

  auto &binding_set(this->binding_sets[binding_name]);
namespace inputstorm {
  #ifdef DEBUG_INPUTSTORM
namespace binding_sets {
    std::stringstream ss;

    ss << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
#define BINDING_SET_TYPE boost::bimap<boost::bimaps::unordered_multiset_of<T>, boost::bimaps::unordered_multiset_of<input::mousebutton::binding>>
                                                << " in set " << binding_name
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, mousebutton>
                                                << ", mousebutton " << this_button

                                                << " (" << parent_mousebutton.get_name(this_button) << ")";
template<typename T>
  #endif // DEBUG_INPUTSTORM
class mousebutton : public BASE_TYPE {
  if(mods == input::key::modtype::NONE) {
  using controltype = T;
    input::mousebutton::binding const binding{

      input::mousebutton::binding::bindtype::ANY_MOD,
  input::mousebutton &parent_mousebutton;
      this_button,

      input::key::modtype::NONE
public:
    };
  mousebutton(binding_manager<controltype> &parent_binding_manager,
    binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, binding));
              input::mousebutton &this_parent_mousebutton);
    update(binding);
  ~mousebutton();

  } else {
  // bind and unbind controls to inputs
    input::mousebutton::binding const binding{
  virtual void unbind(std::string const &binding_name, controltype control) override final;
      input::mousebutton::binding::bindtype::SPECIFIC,
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type
      this_button,

      mods
  void bind(std::string const &binding_name,
    };
            controltype control,
    binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, binding));
            input::mousebutton::buttontype this_button,
    update(binding);
            input::key::modtype mods = input::key::modtype::NONE);
    #ifdef DEBUG_INPUTSTORM
  void bind(controltype control,
      ss << " mods " << input::key::get_mod_name(mods);
            input::mousebutton::buttontype this_button,
    #endif // DEBUG_INPUTSTORM
            input::key::modtype mods = input::key::modtype::NONE);
  }
  void bind(std::string const &binding_name,
  #ifdef DEBUG_INPUTSTORM
            controltype control,
    std::cout << ss.str() << std::endl;
            input::mousebutton::binding const &binding);
  #endif // DEBUG_INPUTSTORM
  void bind(controltype control,
}
            input::mousebutton::binding const &binding);
template<typename T>

void mousebutton<T>::bind(controltype control,
  // update control-based bindings
  void update(std::string const &binding_name,
                          input::mousebutton::buttontype this_button,
              input::mousebutton::binding const &binding);
                          input::key::modtype mods) {
  void update(input::mousebutton::binding const &binding);
  /// Wrapper to work on the selected control set

  bind(this->binding_selected_name, control, this_button, mods);
  virtual void update_all(controltype control) override final;
}
};


///////////////////// update control-based bindings ////////////////////////////
template<typename T>

mousebutton<T>::mousebutton(binding_manager<controltype> &parent_binding_manager,
template<typename T>
                            input::mousebutton &this_parent_mousebutton)
void mousebutton<T>::update(std::string const &binding_name,
  : BASE_TYPE(parent_binding_manager),
                            input::mousebutton::binding const &binding) {
    parent_mousebutton(this_parent_mousebutton) {
  /// Update all digital bindings for a specific mouse button
  /// Default constructor
  #ifdef DEBUG_INPUTSTORM
}

    std::cout << "InputStorm: DEBUG: Updating binding in set " << binding_name
template<typename T>
                                                               << " for mousebutton " << binding.button
mousebutton<T>::~mousebutton() {
                                                               << " (" << parent_mousebutton.get_name(binding.button) << ")" << std::endl;
  /// Default destructor
  #endif // DEBUG_INPUTSTORM
}
  auto const &binding_set(this->binding_sets.at(binding_name));

  auto const &control_range(binding_set.right.equal_range(binding));            // find all controls (and hence functions) that apply to this key
//////////////////// bind and unbind controls to inputs ////////////////////////
  std::vector<controltype> conts;                                               // generate a vector of controls

template<typename T>
  for(auto const &this_control : boost::make_iterator_range(control_range.first, control_range.second)) {
void mousebutton<T>::unbind(std::string const &binding_name, controltype control) {
    conts.emplace_back(this_control.second);                                    // store a list of all controls that use this key
  /// Erase a control binding from an input mousebutton relationship
  }
  #ifdef DEBUG_INPUTSTORM
  std::sort(conts.begin(), conts.end());                                        // sort and unique the controls
    std::cout << "InputStorm: DEBUG: Unbinding mousebutton for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
  auto const &conts_new_end(std::unique(conts.begin(), conts.end()));           // this should be faster to do once than to use a set to insert
  #endif // DEBUG_INPUTSTORM
  conts.resize(std::distance(conts.begin(), conts_new_end));
  auto &binding_set(this->binding_sets[binding_name]);
  std::vector<std::function<void()>> funcs_press;                               // generate a vector of functions for when it's pressed
  auto const &binding_range(binding_set.left.equal_range(control));
  std::vector<std::function<void()>> funcs_release;                             // generate a vector of functions for when it's released
  auto const binding_range_copy(binding_range);                                 // copy the binding range to update after
  for(auto const &this_control : conts) {

    auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
  binding_set.left.erase(control);                                              // clear the current associations with that control
    if(this_func.press) {

      funcs_press.emplace_back(this_func.press);
  for(auto const &it : boost::make_iterator_range(binding_range_copy.first, binding_range_copy.second)) {
    }
    update(it.second);                                                          // update each button that was affected by the change
    if(this_func.release) {
  }
      funcs_release.emplace_back(this_func.release);
}
    }

  }
template<typename T>
  std::function<void()> func_press_combined;
void mousebutton<T>::bind(std::string const &binding_name,
                          controltype control,
  if(funcs_press.empty()) {                                                     // don't bind if there's nothing to bind
                          input::mousebutton::buttontype this_button,
    func_press_combined = nullptr;
                          input::key::modtype mods) {
  } else {
  /// Apply a new control binding to an input mousebutton relationship
    if(funcs_press.size() == 1) {                                               // there's only one function, so bind it directly
  auto &binding_set(this->binding_sets[binding_name]);
      func_press_combined = funcs_press[0];
  #ifdef DEBUG_INPUTSTORM
    } else {
    std::stringstream ss;
      #ifdef DEBUG_INPUTSTORM
    ss << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for mousebutton press" << std::endl;
                                                << " in set " << binding_name
      #endif // DEBUG_INPUTSTORM
                                                << ", mousebutton " << this_button
      func_press_combined = [funcs_press]{                                      // there are multiple functions, so create a function to iterate and call them all
                                                << " (" << parent_mousebutton.get_name(this_button) << ")";
        for(auto const &this_func : funcs_press) {
  #endif // DEBUG_INPUTSTORM
          this_func();
  if(mods == input::key::modtype::NONE) {
        }
    input::mousebutton::binding const binding{
      };
      input::mousebutton::binding::bindtype::ANY_MOD,
    }
      this_button,
  }
      input::key::modtype::NONE
  std::function<void()> func_release_combined;
    };
  if(funcs_release.empty()) {                                                   // don't bind if there's nothing to bind
    binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, binding));
    func_release_combined = nullptr;
    update(binding);
  } else {
  } else {
    input::mousebutton::binding const binding{
    if(funcs_release.size() == 1) {                                             // there's only one function, so bind it directly
      input::mousebutton::binding::bindtype::SPECIFIC,
      func_release_combined = funcs_release[0];
      this_button,
    } else {
      mods
      #ifdef DEBUG_INPUTSTORM
    };
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for mousebutton release" << std::endl;
    binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, binding));
      #endif // DEBUG_INPUTSTORM
    update(binding);
      func_release_combined = [funcs_release]{                                  // there are multiple functions, so create a function to iterate and call them all
    #ifdef DEBUG_INPUTSTORM
        for(auto const &this_func : funcs_release) {
      ss << " mods " << input::key::get_mod_name(mods);
          this_func();
    #endif // DEBUG_INPUTSTORM
        }
  }
      };
  #ifdef DEBUG_INPUTSTORM
    }
    std::cout << ss.str() << std::endl;
  }
  #endif // DEBUG_INPUTSTORM
}
  if(func_press_combined || func_release_combined) {
template<typename T>
    parent_mousebutton.bind(binding, func_press_combined, func_release_combined);
void mousebutton<T>::bind(controltype control,
  } else {
                          input::mousebutton::buttontype this_button,
    parent_mousebutton.unbind(binding);
                          input::key::modtype mods) {
  }
  /// Wrapper to work on the selected control set
}
  bind(this->binding_selected_name, control, this_button, mods);
template<typename T>
}
void mousebutton<T>::update(input::mousebutton::binding const &binding) {

  /// Update all digital bindings for a specific mouse button
///////////////////// update control-based bindings ////////////////////////////
  update(this->binding_selected_name, binding);

}
template<typename T>

void mousebutton<T>::update(std::string const &binding_name,
template<typename T>
                            input::mousebutton::binding const &binding) {
void mousebutton<T>::update_all(controltype control) {
  /// Update all digital bindings for a specific mouse button
  /// Update mouse button bindings for this control
  #ifdef DEBUG_INPUTSTORM
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating binding in set " << binding_name
    std::cout << "InputStorm: DEBUG: Updating all mousebutton bindings for control " << static_cast<unsigned int>(control) << std::endl;
                                                               << " for mousebutton " << binding.button
  #endif // DEBUG_INPUTSTORM
                                                               << " (" << parent_mousebutton.get_name(binding.button) << ")" << std::endl;
  auto const &binding_set(this->get_selected_binding_set());
  #endif // DEBUG_INPUTSTORM
  auto const &binding_range(binding_set.left.equal_range(control));
  auto const &binding_set(this->binding_sets.at(binding_name));
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
  auto const &control_range(binding_set.right.equal_range(binding));            // find all controls (and hence functions) that apply to this key
    update(it.second);
  std::vector<controltype> conts;                                               // generate a vector of controls
  }
  for(auto const &this_control : boost::make_iterator_range(control_range.first, control_range.second)) {
}
    conts.emplace_back(this_control.second);                                    // store a list of all controls that use this key

  }
#undef BINDING_SET_TYPE
  std::sort(conts.begin(), conts.end());                                        // sort and unique the controls
#undef BASE_TYPE
  auto const &conts_new_end(std::unique(conts.begin(), conts.end()));           // this should be faster to do once than to use a set to insert

  conts.resize(std::distance(conts.begin(), conts_new_end));
}
  std::vector<std::function<void()>> funcs_press;                               // generate a vector of functions for when it's pressed
}
  std::vector<std::function<void()>> funcs_release;                             // generate a vector of functions for when it's released

  for(auto const &this_control : conts) {
#endif // INPUTSTORM_BINDING_SETS_MOUSEBUTTON_H_INCLUDED
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
    parent_mousebutton.bind(binding, func_press_combined, func_release_combined);
  } else {
    parent_mousebutton.unbind(binding);
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
