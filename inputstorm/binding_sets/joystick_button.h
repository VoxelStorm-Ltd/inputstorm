template<typename T>
void joystick_button<T>::bind(controltype control,
                              unsigned int joystick_id,
                              unsigned int button) {
  /// Wrapper to work on the selected control set
  bind(this->binding_selected_name, control, joystick_id, button);
}
template<typename T>
void joystick_button<T>::bind(std::string const &binding_name,
                              controltype control,
                              input::joystick::binding_button const &binding) {
  /// Wrapper to work on a binding
#ifndef INPUTSTORM_BINDING_SETS_JOYSTICK_BUTTON_H_INCLUDED
  bind(binding_name, control, binding.joystick_id, binding.button);
#define INPUTSTORM_BINDING_SETS_JOYSTICK_BUTTON_H_INCLUDED
}

template<typename T>
#include "base.h"
void joystick_button<T>::bind(controltype control,
#include "inputstorm/input/joystick.h"
                              input::joystick::binding_button const &binding) {

  /// Wrapper to work on a binding in the selected control set
namespace inputstorm {
  bind(control, binding.joystick_id, binding.button);
namespace binding_sets {
}


#define BINDING_SET_TYPE boost::bimap<boost::bimaps::unordered_multiset_of<T>, boost::bimaps::unordered_multiset_of<input::joystick::binding_button>>
///////////////////// update control-based bindings ////////////////////////////
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, joystick_button>


template<typename T>
template<typename T>
void joystick_button<T>::update(std::string const &binding_name,
class joystick_button : public BASE_TYPE {
  using controltype = T;
                                input::joystick::binding_button const &binding) {

  /// Update all digital bindings for a specific joystick button
  input::joystick &parent_joystick;
  #ifdef DEBUG_INPUTSTORM

    std::cout << "InputStorm: DEBUG: Updating binding in set " << binding_name
public:
                                                               << " for joystick " << binding.joystick_id
  joystick_button(binding_manager<controltype> &parent_binding_manager,
                                                               << " button " << binding.button << std::endl;
                  input::joystick &this_parent_joystick);
  #endif // DEBUG_INPUTSTORM
  ~joystick_button();
  auto const &binding_set(this->binding_sets.at(binding_name));

  auto const &control_range(binding_set.right.equal_range(binding));            // find all controls (and hence functions) that apply to this key
  // bind and unbind controls to inputs
  std::vector<controltype> conts;                                               // generate a vector of controls
  virtual void unbind(std::string const &binding_name, controltype control) override final;
  for(auto const &this_control : boost::make_iterator_range(control_range.first, control_range.second)) {
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type

    conts.emplace_back(this_control.second);                                    // store a list of all controls that use this key
  void bind(std::string const &binding_name,
  }
            controltype control,
  std::sort(conts.begin(), conts.end());                                        // sort and unique the controls
            unsigned int joystick_id,
  auto const &conts_new_end(std::unique(conts.begin(), conts.end()));           // this should be faster to do once than to use a set to insert
            unsigned int button);
  conts.resize(std::distance(conts.begin(), conts_new_end));
  void bind(controltype control,
  std::vector<std::function<void()>> funcs_press;                               // generate a vector of functions for when it's pressed
            unsigned int joystick_id,
  std::vector<std::function<void()>> funcs_release;                             // generate a vector of functions for when it's released
            unsigned int button);
  for(auto const &this_control : conts) {
  void bind(std::string const &binding_name,
            controltype control,
    auto const &this_func(this->bindings.action_bindings_digital[static_cast<unsigned int>(this_control)]);
            input::joystick::binding_button const &binding);
    if(this_func.press) {
  void bind(controltype control,
      funcs_press.emplace_back(this_func.press);
            input::joystick::binding_button const &binding);
    }

    if(this_func.release) {
  // update control-based bindings
      funcs_release.emplace_back(this_func.release);
  void update(std::string const &binding_name,
    }
              input::joystick::binding_button const &binding);
  }
  void update(input::joystick::binding_button const &binding);
  std::function<void()> func_press_combined;

  if(funcs_press.empty()) {                                                     // don't bind if there's nothing to bind
  virtual void update_all(controltype control) override final;
    func_press_combined = nullptr;
};
  } else {

template<typename T>
    if(funcs_press.size() == 1) {                                               // there's only one function, so bind it directly
joystick_button<T>::joystick_button(binding_manager<controltype> &parent_binding_manager,
      func_press_combined = funcs_press[0];
                                    input::joystick &this_parent_joystick)
    } else {
  : BASE_TYPE(parent_binding_manager),
      #ifdef DEBUG_INPUTSTORM
    parent_joystick(this_parent_joystick) {
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for joystick button press" << std::endl;
  /// Default constructor
      #endif // DEBUG_INPUTSTORM
}
      func_press_combined = [funcs_press]{                                      // there are multiple functions, so create a function to iterate and call them all

        for(auto const &this_func : funcs_press) {
template<typename T>
          this_func();
joystick_button<T>::~joystick_button() {
        }
  /// Default destructor
}
      };

    }
//////////////////// bind and unbind controls to inputs ////////////////////////
  }

  std::function<void()> func_release_combined;
template<typename T>
  if(funcs_release.empty()) {                                                   // don't bind if there's nothing to bind
void joystick_button<T>::unbind(std::string const &binding_name,
    func_release_combined = nullptr;
                                controltype control) {
  } else {
  /// Erase a control binding from an input joystick button relationship
    if(funcs_release.size() == 1) {                                             // there's only one function, so bind it directly
  #ifdef DEBUG_INPUTSTORM
      func_release_combined = funcs_release[0];
    std::cout << "InputStorm: DEBUG: unbinding joystick button for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
    } else {
  #endif // DEBUG_INPUTSTORM
      #ifdef DEBUG_INPUTSTORM
  auto &binding_set(this->binding_sets[binding_name]);
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for joystick button release" << std::endl;
  auto const &binding_range(binding_set.left.equal_range(control));
      #endif // DEBUG_INPUTSTORM
  auto const binding_range_copy(binding_range);                                 // copy the binding range to update after
      func_release_combined = [funcs_release]{                                  // there are multiple functions, so create a function to iterate and call them all

        for(auto const &this_func : funcs_release) {
  binding_set.left.erase(control);                                              // clear the current associations with that control
          this_func();

        }
  for(auto const &it : boost::make_iterator_range(binding_range_copy.first, binding_range_copy.second)) {
      };
    update(it.second);
    }
  }
  }
}

  if(func_press_combined || func_release_combined) {
template<typename T>
    parent_joystick.bind_button(binding, func_press_combined, func_release_combined);
void joystick_button<T>::bind(std::string const &binding_name,
  } else {
                              controltype control,
    parent_joystick.unbind_button(binding);
                              unsigned int joystick_id,
  }
                              unsigned int button) {
}
  /// Apply a new control binding to an input key relationship
template<typename T>
  #ifdef DEBUG_INPUTSTORM
void joystick_button<T>::update(input::joystick::binding_button const &binding) {
    std::cout << "InputStorm: DEBUG: Binding control " << static_cast<int>(control)
  /// Update all digital bindings for a specific joystick button in the default control set
              << " in set " << binding_name
  update(this->binding_selected_name, binding);
              << ", joystick " << joystick_id
}
              << " button " << button << std::endl;

  #endif // DEBUG_INPUTSTORM
template<typename T>
  auto &binding_set(this->binding_sets[binding_name]);
void joystick_button<T>::update_all(controltype control) {
  binding_set.insert(typename BASE_TYPE::binding_set_value_type(control, input::joystick::binding_button{
  /// Update joystick button bindings for this control
    joystick_id,
  #ifdef DEBUG_INPUTSTORM
    input::joystick::binding_button::bindtype::SPECIFIC,
    std::cout << "InputStorm: DEBUG: Updating all joystick button bindings for control " << static_cast<unsigned int>(control) << std::endl;
    button
  #endif // DEBUG_INPUTSTORM
  }));
  auto const &binding_set(this->get_selected_binding_set());
  update(binding_name, input::joystick::binding_button{joystick_id,
  auto const &binding_range(binding_set.left.equal_range(control));
                                                       input::joystick::binding_button::bindtype::SPECIFIC,
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
                                                       button});
}
    update(it.second);
template<typename T>
  }
void joystick_button<T>::bind(controltype control,
}
                              unsigned int joystick_id,

                              unsigned int button) {
#undef BINDING_SET_TYPE
  /// Wrapper to work on the selected control set
#undef BASE_TYPE
  bind(this->binding_selected_name, control, joystick_id, button);

}
}
template<typename T>
}
void joystick_button<T>::bind(std::string const &binding_name,

                              controltype control,
#endif // INPUTSTORM_BINDING_SETS_JOYSTICK_BUTTON_H_INCLUDED
                              input::joystick::binding_button const &binding) {
  /// Wrapper to work on a binding
  bind(binding_name, control, binding.joystick_id, binding.button);
}
template<typename T>
void joystick_button<T>::bind(controltype control,
                              input::joystick::binding_button const &binding) {
  /// Wrapper to work on a binding in the selected control set
  bind(control, binding.joystick_id, binding.button);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void joystick_button<T>::update(std::string const &binding_name,
                                input::joystick::binding_button const &binding) {
  /// Update all digital bindings for a specific joystick button
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating binding in set " << binding_name
                                                               << " for joystick " << binding.joystick_id
                                                               << " button " << binding.button << std::endl;
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
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for joystick button press" << std::endl;
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
        std::cout << "InputStorm: DEBUG: Combining " << funcs_press.size() << " functions for joystick button release" << std::endl;
      #endif // DEBUG_INPUTSTORM
      func_release_combined = [funcs_release]{                                  // there are multiple functions, so create a function to iterate and call them all
        for(auto const &this_func : funcs_release) {
          this_func();
        }
      };
    }
  }
  if(func_press_combined || func_release_combined) {
    parent_joystick.bind_button(binding, func_press_combined, func_release_combined);
  } else {
    parent_joystick.unbind_button(binding);
  }
}
template<typename T>
void joystick_button<T>::update(input::joystick::binding_button const &binding) {
  /// Update all digital bindings for a specific joystick button in the default control set
  update(this->binding_selected_name, binding);
}

template<typename T>
void joystick_button<T>::update_all(controltype control) {
  /// Update joystick button bindings for this control
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating all joystick button bindings for control " << static_cast<unsigned int>(control) << std::endl;
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

#endif // INPUTSTORM_BINDING_SETS_JOYSTICK_BUTTON_H_INCLUDED
