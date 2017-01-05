#include "joystick.h"
#include <iostream>
#ifdef DEBUG_INPUTSTORM
  #include <sstream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
namespace input {

unsigned int constexpr const joystick::max_axis;
unsigned int constexpr const joystick::max_button;

void joystick::init() {
  /// assign a safe default function to all joystick axes
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #ifdef DEBUG_INPUTSTORM
        std::stringstream ss;
        ss << "InputStorm: DEBUG: unbound joystick function called on axis " << axis;
        if(joystick_id != 0) {
#include "joystick.h"
          ss << " on joystick id " << joystick_id;
#include <iostream>
        }
#ifdef DEBUG_INPUTSTORM
        ss << " value ";
  #include <sstream>
        bind_axis(joystick_id, axis, [s = ss.str()](float value){
#endif // DEBUG_INPUTSTORM
          std::cout << s << std::fixed << value << std::endl;

        });
namespace inputstorm {
      #else
namespace input {
        bind_axis(joystick_id, axis, [](float value __attribute__((__unused__))){}); // default to noop

        axis_bindings[joystick_id][axis].enabled = false;
unsigned int constexpr const joystick::max_axis;
      #endif // DEBUG_INPUTSTORM
unsigned int constexpr const joystick::max_button;
    }

  }
void joystick::init() {
  /// assign a safe default function to all joystick buttons
  /// assign a safe default function to all joystick axes
  for(actiontype action : actiontype()) {
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #ifdef DEBUG_INPUTSTORM
      for(unsigned int button = 0; button != max_button; ++button) {
        std::stringstream ss;
        #ifdef DEBUG_INPUTSTORM
        ss << "InputStorm: DEBUG: unbound joystick function called on axis " << axis;
          std::stringstream ss;
        if(joystick_id != 0) {
          ss << "InputStorm: DEBUG: unbound joystick function called on button " << button;
          ss << " on joystick id " << joystick_id;
          if(joystick_id != 0) {
        }
            ss << " on joystick id " << joystick_id;
        ss << " value ";
          }
        bind_axis(joystick_id, axis, [s = ss.str()](float value){
          ss << " action " << get_actiontype_name(action);
          std::cout << s << std::fixed << value << std::endl;
          if(action == actiontype::PRESS) {
        });
            bind_button(joystick_id, button, action, [s = ss.str()]{
      #else
              std::cout << s << std::endl;
        bind_axis(joystick_id, axis, [](float value __attribute__((__unused__))){}); // default to noop
            });
        axis_bindings[joystick_id][axis].enabled = false;
          } else {
      #endif // DEBUG_INPUTSTORM
            bind_button(joystick_id, button, action, []{});
    }
          }
  }
        #else
  /// assign a safe default function to all joystick buttons
          bind_button(joystick_id, button, action, []{});                       // default to noop
  for(actiontype action : actiontype()) {
        #endif // DEBUG_INPUTSTORM
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      }
      for(unsigned int button = 0; button != max_button; ++button) {
    }
        #ifdef DEBUG_INPUTSTORM
  }
          std::stringstream ss;

          ss << "InputStorm: DEBUG: unbound joystick function called on button " << button;
  // all previous states are released
          if(joystick_id != 0) {
            ss << " on joystick id " << joystick_id;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
          }
    button_state[joystick_id].fill(actiontype::RELEASE);
          ss << " action " << get_actiontype_name(action);
  }
          if(action == actiontype::PRESS) {

            bind_button(joystick_id, button, action, [s = ss.str()]{
  // enable all the joysticks by default
              std::cout << s << std::endl;
  enabled.fill(true);
            });
  update_names();
          } else {

            bind_button(joystick_id, button, action, []{});
  // report status
          }
  std::cout << "InputStorm: Joystick axis bindings:   " << sizeof(axis_bindings) / 1024 << "KB" << std::endl;
        #else
  std::cout << "InputStorm: Joystick button bindings: " << sizeof(button_bindings) / 1024 << "KB" << std::endl;
          bind_button(joystick_id, button, action, []{});                       // default to noop
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
        #endif // DEBUG_INPUTSTORM
    if(glfwJoystickPresent(joystick_id)) {
      }
      std::cout << "InputStorm: Joystick " << joystick_id << ": " << names[joystick_id] << std::endl;
    }
    }
  }
  }

}
  // all previous states are released

  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
joystick_axis_bindingtype const &joystick::axis_binding_at(unsigned int joystick_id, unsigned int axis) const {
    button_state[joystick_id].fill(actiontype::RELEASE);
  }
  /// Accessor for the joystick axis structure sparse arrays

  #ifndef NDEBUG
  // enable all the joysticks by default
    // boundary safety check
  enabled.fill(true);
    if(joystick_id >= max) {
  update_names();
      std::cout << "InputStorm: ERROR: attempting to address axis of joystick id " << joystick_id << " when max is " << max - 1 << std::endl;

      return axis_bindings[0][0];
  // report status
    }
  std::cout << "InputStorm: Joystick axis bindings:   " << sizeof(axis_bindings) / 1024 << "KB" << std::endl;
    if(axis >= max_axis) {
  std::cout << "InputStorm: Joystick button bindings: " << sizeof(button_bindings) / 1024 << "KB" << std::endl;
      std::cout << "InputStorm: ERROR: attempting to address axis number " << axis << " when max is " << max_axis - 1 << std::endl;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      return axis_bindings[0][0];
    if(glfwJoystickPresent(joystick_id)) {
    }
      std::cout << "InputStorm: Joystick " << joystick_id << ": " << names[joystick_id] << std::endl;
  #endif // NDEBUG
    }
  return axis_bindings[joystick_id][axis];
  }
}
}

