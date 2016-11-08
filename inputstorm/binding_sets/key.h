#ifndef INPUTSTORM_BINDING_SETS_KEY_H_INCLUDED
#define INPUTSTORM_BINDING_SETS_KEY_H_INCLUDED

#include "base.h"
#ifdef DEBUG_INPUTSTORM
  #include <iostream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
template<typename T> class binding_manager;

namespace binding_sets {

#define BINDING_SET_TYPE boost::bimap<boost::bimaps::unordered_multiset_of<T>, boost::bimaps::unordered_multiset_of<input::key::binding>>
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, key>

template<typename T>
class key : public BASE_TYPE {
  using controltype = T;

public:
  key(manager &input_manager, binding_manager<T> &parent_binding_manager);
  ~key();

  // bind and unbind controls to inputs
  virtual void unbind(std::string const &binding_name, controltype control) override final;
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type

  void bind(std::string const &binding_name,
            controltype control,
            input::key::keytype this_key,
            input::key::modtype mods = input::key::modtype::NONE);
  void bind(controltype control,
            input::key::keytype this_key,
            input::key::modtype mods = input::key::modtype::NONE);

  // update control-based bindings
  void update(std::string const &binding_name,
              input::key::binding const &binding);
  void update(input::key::binding const &binding);

  virtual void update_all(controltype control) override final;
};

template<typename T>
key<T>::key(manager &input_manager,
            binding_manager<controltype> &parent_binding_manager)
  : BASE_TYPE(input_manager, parent_binding_manager) {
  /// Default constructor
}

template<typename T>
key<T>::~key() {
  /// Default destructor
}

//////////////////// bind and unbind controls to inputs ////////////////////////

template<typename T>
void key<T>::unbind(std::string const &binding_name,
                    controltype control) {
  /// Erase a control binding from an input key relationship
  auto &binding_set(this->binding_sets[binding_name]);
  auto const &binding_range(binding_set.left.equal_range(control));             // find all keys with this control applied
  std::vector<input::key::binding> bindings_to_unbind;                          // copy the controls affected by the binding range to update after
  bindings_to_unbind.reserve(std::distance(binding_range.first, binding_range.second)); // reserve the correct size for the range
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
    bindings_to_unbind.emplace_back(it.second);
  }

  binding_set.left.erase(control);                                              // clear the current associations with that control

  for(auto const &it : bindings_to_unbind) {
    update(it);                                                                 // update each key that was affected by the change
  }
}

template<typename T>
void key<T>::bind(std::string const &binding_name,
                  controltype control,
                  input::key::keytype this_key,
                  input::key::modtype mods) {
  /// Apply a new control binding to an input key relationship
  auto &binding_set(this->binding_sets[binding_name]);
  #ifdef DEBUG_INPUTSTORM
    std::stringstream ss;
    ss << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control) <<  " in set " << binding_name << ", key " << this_key << " (" << this->input.key.get_name(this_key) << ")";
  #endif // DEBUG_INPUTSTORM
  //if(mods == input::key::modtype::NONE) {
  //  binding_set.insert(typename base<T, BINDING_SET_TYPE>::binding_set_value_type(control, input::key::binding{input::key::binding::bindtype::ANY_MOD, this_key, input::key::modtype::NONE}));
  //} else {
    binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, input::key::binding{
      input::key::binding::bindtype::SPECIFIC,
      this_key,
      mods
    }));
    #ifdef DEBUG_INPUTSTORM
      ss << " mods " << input::key::get_mod_name(mods);
    #endif // DEBUG_INPUTSTORM
  //}
  #ifdef DEBUG_INPUTSTORM
    std::cout << ss.str() << std::endl;
  #endif // DEBUG_INPUTSTORM
}
template<typename T>
void key<T>::bind(controltype control,
                  input::key::keytype this_key,
                  input::key::modtype mods) {
  /// Wrapper to work on the selected control set
  bind(this->binding_selected_name, control, this_key, mods);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void key<T>::update(std::string const &binding_name,
                    input::key::binding const &binding) {
  /// Update all digital bindings for a specific key
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
      func_release_combined = [funcs_release]{                                  // there are multiple functions, so create a function to iterate and call them all
        for(auto const &this_func : funcs_release) {
          this_func();
        }
      };
    }
  }
  if(func_press_combined || func_release_combined) {
    this->input.key.bind(binding, func_press_combined, func_release_combined);
  } else {
    this->input.key.unbind(binding);
  }
}
template<typename T>
void key<T>::update(input::key::binding const &binding) {
  /// Update all digital bindings for a specific key in the default control set
  update(this->binding_selected_name, binding);
}

template<typename T>
void key<T>::update_all(controltype control) {
  /// Update key bindings for this control
  auto const &binding_set(this->get_selected_binding_set());
  auto const &binding_range(binding_set.left.equal_range(control));             // find all keys with this control applied
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) { // for each key:
    update(it.second);
  }
}

#undef BINDING_SET_TYPE
#undef BASE_TYPE

}
}

#endif // INPUTSTORM_BINDING_SETS_KEY_H_INCLUDED
