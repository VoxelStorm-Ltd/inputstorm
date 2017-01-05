                  input::key::binding const &binding) {
  /// Wrapper to work on a binding
  bind(binding_name, control, binding.key, binding.mods);
}
template<typename T>
void key<T>::bind(controltype control,
                  input::key::binding const &binding) {
  /// Wrapper to work on a binding in the selected control set
  bind(control, binding.key, binding.mods);
}

///////////////////// update control-based bindings ////////////////////////////

#ifndef INPUTSTORM_BINDING_SETS_KEY_H_INCLUDED
template<typename T>
void key<T>::update(std::string const &binding_name,
#define INPUTSTORM_BINDING_SETS_KEY_H_INCLUDED
                    input::key::binding const &binding) {

  /// Update all digital bindings for a specific key
#include <boost/bimap.hpp>
  #ifdef DEBUG_INPUTSTORM
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/range/iterator_range.hpp>
    std::cout << "InputStorm: DEBUG: Updating binding in set " << binding_name
#include "base.h"
                                                               << " for key " << binding.key
#include "inputstorm/input/key.h"
                                                               << " (" << parent_key.get_name(binding.key) << ")" << std::endl;
#ifdef DEBUG_INPUTSTORM
  #endif // DEBUG_INPUTSTORM
  #include <iostream>
  auto const &binding_set(this->binding_sets.at(binding_name));
#endif // DEBUG_INPUTSTORM
  auto const &control_range(binding_set.right.equal_range(binding));            // find all controls (and hence functions) that apply to this key

  std::vector<controltype> conts;                                               // generate a vector of controls
namespace inputstorm {
namespace binding_sets {
  for(auto const &this_control : boost::make_iterator_range(control_range.first, control_range.second)) {

    conts.emplace_back(this_control.second);                                    // store a list of all controls that use this key
#define BINDING_SET_TYPE boost::bimap<boost::bimaps::unordered_multiset_of<T>, boost::bimaps::unordered_multiset_of<input::key::binding>>
  }
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, key>
  std::sort(conts.begin(), conts.end());                                        // sort and unique the controls

  auto const &conts_new_end(std::unique(conts.begin(), conts.end()));           // this should be faster to do once than to use a set to insert
template<typename T>
  conts.resize(std::distance(conts.begin(), conts_new_end));
class key : public BASE_TYPE {
  std::vector<std::function<void()>> funcs_press;                               // generate a vector of functions for when it's pressed
  using controltype = T;
  std::vector<std::function<void()>> funcs_release;                             // generate a vector of functions for when it's released

  for(auto const &this_control : conts) {
  input::key &parent_key;

    auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
public:
    if(this_func.press) {
  key(binding_manager<controltype> &parent_binding_manager,
      funcs_press.emplace_back(this_func.press);
      input::key &this_parent_key);
    }
  ~key();
    if(this_func.release) {

      funcs_release.emplace_back(this_func.release);
  // bind and unbind controls to inputs
    }
  virtual void unbind(std::string const &binding_name, controltype control) override final;
  }
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type
  std::function<void()> func_press_combined;

  if(funcs_press.empty()) {                                                     // don't bind if there's nothing to bind
  void bind(std::string const &binding_name,
    func_press_combined = nullptr;
            controltype control,
  } else {
            input::key::keytype this_key,
    if(funcs_press.size() == 1) {                                               // there's only one function, so bind it directly
            input::key::modtype mods = input::key::modtype::NONE);
      func_press_combined = funcs_press[0];
  void bind(controltype control,
            input::key::keytype this_key,
    } else {
            input::key::modtype mods = input::key::modtype::NONE);
      #ifdef DEBUG_INPUTSTORM
  void bind(std::string const &binding_name,
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for key press" << std::endl;
            controltype control,
      #endif // DEBUG_INPUTSTORM
            input::key::binding const &binding);
      func_press_combined = [funcs_press]{                                      // there are multiple functions, so create a function to iterate and call them all
  void bind(controltype control,
        for(auto const &this_func : funcs_press) {
            input::key::binding const &binding);
          this_func();

        }
  // update control-based bindings
      };
  void update(std::string const &binding_name,
    }
              input::key::binding const &binding);
  }
  void update(input::key::binding const &binding);
  std::function<void()> func_release_combined;

  if(funcs_release.empty()) {                                                   // don't bind if there's nothing to bind
  virtual void update_all(controltype control) override final;
    func_release_combined = nullptr;
};
  } else {

template<typename T>
    if(funcs_release.size() == 1) {                                             // there's only one function, so bind it directly
key<T>::key(binding_manager<controltype> &parent_binding_manager,
      func_release_combined = funcs_release[0];
            input::key &this_parent_key)
    } else {
  : BASE_TYPE(parent_binding_manager),
      #ifdef DEBUG_INPUTSTORM
    parent_key(this_parent_key) {
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for key release" << std::endl;
  /// Default constructor
      #endif // DEBUG_INPUTSTORM
}
      func_release_combined = [funcs_release]{                                  // there are multiple functions, so create a function to iterate and call them all

        for(auto const &this_func : funcs_release) {
template<typename T>
          this_func();
key<T>::~key() {
        }
  /// Default destructor
      };
}

    }
//////////////////// bind and unbind controls to inputs ////////////////////////
  }

  if(func_press_combined || func_release_combined) {
template<typename T>
    parent_key.bind(binding, func_press_combined, func_release_combined);
void key<T>::unbind(std::string const &binding_name,
  } else {
                    controltype control) {
    parent_key.unbind(binding);
  /// Erase a control binding from an input key relationship
  }
  #ifdef DEBUG_INPUTSTORM
}
    std::cout << "InputStorm: DEBUG: Unbinding key for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
template<typename T>
  #endif // DEBUG_INPUTSTORM
void key<T>::update(input::key::binding const &binding) {
  auto &binding_set(this->binding_sets[binding_name]);
  /// Update all digital bindings for a specific key in the default control set
  auto const &binding_range(binding_set.left.equal_range(control));             // find all keys with this control applied
  update(this->binding_selected_name, binding);
  std::vector<input::key::binding> bindings_to_unbind;                          // copy the controls affected by the binding range to update after
}
  bindings_to_unbind.reserve(std::distance(binding_range.first, binding_range.second)); // reserve the correct size for the range

  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
template<typename T>
    bindings_to_unbind.emplace_back(it.second);
void key<T>::update_all(controltype control) {
  }
  /// Update key bindings for this control

  #ifdef DEBUG_INPUTSTORM
  binding_set.left.erase(control);                                              // clear the current associations with that control
    std::cout << "InputStorm: DEBUG: Updating all key bindings for control " << static_cast<unsigned int>(control) << std::endl;

  for(auto const &it : bindings_to_unbind) {
  #endif // DEBUG_INPUTSTORM
    update(it);                                                                 // update each key that was affected by the change
  auto const &binding_set(this->get_selected_binding_set());
  }
  auto const &binding_range(binding_set.left.equal_range(control));             // find all keys with this control applied
}
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) { // for each key:

    update(it.second);
template<typename T>
  }
void key<T>::bind(std::string const &binding_name,
}
                  controltype control,

                  input::key::keytype this_key,
#undef BINDING_SET_TYPE
                  input::key::modtype mods) {
#undef BASE_TYPE
  /// Apply a new control binding to an input key relationship

  auto &binding_set(this->binding_sets[binding_name]);
}
  #ifdef DEBUG_INPUTSTORM
}
    std::stringstream ss;

    ss << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