std::function<void()> const &joystick::button_binding_at(unsigned int joystick_id, unsigned int button, actiontype action) const {
joystick_axis_bindingtype const &joystick::axis_binding_at(unsigned int joystick_id, unsigned int axis) const {
  /// Accessor for the joystick button function sparse arrays
  /// Accessor for the joystick axis structure sparse arrays
  #ifndef NDEBUG
  #ifndef NDEBUG
    // boundary safety check
    // boundary safety check
    if(joystick_id >= max) {
    if(joystick_id >= max) {
      std::cout << "InputStorm: ERROR: attempting to address button of joystick id " << joystick_id << " when max is " << max - 1 << std::endl;
      std::cout << "InputStorm: ERROR: attempting to address axis of joystick id " << joystick_id << " when max is " << max - 1 << std::endl;
      return button_bindings[0][0][0];
      return axis_bindings[0][0];
    }
    }
    if(button >= max_button) {
    if(axis >= max_axis) {
      std::cout << "InputStorm: ERROR: attempting to address button number " << button << " when max is " << max_button - 1 << std::endl;
      std::cout << "InputStorm: ERROR: attempting to address axis number " << axis << " when max is " << max_axis - 1 << std::endl;
      return button_bindings[0][0][0];
      return axis_bindings[0][0];
    }
    }
    if(static_cast<unsigned int>(action) > static_cast<unsigned int>(actiontype::LAST)) {
  #endif // NDEBUG
  return axis_bindings[joystick_id][axis];
      std::cout << "InputStorm: ERROR: attempting to address button action " << static_cast<unsigned int>(action) << " when max is " << static_cast<unsigned int>(actiontype::LAST) << std::endl;
}
      return button_bindings[0][0][0];
std::function<void()> const &joystick::button_binding_at(unsigned int joystick_id, unsigned int button, actiontype action) const {
    }
  /// Accessor for the joystick button function sparse arrays
  #endif // NDEBUG
  #ifndef NDEBUG
  return button_bindings[static_cast<unsigned int>(action)][joystick_id][button];
    // boundary safety check
}
    if(joystick_id >= max) {
std::vector<unsigned int> joystick::get_connected_ids() const {
      std::cout << "InputStorm: ERROR: attempting to address button of joystick id " << joystick_id << " when max is " << max - 1 << std::endl;
  /// Return a list of attached joystick numbers
      return button_bindings[0][0][0];
  std::vector<unsigned int> out;
    }
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    if(button >= max_button) {
    if(glfwJoystickPresent(joystick_id)) {
      std::cout << "InputStorm: ERROR: attempting to address button number " << button << " when max is " << max_button - 1 << std::endl;
      out.emplace_back(joystick_id);
      return button_bindings[0][0][0];
    }
    }
  }
    if(static_cast<unsigned int>(action) > static_cast<unsigned int>(actiontype::LAST)) {
  return out;
      std::cout << "InputStorm: ERROR: attempting to address button action " << static_cast<unsigned int>(action) << " when max is " << static_cast<unsigned int>(actiontype::LAST) << std::endl;
}
      return button_bindings[0][0][0];
std::string const &joystick::get_name(unsigned int joystick_id) const {
    }
  /// Return the name of a specific joystick ID
  #endif // NDEBUG
  return names[joystick_id];
  return button_bindings[static_cast<unsigned int>(action)][joystick_id][button];
}
}
std::string joystick::get_actiontype_name(actiontype action) {
std::vector<unsigned int> joystick::get_connected_ids() const {
  /// Return a human-readable name for this joystick button actiontype
  /// Return a list of attached joystick numbers
  switch(action) {
  std::vector<unsigned int> out;
  case actiontype::RELEASE:
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    return "RELEASE";
    if(glfwJoystickPresent(joystick_id)) {
  case actiontype::PRESS:
      out.emplace_back(joystick_id);
    }
    return "PRESS";
  }
  default:
  return out;
    return "";
}
  }
std::string const &joystick::get_name(unsigned int joystick_id) const {
}
  /// Return the name of a specific joystick ID

  return names[joystick_id];
void joystick::bind_axis(unsigned int joystick_id,
}
                         unsigned int axis,
std::string joystick::get_actiontype_name(actiontype action) {
                         std::function<void(float)> func,
  /// Return a human-readable name for this joystick button actiontype
                         bool flip,
  switch(action) {
                         float deadzone_min,
  case actiontype::RELEASE:
                         float deadzone_max,
    return "RELEASE";
                         float saturation_min,
  case actiontype::PRESS:
                         float saturation_max,
    return "PRESS";
                         float centre) {
  default:
    return "";
  /// Bind a function to a joystick axis, with the specified parameters
  }
  #ifndef NDEBUG
}
    if(!func) {

      std::cout << "InputStorm: WARNING: Binding a null function to axis " << axis << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
void joystick::bind_axis(unsigned int joystick_id,
    }
                         unsigned int axis,
  #endif // NDEBUG
                         std::function<void(float)> func,
  joystick_axis_bindingtype &this_binding = axis_bindings[joystick_id][axis];   // NOTE: this will contain the already bound axis configuration, which will remember anything not explicitly set here
                         bool flip,
  this_binding.deadzone_min = deadzone_min;
                         float deadzone_min,
  this_binding.deadzone_max = deadzone_max;
                         float deadzone_max,
  this_binding.saturation_min = saturation_min;
                         float saturation_min,
  this_binding.saturation_max = saturation_max;
                         float saturation_max,
  this_binding.centre = centre;
                         float centre) {

  /// Bind a function to a joystick axis, with the specified parameters
  if(flip) {                                                                    // invert the axis if requested
  #ifndef NDEBUG
    if(this_binding.premultiply > 0) {
    if(!func) {
      this_binding.premultiply *= -1.0f;                                        // keep the premultiply, and invert it only if it's not already facing the right way
      std::cout << "InputStorm: WARNING: Binding a null function to axis " << axis << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
    }
    }
  #endif // NDEBUG
  } else {
  joystick_axis_bindingtype &this_binding = axis_bindings[joystick_id][axis];   // NOTE: this will contain the already bound axis configuration, which will remember anything not explicitly set here
    if(this_binding.premultiply < 0) {
  this_binding.deadzone_min = deadzone_min;
      this_binding.premultiply *= -1.0f;                                        // keep the premultiply, and invert it only if it's not already facing the right way
  this_binding.deadzone_max = deadzone_max;
    }
  this_binding.saturation_min = saturation_min;
  }
  this_binding.saturation_max = saturation_max;
  this_binding.update_scales();
  this_binding.centre = centre;
  this_binding.func = func;

  this_binding.enabled = true;
  if(flip) {                                                                    // invert the axis if requested
}
    if(this_binding.premultiply > 0) {
void joystick::bind_axis_half(unsigned int joystick_id, unsigned int axis, std::function<void(float)> func, bool flip) {
      this_binding.premultiply *= -1.0f;                                        // keep the premultiply, and invert it only if it's not already facing the right way
  /// Helper function for binding to output on a half-axis, for instance with a throttle control that ranges -1 to 1
    }
  bind_axis(joystick_id, axis, func, flip, 0.0f, 0.0f, -1.0f, 2.0f, -1.0f);
  } else {
}
    if(this_binding.premultiply < 0) {
void joystick::bind_axis(joystick::binding_axis const &this_binding, std::function<void(float)> func) {
      this_binding.premultiply *= -1.0f;                                        // keep the premultiply, and invert it only if it's not already facing the right way
    }
  /// Helper function to load binding settings from a binding object
  }
  bind_axis(this_binding.joystick_id,
  this_binding.update_scales();
            this_binding.axis,
  this_binding.func = func;
            func,
  this_binding.enabled = true;
            this_binding.flip,
}
            this_binding.deadzone_min,
void joystick::bind_axis_half(unsigned int joystick_id, unsigned int axis, std::function<void(float)> func, bool flip) {
            this_binding.deadzone_max,
  /// Helper function for binding to output on a half-axis, for instance with a throttle control that ranges -1 to 1
            this_binding.saturation_min,
  bind_axis(joystick_id, axis, func, flip, 0.0f, 0.0f, -1.0f, 2.0f, -1.0f);
            this_binding.saturation_max,
}
            this_binding.centre);
void joystick::bind_axis(joystick::binding_axis const &this_binding, std::function<void(float)> func) {
}
  /// Helper function to load binding settings from a binding object