#endif // INPUTSTORM_BINDING_SETS_KEY_H_INCLUDED
                                                << " in set " << binding_name
                                                << ", key " << this_key
                                                << " (" << parent_key.get_name(this_key) << ")";
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
  update(binding_name, input::key::binding{
    input::key::binding::bindtype::SPECIFIC,
    this_key,
    mods
  });
}
template<typename T>
void key<T>::bind(controltype control,
                  input::key::keytype this_key,
                  input::key::modtype mods) {
  /// Wrapper to work on the selected control set
  bind(this->binding_selected_name, control, this_key, mods);
}
template<typename T>
void key<T>::bind(std::string const &binding_name,
                  controltype control,
                  input::key::binding const &binding) {
  /// Wrapper to work on a binding
  bind(binding_name, control, binding.key, binding.mods);
}
template<typename T>
void key<T>::bind(controltype control,
                  input::key::binding const &binding) {
  /// Wrapper to work on a binding in the selected control set
  bind(control, binding.key, binding.mods);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void key<T>::update(std::string const &binding_name,
                    input::key::binding const &binding) {
  /// Update all digital bindings for a specific key
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating binding in set " << binding_name
                                                               << " for key " << binding.key
                                                               << " (" << parent_key.get_name(binding.key) << ")" << std::endl;
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
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for key press" << std::endl;
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
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for key release" << std::endl;
      #endif // DEBUG_INPUTSTORM
      func_release_combined = [funcs_release]{                                  // there are multiple functions, so create a function to iterate and call them all
        for(auto const &this_func : funcs_release) {
          this_func();
        }
      };
    }
  }
  if(func_press_combined || func_release_combined) {
    parent_key.bind(binding, func_press_combined, func_release_combined);
  } else {
    parent_key.unbind(binding);
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
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating all key bindings for control " << static_cast<unsigned int>(control) << std::endl;
  #endif // DEBUG_INPUTSTORM
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