void joystick::bind_button(unsigned int joystick_id, unsigned int button, actiontype action, std::function<void()> func) {
  bind_axis(this_binding.joystick_id,
  /// Bind a function to a joystick button
            this_binding.axis,
  #ifndef NDEBUG
            func,
    if(!func) {
            this_binding.flip,
            this_binding.deadzone_min,
      std::cout << "InputStorm: WARNING: Binding a null function to button " << button << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
            this_binding.deadzone_max,
    }
            this_binding.saturation_min,
  #endif // NDEBUG
            this_binding.saturation_max,
  button_bindings[static_cast<unsigned int>(action)][joystick_id][button] = func;
            this_binding.centre);
}
}
void joystick::bind_button_any(unsigned int joystick_id, std::function<void()> func) {
void joystick::bind_button(unsigned int joystick_id, unsigned int button, actiontype action, std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons, press event only
  /// Bind a function to a joystick button
  for(unsigned int button = 0; button != max_button; ++button) {
  #ifndef NDEBUG
    if(!func) {
    bind_button(joystick_id, button, actiontype::PRESS, func);
  }
      std::cout << "InputStorm: WARNING: Binding a null function to button " << button << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
}
    }
  #endif // NDEBUG
void joystick::bind_button_any_all(std::function<void()> func) {
  button_bindings[static_cast<unsigned int>(action)][joystick_id][button] = func;
  /// Helper function to bind a callback to all joystick buttons on all joysticks, press event only
}
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
void joystick::bind_button_any(unsigned int joystick_id, std::function<void()> func) {
    bind_button_any(joystick_id, func);
  /// Helper function to bind a callback to all joystick buttons, press event only
  }
  for(unsigned int button = 0; button != max_button; ++button) {
}
    bind_button(joystick_id, button, actiontype::PRESS, func);
void joystick::bind_button(binding_button const &this_binding,
  }
                           std::function<void()> func_press,
}
                           std::function<void()> func_release) {
void joystick::bind_button_any_all(std::function<void()> func) {
  /// Helper function to load binding settings from a binding object
  /// Helper function to bind a callback to all joystick buttons on all joysticks, press event only
  switch(this_binding.type) {
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
  case binding_button::bindtype::SPECIFIC:
    bind_button_any(joystick_id, func);
    if(func_press) {
  }
}
      bind_button(this_binding.joystick_id, this_binding.button, actiontype::PRESS, func_press);
void joystick::bind_button(binding_button const &this_binding,
    }
                           std::function<void()> func_press,
    if(func_release) {
                           std::function<void()> func_release) {
      bind_button(this_binding.joystick_id, this_binding.button, actiontype::RELEASE, func_release);
  /// Helper function to load binding settings from a binding object
    }
  switch(this_binding.type) {
    break;
  case binding_button::bindtype::SPECIFIC:
  case binding_button::bindtype::ANY:
    if(func_press) {
    if(func_press) {
      bind_button(this_binding.joystick_id, this_binding.button, actiontype::PRESS, func_press);
      bind_button_any(this_binding.joystick_id, func_press);
    }
    } else {
    if(func_release) {
      std::cout << "InputStorm: Joystick: WARNING - requested to bind to any button with a function other than PRESS on joystick " << this_binding.joystick_id << ", this is not currently supported - create a set of specific bindings instead." << std::endl;
      bind_button(this_binding.joystick_id, this_binding.button, actiontype::RELEASE, func_release);
    }
    }
    #ifndef NDEBUG
    break;
      if(func_release) {
  case binding_button::bindtype::ANY:
    if(func_press) {
        std::cout << "InputStorm: WARNING: Requested to bind a function to any button release on joystick " << this_binding.joystick_id << ", which is not possible - create a set of specific bindings instead." << std::endl;
      bind_button_any(this_binding.joystick_id, func_press);
      }
    } else {
    #endif // NDEBUG
      std::cout << "InputStorm: Joystick: WARNING - requested to bind to any button with a function other than PRESS on joystick " << this_binding.joystick_id << ", this is not currently supported - create a set of specific bindings instead." << std::endl;
    break;
    }
  case binding_button::bindtype::ANY_ALL:
    #ifndef NDEBUG
    if(func_press) {
      if(func_release) {
      bind_button_any_all(func_press);
        std::cout << "InputStorm: WARNING: Requested to bind a function to any button release on joystick " << this_binding.joystick_id << ", which is not possible - create a set of specific bindings instead." << std::endl;
    } else {
      }
      std::cout << "InputStorm: Joystick: WARNING - requested to bind to any button on all joysticks with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
    #endif // NDEBUG
    }
    break;
    #ifndef NDEBUG
  case binding_button::bindtype::ANY_ALL:
      if(func_release) {
    if(func_press) {
        std::cout << "InputStorm: WARNING: Requested to bind a function to any button release on all joysticks, which is not possible - create a set of specific bindings instead." << std::endl;
      bind_button_any_all(func_press);
      }
    } else {
    #endif // NDEBUG
      std::cout << "InputStorm: Joystick: WARNING - requested to bind to any button on all joysticks with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
    break;
    }
  }
    #ifndef NDEBUG
}
      if(func_release) {

        std::cout << "InputStorm: WARNING: Requested to bind a function to any button release on all joysticks, which is not possible - create a set of specific bindings instead." << std::endl;
void joystick::unbind_axis(unsigned int joystick_id, unsigned int axis) {
      }
    #endif // NDEBUG
  /// Unbind a callback on a joystick axis
    break;
  joystick_axis_bindingtype &this_binding = axis_bindings[joystick_id][axis];
  }
  this_binding.func = [](float value __attribute__((unused))){};                // noop
}
  this_binding.enabled = false;

}
void joystick::unbind_axis(unsigned int joystick_id, unsigned int axis) {
void joystick::unbind_axis_any(unsigned int joystick_id) {
  /// Unbind a callback on a joystick axis
  /// Helper function to unbind all axes on a joystick
  joystick_axis_bindingtype &this_binding = axis_bindings[joystick_id][axis];
  for(unsigned int axis = 0; axis != max_axis; ++axis) {
  this_binding.func = [](float value __attribute__((unused))){};                // noop
    unbind_axis(joystick_id, axis);
  this_binding.enabled = false;
  }
}
}
void joystick::unbind_axis_any(unsigned int joystick_id) {
void joystick::unbind_axis_any_all() {
  /// Helper function to unbind all axes on a joystick
  /// Helper function to unbind all axes on all joysticks
  for(unsigned int axis = 0; axis != max_axis; ++axis) {
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    unbind_axis(joystick_id, axis);
    unbind_axis_any(joystick_id);
  }
  }
}
}
void joystick::unbind_axis_any_all() {
void joystick::unbind_axis(binding_axis const &this_binding) {
  /// Helper function to unbind all axes on all joysticks
  /// Helper function to unbind using a binding object
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    unbind_axis_any(joystick_id);
  unbind_axis(this_binding.joystick_id, this_binding.axis);
  }
}
}

void joystick::unbind_axis(binding_axis const &this_binding) {
void joystick::unbind_button(unsigned int joystick_id, unsigned int button, actiontype action) {
  /// Helper function to unbind using a binding object
  /// Unbind a callback on a joystick button with a specific action
  unbind_axis(this_binding.joystick_id, this_binding.axis);
  button_bindings[static_cast<unsigned int>(action)][joystick_id][button] = []{}; // noop
}
}

void joystick::unbind_button_any(unsigned int joystick_id) {
void joystick::unbind_button(unsigned int joystick_id, unsigned int button, actiontype action) {
  /// Helper function to unbind all buttons on a joystick, all actions
  /// Unbind a callback on a joystick button with a specific action
  for(unsigned int button = 0; button != max_button; ++button) {
  button_bindings[static_cast<unsigned int>(action)][joystick_id][button] = []{}; // noop
    unbind_button(joystick_id, button, actiontype::PRESS);
}
    unbind_button(joystick_id, button, actiontype::RELEASE);
void joystick::unbind_button_any(unsigned int joystick_id) {
  }
  /// Helper function to unbind all buttons on a joystick, all actions
}
  for(unsigned int button = 0; button != max_button; ++button) {
void joystick::unbind_button_any_all() {
    unbind_button(joystick_id, button, actiontype::PRESS);
  /// Helper function to unbind all buttons with all actions on all joysticks
    unbind_button(joystick_id, button, actiontype::RELEASE);
  }
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
}
    unbind_button_any(joystick_id);
void joystick::unbind_button_any_all() {
  }
  /// Helper function to unbind all buttons with all actions on all joysticks
}
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
void joystick::unbind_button(binding_button const &this_binding) {
    unbind_button_any(joystick_id);
  /// Helper function to unbind using a binding object
  }
  switch(this_binding.type) {
}
  case binding_button::bindtype::SPECIFIC:
void joystick::unbind_button(binding_button const &this_binding) {
    unbind_button(this_binding.joystick_id, this_binding.button, actiontype::PRESS);
  /// Helper function to unbind using a binding object
    unbind_button(this_binding.joystick_id, this_binding.button, actiontype::RELEASE);
  switch(this_binding.type) {
    // note: there is no REPEAT action for joystick buttons!
  case binding_button::bindtype::SPECIFIC:
    break;
    unbind_button(this_binding.joystick_id, this_binding.button, actiontype::PRESS);
  case binding_button::bindtype::ANY:
    unbind_button(this_binding.joystick_id, this_binding.button, actiontype::RELEASE);
    unbind_button_any(this_binding.joystick_id);
    // note: there is no REPEAT action for joystick buttons!
    break;
    break;
  case binding_button::bindtype::ANY_ALL:
  case binding_button::bindtype::ANY:
    unbind_button_any_all();
    unbind_button_any(this_binding.joystick_id);
    break;
    break;
  }
  case binding_button::bindtype::ANY_ALL:
}
    unbind_button_any_all();

    break;
  }
void joystick::execute_axis(unsigned int joystick_id, unsigned int axis, float value) const {
}
  /// Call the function associated with a joystick axis, having transformed the value appropriately

  joystick_axis_bindingtype const &this_binding = axis_binding_at(joystick_id, axis);
void joystick::execute_axis(unsigned int joystick_id, unsigned int axis, float value) const {
  if(!this_binding.enabled) {
  /// Call the function associated with a joystick axis, having transformed the value appropriately
    return;                                                                     // early exit in case this binding isn't in use
  joystick_axis_bindingtype const &this_binding = axis_binding_at(joystick_id, axis);
  }
  if(!this_binding.enabled) {
  this_binding.execute(value);
    return;                                                                     // early exit in case this binding isn't in use
}
  }
void joystick::execute_button(unsigned int joystick_id, unsigned int button, actiontype action) {
  this_binding.execute(value);
  /// Call the function associated with a joystick button
}
  if(button_state[joystick_id][button] == action) {                             // skip repeat-calling functions when the state hasn't changed
void joystick::execute_button(unsigned int joystick_id, unsigned int button, actiontype action) {
    return;
  /// Call the function associated with a joystick button
  }
  if(button_state[joystick_id][button] == action) {                             // skip repeat-calling functions when the state hasn't changed
  button_state[joystick_id][button] = action;
    return;
  }
  button_binding_at(joystick_id, button, action)();
  button_state[joystick_id][button] = action;
}
  button_binding_at(joystick_id, button, action)();

}
void joystick::capture_axis(std::function<void(unsigned int, unsigned int, bool)> callback,

                            bool calibrate) {
void joystick::capture_axis(std::function<void(unsigned int, unsigned int, bool)> callback,
  /// Capture an axis movement and return it to the given callback
                            bool calibrate) {
  static bool calibrated = false;
  /// Capture an axis movement and return it to the given callback
  static std::array<std::array<float, max_axis>, max> initial_values;
  static bool calibrated = false;
  if(calibrate || !calibrated) {
  static std::array<std::array<float, max_axis>, max> initial_values;
  if(calibrate || !calibrated) {
    // read the initial values of all axes, and store them for later comparison - some axes don't default to zero, so we need to catch the biggest change
    // read the initial values of all axes, and store them for later comparison - some axes don't default to zero, so we need to catch the biggest change
    std::cout << "InputStorm: Calibrating for capture" << std::endl;
    std::cout << "InputStorm: Calibrating for capture" << std::endl;
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      int num_axes;
      int num_axes;
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
        initial_values[joystick_id][axis] = axis_data[axis];
        initial_values[joystick_id][axis] = axis_data[axis];
        #ifdef DEBUG_INPUTSTORM
        #ifdef DEBUG_INPUTSTORM
          std::cout << "InputStorm: DEBUG: Calibrated id " << joystick_id
          std::cout << "InputStorm: DEBUG: Calibrated id " << joystick_id
                    << " axis " << axis
                    << " axis " << axis
                    << ": " << initial_values[joystick_id][axis] << std::endl;
                    << ": " << initial_values[joystick_id][axis] << std::endl;
        #endif // DEBUG_INPUTSTORM
        #endif // DEBUG_INPUTSTORM
      }
      }
    }
    }
    calibrated = true;
    calibrated = true;
    if(calibrate) {
    if(calibrate) {
      return;
      return;
    }
    }
  }
  }


  float constexpr const deadzone = 0.5f;
  float constexpr const deadzone = 0.5f;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #ifdef DEBUG_INPUTSTORM
      #ifdef DEBUG_INPUTSTORM
        std::stringstream ss;
        std::stringstream ss;
        ss << "InputStorm: DEBUG: id " << joystick_id << " axis " << axis << ": ";
        ss << "InputStorm: DEBUG: id " << joystick_id << " axis " << axis << ": ";
      #endif // DEBUG_INPUTSTORM
      #endif // DEBUG_INPUTSTORM
      float const initial_value = initial_values[joystick_id][axis];
      float const initial_value = initial_values[joystick_id][axis];
      #ifdef DEBUG_INPUTSTORM
      #ifdef DEBUG_INPUTSTORM
        bind_axis(joystick_id, axis, [callback, s = ss.str(), joystick_id, axis, initial_value](float value){
      #else
        bind_axis(joystick_id, axis, [callback, s = ss.str(), joystick_id, axis, initial_value](float value){
        bind_axis(joystick_id, axis, [callback, joystick_id, axis, initial_value](float value){
      #else
      #endif // DEBUG_INPUTSTORM
        bind_axis(joystick_id, axis, [callback, joystick_id, axis, initial_value](float value){
        float const offset = value - initial_value;
      #endif // DEBUG_INPUTSTORM
        if(offset > deadzone) {
        float const offset = value - initial_value;
          #ifdef DEBUG_INPUTSTORM
        if(offset > deadzone) {
            std::cout << s << std::fixed << value << "(offset: pos " << offset << ")" <<  std::endl;
          #ifdef DEBUG_INPUTSTORM
          #endif // DEBUG_INPUTSTORM
            std::cout << s << std::fixed << value << "(offset: pos " << offset << ")" <<  std::endl;
          callback(joystick_id, axis, false);
          #endif // DEBUG_INPUTSTORM
        } else if(offset < -deadzone) {
          callback(joystick_id, axis, false);
          #ifdef DEBUG_INPUTSTORM
        } else if(offset < -deadzone) {
            std::cout << s << std::fixed << value << "(offset: neg " << offset << ")" <<  std::endl;
          #ifdef DEBUG_INPUTSTORM
          #endif // DEBUG_INPUTSTORM
            std::cout << s << std::fixed << value << "(offset: neg " << offset << ")" <<  std::endl;
          callback(joystick_id, axis, true);
          #endif // DEBUG_INPUTSTORM
        }
          callback(joystick_id, axis, true);
      });
        }
    }
      });
  }
    }
}
  }
void joystick::capture_axis(std::function<void(binding_axis const&)> callback,
}
                            bool calibrate) {
void joystick::capture_axis(std::function<void(binding_axis const&)> callback,
  /// Capture an axis movement and return it to the given callback as a binding object
                            bool calibrate) {
  #ifdef DEBUG_INPUTSTORM
  /// Capture an axis movement and return it to the given callback as a binding object
    std::cout << "InputStorm: DEBUG: capturing joystick axis" << std::endl;
  #ifdef DEBUG_INPUTSTORM
  #endif // DEBUG_INPUTSTORM
  static bool calibrated = false;
    std::cout << "InputStorm: DEBUG: capturing joystick axis" << std::endl;
  static std::array<std::array<float, max_axis>, max> initial_values;
  #endif // DEBUG_INPUTSTORM
  if(calibrate || !calibrated) {
  static bool calibrated = false;
    // read the initial values of all axes, and store them for later comparison - some axes don't default to zero, so we need to catch the biggest change
  static std::array<std::array<float, max_axis>, max> initial_values;
    std::cout << "InputStorm: Calibrating for capture" << std::endl;
  if(calibrate || !calibrated) {
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    // read the initial values of all axes, and store them for later comparison - some axes don't default to zero, so we need to catch the biggest change
      int num_axes;
    std::cout << "InputStorm: Calibrating for capture" << std::endl;
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      int num_axes;
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
        initial_values[joystick_id][axis] = axis_data[axis];
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
        #ifdef DEBUG_INPUTSTORM
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
          std::cout << "InputStorm: DEBUG: Calibrated id " << joystick_id
        initial_values[joystick_id][axis] = axis_data[axis];
                    << " axis " << axis
        #ifdef DEBUG_INPUTSTORM
                    << ": " << initial_values[joystick_id][axis] << std::endl;
        #endif // DEBUG_INPUTSTORM
          std::cout << "InputStorm: DEBUG: Calibrated id " << joystick_id
      }
                    << " axis " << axis
    }
                    << ": " << initial_values[joystick_id][axis] << std::endl;
    calibrated = true;
        #endif // DEBUG_INPUTSTORM
    if(calibrate) {
      }
      return;
    }
    }
    calibrated = true;
  }
    if(calibrate) {

      return;
  float constexpr const deadzone = 0.5f;
    }
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
  }
    for(unsigned int axis = 0; axis != max_axis; ++axis) {

      #ifdef DEBUG_INPUTSTORM
  float constexpr const deadzone = 0.5f;
        std::stringstream ss;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
        ss << "InputStorm: DEBUG: id " << joystick_id << " axis " << axis << ": ";
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #endif // DEBUG_INPUTSTORM
      #ifdef DEBUG_INPUTSTORM
      float const initial_value = initial_values[joystick_id][axis];
        std::stringstream ss;
      #ifdef DEBUG_INPUTSTORM
        ss << "InputStorm: DEBUG: id " << joystick_id << " axis " << axis << ": ";
        bind_axis(joystick_id, axis, [callback, s = ss.str(), joystick_id, axis, initial_value](float value){
      #endif // DEBUG_INPUTSTORM
      #else
      float const initial_value = initial_values[joystick_id][axis];
        bind_axis(joystick_id, axis, [callback, joystick_id, axis, initial_value](float value){
      #ifdef DEBUG_INPUTSTORM
      #endif // DEBUG_INPUTSTORM
        float const offset = value - initial_value;
        bind_axis(joystick_id, axis, [callback, s = ss.str(), joystick_id, axis, initial_value](float value){
        if(offset > deadzone) {
      #else
          #ifdef DEBUG_INPUTSTORM
        bind_axis(joystick_id, axis, [callback, joystick_id, axis, initial_value](float value){
            std::cout << s << std::fixed << value << "(offset: pos " << offset << ")" <<  std::endl;
      #endif // DEBUG_INPUTSTORM
          #endif // DEBUG_INPUTSTORM
        float const offset = value - initial_value;
          callback(binding_axis{joystick_id, axis, false, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f});
        if(offset > deadzone) {
        } else if(offset < -deadzone) {
          #ifdef DEBUG_INPUTSTORM
          #ifdef DEBUG_INPUTSTORM
            std::cout << s << std::fixed << value << "(offset: pos " << offset << ")" <<  std::endl;
            std::cout << s << std::fixed << value << "(offset: neg " << offset << ")" <<  std::endl;
          #endif // DEBUG_INPUTSTORM
          #endif // DEBUG_INPUTSTORM
          callback(binding_axis{joystick_id, axis, false, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f});
          callback(binding_axis{joystick_id, axis, true, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f});
        } else if(offset < -deadzone) {
        }
          #ifdef DEBUG_INPUTSTORM
      });
            std::cout << s << std::fixed << value << "(offset: neg " << offset << ")" <<  std::endl;
    }
  }
          #endif // DEBUG_INPUTSTORM
}
          callback(binding_axis{joystick_id, axis, true, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f});
void joystick::capture_button(std::function<void(unsigned int, unsigned int)> callback) {
        }
  /// Capture a button press and return it to the given callback
      });
  #ifdef DEBUG_INPUTSTORM
    }
    std::cout << "InputStorm: DEBUG: capturing joystick button" << std::endl;
  }
  #endif // DEBUG_INPUTSTORM
}
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
void joystick::capture_button(std::function<void(unsigned int, unsigned int)> callback) {
    for(unsigned int button = 0; button != max_button; ++button) {
  /// Capture a button press and return it to the given callback
      bind_button(joystick_id, button, actiontype::RELEASE, []{});              // unbind release actions
  #ifdef DEBUG_INPUTSTORM
      bind_button(joystick_id, button, actiontype::PRESS, [callback,
    std::cout << "InputStorm: DEBUG: capturing joystick button" << std::endl;
                                                           joystick_id,
  #endif // DEBUG_INPUTSTORM
                                                           button]{             // bind on the press action
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
        callback(joystick_id, button);
    for(unsigned int button = 0; button != max_button; ++button) {
      });
      bind_button(joystick_id, button, actiontype::RELEASE, []{});              // unbind release actions
    }
  }
      bind_button(joystick_id, button, actiontype::PRESS, [callback,
}
                                                           joystick_id,
void joystick::capture_button(std::function<void(binding_button const&)> callback) {
                                                           button]{             // bind on the press action
  /// Capture a button press and return it to the given callback as a binding object
        callback(joystick_id, button);
  #ifdef DEBUG_INPUTSTORM
      });
    std::cout << "InputStorm: DEBUG: capturing joystick button to binding" << std::endl;
    }
  #endif // DEBUG_INPUTSTORM
  }
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
}
    for(unsigned int button = 0; button != max_button; ++button) {
void joystick::capture_button(std::function<void(binding_button const&)> callback) {
      bind_button(joystick_id, button, actiontype::RELEASE, []{});              // unbind release actions
  /// Capture a button press and return it to the given callback as a binding object
      bind_button(joystick_id, button, actiontype::PRESS, [callback,
  #ifdef DEBUG_INPUTSTORM
                                                           joystick_id,
    std::cout << "InputStorm: DEBUG: capturing joystick button to binding" << std::endl;
                                                           button]{             // bind on the press action
  #endif // DEBUG_INPUTSTORM
        callback(binding_button{joystick_id, binding_button::bindtype::SPECIFIC, button});
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      });
    for(unsigned int button = 0; button != max_button; ++button) {
    }
      bind_button(joystick_id, button, actiontype::RELEASE, []{});              // unbind release actions
  }
      bind_button(joystick_id, button, actiontype::PRESS, [callback,
}

                                                           joystick_id,
void joystick::update_names() {
                                                           button]{             // bind on the press action
  /// Update the list of joystick names
        callback(binding_button{joystick_id, binding_button::bindtype::SPECIFIC, button});
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      });
    if(glfwJoystickPresent(joystick_id)) {
    }
      names[joystick_id] = glfwGetJoystickName(joystick_id);
  }
    } else {
}
      names[joystick_id].clear();

    }
void joystick::update_names() {
  }
  /// Update the list of joystick names
}
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {

    if(glfwJoystickPresent(joystick_id)) {
void joystick::poll() {
  /// Check which joysticks are attached and poll them
      names[joystick_id] = glfwGetJoystickName(joystick_id);
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    } else {
    if(!glfwJoystickPresent(joystick_id)) {
      names[joystick_id].clear();
      continue;
    }
    }
  }
    {
}
      // poll the axes

      int num_axes;
void joystick::poll() {
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
  /// Check which joysticks are attached and poll them
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
    if(!glfwJoystickPresent(joystick_id)) {
        execute_axis(joystick_id, axis, axis_data[axis]);
      continue;
      }
    }
    }
    {
    {
      // poll the axes
      // poll the buttons
      int num_axes;
      int num_buttons;
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
      unsigned char const *const button_data = glfwGetJoystickButtons(joystick_id, &num_buttons);
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      unsigned int const button_max = std::min(max_button, static_cast<unsigned int>(num_buttons));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
      for(unsigned int button = 0; button != button_max; ++button) {
        execute_axis(joystick_id, axis, axis_data[axis]);
        execute_button(joystick_id, button, static_cast<actiontype>(button_data[button]));
      }
      }
    }
    }
  }
    {
}
      // poll the buttons

      int num_buttons;
void joystick::draw_binding_graphs() const {
      unsigned char const *const button_data = glfwGetJoystickButtons(joystick_id, &num_buttons);
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      unsigned int const button_max = std::min(max_button, static_cast<unsigned int>(num_buttons));
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      for(unsigned int button = 0; button != button_max; ++button) {
      joystick_axis_bindingtype const &this_binding(axis_binding_at(joystick_id, axis));
        execute_button(joystick_id, button, static_cast<actiontype>(button_data[button]));
      if(!this_binding.enabled) {
      }
        continue;
    }
      }
  }
      std::cout << "InputStorm: Transform function on joystick " << joystick_id
}
                << " axis " << axis << ":" << std::endl;

      this_binding.draw_graph_console();
void joystick::draw_binding_graphs() const {
    }
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
  }
}
    for(unsigned int axis = 0; axis != max_axis; ++axis) {

      joystick_axis_bindingtype const &this_binding(axis_binding_at(joystick_id, axis));
}
      if(!this_binding.enabled) {
}
        continue;
      }
      std::cout << "InputStorm: Transform function on joystick " << joystick_id
                << " axis " << axis << ":" << std::endl;
      this_binding.draw_graph_console();
    }
  }
}

}
}
