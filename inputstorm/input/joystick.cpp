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
          ss << " on joystick id " << joystick_id;
        }
        ss << " value ";
        bind_axis(joystick_id, axis, [s = ss.str()](float value){
          std::cout << s << std::fixed << value << std::endl;
        });
      #else
        bind_axis(joystick_id, axis, [](float value __attribute__((__unused__))){}); // default to noop
        axis_bindings[joystick_id][axis].enabled = false;
      #endif // DEBUG_INPUTSTORM
    }
  }
  /// assign a safe default function to all joystick buttons
  for(actiontype action : actiontype()) {
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      for(unsigned int button = 0; button != max_button; ++button) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound joystick function called on button " << button;
          if(joystick_id != 0) {
            ss << " on joystick id " << joystick_id;
          }
          ss << " action " << get_actiontype_name(action);
          if(action == actiontype::PRESS) {
            bind_button(joystick_id, button, action, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind_button(joystick_id, button, action, []{});
          }
        #else
          bind_button(joystick_id, button, action, []{});                       // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }

  // all previous states are released
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    button_state[joystick_id].fill(actiontype::RELEASE);
  }

  // enable all the joysticks by default
  enabled.fill(true);
  update_names();

  // report status
  std::cout << "InputStorm: Joystick axis bindings:   " << sizeof(axis_bindings) / 1024 << "KB" << std::endl;
  std::cout << "InputStorm: Joystick button bindings: " << sizeof(button_bindings) / 1024 << "KB" << std::endl;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    if(glfwJoystickPresent(joystick_id)) {
      std::cout << "InputStorm: Joystick " << joystick_id << ": " << names[joystick_id] << std::endl;
    }
  }
}

joystick_axis_bindingtype const &joystick::axis_binding_at(unsigned int joystick_id, unsigned int axis) const {
  /// Accessor for the joystick axis structure sparse arrays
  #ifndef NDEBUG
    // boundary safety check
    if(joystick_id >= max) {
      std::cout << "InputStorm: ERROR: attempting to address axis of joystick id " << joystick_id << " when max is " << max - 1 << std::endl;
      return axis_bindings[0][0];
    }
    if(axis >= max_axis) {
      std::cout << "InputStorm: ERROR: attempting to address axis number " << axis << " when max is " << max_axis - 1 << std::endl;
      return axis_bindings[0][0];
    }
  #endif // NDEBUG
  return axis_bindings[joystick_id][axis];
}
std::function<void()> const &joystick::button_binding_at(unsigned int joystick_id, unsigned int button, actiontype action) const {
  /// Accessor for the joystick button function sparse arrays
  #ifndef NDEBUG
    // boundary safety check
    if(joystick_id >= max) {
      std::cout << "InputStorm: ERROR: attempting to address button of joystick id " << joystick_id << " when max is " << max - 1 << std::endl;
      return button_bindings[0][0][0];
    }
    if(button >= max_button) {
      std::cout << "InputStorm: ERROR: attempting to address button number " << button << " when max is " << max_button - 1 << std::endl;
      return button_bindings[0][0][0];
    }
    if(static_cast<unsigned int>(action) > static_cast<unsigned int>(actiontype::LAST)) {
      std::cout << "InputStorm: ERROR: attempting to address button action " << static_cast<unsigned int>(action) << " when max is " << static_cast<unsigned int>(actiontype::LAST) << std::endl;
      return button_bindings[0][0][0];
    }
  #endif // NDEBUG
  return button_bindings[static_cast<unsigned int>(action)][joystick_id][button];
}
std::vector<unsigned int> joystick::get_connected_ids() const {
  /// Return a list of attached joystick numbers
  std::vector<unsigned int> out;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    if(glfwJoystickPresent(joystick_id)) {
      out.emplace_back(joystick_id);
    }
  }
  return out;
}
std::string const &joystick::get_name(unsigned int joystick_id) const {
  /// Return the name of a specific joystick ID
  return names[joystick_id];
}
std::string joystick::get_actiontype_name(actiontype action) {
  /// Return a human-readable name for this joystick button actiontype
  switch(action) {
  case actiontype::RELEASE:
    return "RELEASE";
  case actiontype::PRESS:
    return "PRESS";
  default:
    return "";
  }
}

void joystick::bind_axis(unsigned int joystick_id,
                         unsigned int axis,
                         std::function<void(float)> func,
                         bool flip,
                         float deadzone_min,
                         float deadzone_max,
                         float saturation_min,
                         float saturation_max,
                         float centre) {
  /// Bind a function to a joystick axis, with the specified parameters
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to axis " << axis << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  joystick_axis_bindingtype &this_binding = axis_bindings[joystick_id][axis];   // NOTE: this will contain the already bound axis configuration, which will remember anything not explicitly set here
  this_binding.deadzone_min = deadzone_min;
  this_binding.deadzone_max = deadzone_max;
  this_binding.saturation_min = saturation_min;
  this_binding.saturation_max = saturation_max;
  this_binding.centre = centre;

  if(flip) {                                                                    // invert the axis if requested
    if(this_binding.premultiply > 0) {
      this_binding.premultiply *= -1.0f;                                        // keep the premultiply, and invert it only if it's not already facing the right way
    }
  } else {
    if(this_binding.premultiply < 0) {
      this_binding.premultiply *= -1.0f;                                        // keep the premultiply, and invert it only if it's not already facing the right way
    }
  }
  this_binding.update_scales();
  this_binding.func = func;
  this_binding.enabled = true;
}
void joystick::bind_axis_half(unsigned int joystick_id, unsigned int axis, std::function<void(float)> func, bool flip) {
  /// Helper function for binding to output on a half-axis, for instance with a throttle control that ranges -1 to 1
  bind_axis(joystick_id, axis, func, flip, 0.0f, 0.0f, -1.0f, 2.0f, -1.0f);
}
void joystick::bind_axis(joystick::binding_axis const &this_binding, std::function<void(float)> func) {
  /// Helper function to load binding settings from a binding object
  bind_axis(this_binding.joystick_id,
            this_binding.axis,
            func,
            this_binding.flip,
            this_binding.deadzone_min,
            this_binding.deadzone_max,
            this_binding.saturation_min,
            this_binding.saturation_max,
            this_binding.centre);
}
void joystick::bind_button(unsigned int joystick_id, unsigned int button, actiontype action, std::function<void()> func) {
  /// Bind a function to a joystick button
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to button " << button << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  button_bindings[static_cast<unsigned int>(action)][joystick_id][button] = func;
}
void joystick::bind_button_any(unsigned int joystick_id, std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons, press event only
  for(unsigned int button = 0; button != max_button; ++button) {
    bind_button(joystick_id, button, actiontype::PRESS, func);
  }
}
void joystick::bind_button_any_all(std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons on all joysticks, press event only
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    bind_button_any(joystick_id, func);
  }
}
void joystick::bind_button(binding_button const &this_binding,
                           std::function<void()> func_press,
                           std::function<void()> func_release) {
  /// Helper function to load binding settings from a binding object
  switch(this_binding.type) {
  case binding_button::bindtype::SPECIFIC:
    if(func_press) {
      bind_button(this_binding.joystick_id, this_binding.button, actiontype::PRESS, func_press);
    }
    if(func_release) {
      bind_button(this_binding.joystick_id, this_binding.button, actiontype::RELEASE, func_release);
    }
    break;
  case binding_button::bindtype::ANY:
    if(func_press) {
      bind_button_any(this_binding.joystick_id, func_press);
    } else {
      std::cout << "InputStorm: Joystick: WARNING - requested to bind to any button with a function other than PRESS on joystick " << this_binding.joystick_id << ", this is not currently supported - create a set of specific bindings instead." << std::endl;
    }
    #ifndef NDEBUG
      if(func_release) {
        std::cout << "InputStorm: WARNING: Requested to bind a function to any button release on joystick " << this_binding.joystick_id << ", which is not possible - create a set of specific bindings instead." << std::endl;
      }
    #endif // NDEBUG
    break;
  case binding_button::bindtype::ANY_ALL:
    if(func_press) {
      bind_button_any_all(func_press);
    } else {
      std::cout << "InputStorm: Joystick: WARNING - requested to bind to any button on all joysticks with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
    }
    #ifndef NDEBUG
      if(func_release) {
        std::cout << "InputStorm: WARNING: Requested to bind a function to any button release on all joysticks, which is not possible - create a set of specific bindings instead." << std::endl;
      }
    #endif // NDEBUG
    break;
  }
}

void joystick::unbind_axis(unsigned int joystick_id, unsigned int axis) {
  /// Unbind a callback on a joystick axis
  joystick_axis_bindingtype &this_binding = axis_bindings[joystick_id][axis];
  this_binding.func = [](float value __attribute__((unused))){};                // noop
  this_binding.enabled = false;
}
void joystick::unbind_axis_any(unsigned int joystick_id) {
  /// Helper function to unbind all axes on a joystick
  for(unsigned int axis = 0; axis != max_axis; ++axis) {
    unbind_axis(joystick_id, axis);
  }
}
void joystick::unbind_axis_any_all() {
  /// Helper function to unbind all axes on all joysticks
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    unbind_axis_any(joystick_id);
  }
}
void joystick::unbind_axis(binding_axis const &this_binding) {
  /// Helper function to unbind using a binding object
  unbind_axis(this_binding.joystick_id, this_binding.axis);
}

void joystick::unbind_button(unsigned int joystick_id, unsigned int button, actiontype action) {
  /// Unbind a callback on a joystick button with a specific action
  button_bindings[static_cast<unsigned int>(action)][joystick_id][button] = []{}; // noop
}
void joystick::unbind_button_any(unsigned int joystick_id) {
  /// Helper function to unbind all buttons on a joystick, all actions
  for(unsigned int button = 0; button != max_button; ++button) {
    unbind_button(joystick_id, button, actiontype::PRESS);
    unbind_button(joystick_id, button, actiontype::RELEASE);
  }
}
void joystick::unbind_button_any_all() {
  /// Helper function to unbind all buttons with all actions on all joysticks
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    unbind_button_any(joystick_id);
  }
}
void joystick::unbind_button(binding_button const &this_binding) {
  /// Helper function to unbind using a binding object
  switch(this_binding.type) {
  case binding_button::bindtype::SPECIFIC:
    unbind_button(this_binding.joystick_id, this_binding.button, actiontype::PRESS);
    unbind_button(this_binding.joystick_id, this_binding.button, actiontype::RELEASE);
    // note: there is no REPEAT action for joystick buttons!
    break;
  case binding_button::bindtype::ANY:
    unbind_button_any(this_binding.joystick_id);
    break;
  case binding_button::bindtype::ANY_ALL:
    unbind_button_any_all();
    break;
  }
}

void joystick::execute_axis(unsigned int joystick_id, unsigned int axis, float value) const {
  /// Call the function associated with a joystick axis, having transformed the value appropriately
  joystick_axis_bindingtype const &this_binding = axis_binding_at(joystick_id, axis);
  if(!this_binding.enabled) {
    return;                                                                     // early exit in case this binding isn't in use
  }
  this_binding.execute(value);
}
void joystick::execute_button(unsigned int joystick_id, unsigned int button, actiontype action) {
  /// Call the function associated with a joystick button
  if(button_state[joystick_id][button] == action) {                             // skip repeat-calling functions when the state hasn't changed
    return;
  }
  button_state[joystick_id][button] = action;
  button_binding_at(joystick_id, button, action)();
}

void joystick::capture_axis(std::function<void(unsigned int, unsigned int, bool)> callback,
                            bool calibrate) {
  /// Capture an axis movement and return it to the given callback
  static bool calibrated = false;
  static std::array<std::array<float, max_axis>, max> initial_values;
  if(calibrate || !calibrated) {
    // read the initial values of all axes, and store them for later comparison - some axes don't default to zero, so we need to catch the biggest change
    std::cout << "InputStorm: Calibrating for capture" << std::endl;
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      int num_axes;
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
        initial_values[joystick_id][axis] = axis_data[axis];
        #ifdef DEBUG_INPUTSTORM
          std::cout << "InputStorm: DEBUG: Calibrated id " << joystick_id
                    << " axis " << axis
                    << ": " << initial_values[joystick_id][axis] << std::endl;
        #endif // DEBUG_INPUTSTORM
      }
    }
    calibrated = true;
    if(calibrate) {
      return;
    }
  }

  float constexpr const deadzone = 0.5f;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #ifdef DEBUG_INPUTSTORM
        std::stringstream ss;
        ss << "InputStorm: DEBUG: id " << joystick_id << " axis " << axis << ": ";
      #endif // DEBUG_INPUTSTORM
      float const initial_value = initial_values[joystick_id][axis];
      #ifdef DEBUG_INPUTSTORM
        bind_axis(joystick_id, axis, [callback, s = ss.str(), joystick_id, axis, initial_value](float value){
      #else
        bind_axis(joystick_id, axis, [callback, joystick_id, axis, initial_value](float value){
      #endif // DEBUG_INPUTSTORM
        float const offset = value - initial_value;
        if(offset > deadzone) {
          #ifdef DEBUG_INPUTSTORM
            std::cout << s << std::fixed << value << "(offset: pos " << offset << ")" <<  std::endl;
          #endif // DEBUG_INPUTSTORM
          callback(joystick_id, axis, false);
        } else if(offset < -deadzone) {
          #ifdef DEBUG_INPUTSTORM
            std::cout << s << std::fixed << value << "(offset: neg " << offset << ")" <<  std::endl;
          #endif // DEBUG_INPUTSTORM
          callback(joystick_id, axis, true);
        }
      });
    }
  }
}
void joystick::capture_axis(std::function<void(binding_axis const&)> callback,
                            bool calibrate) {
  /// Capture an axis movement and return it to the given callback as a binding object
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing joystick axis" << std::endl;
  #endif // DEBUG_INPUTSTORM
  static bool calibrated = false;
  static std::array<std::array<float, max_axis>, max> initial_values;
  if(calibrate || !calibrated) {
    // read the initial values of all axes, and store them for later comparison - some axes don't default to zero, so we need to catch the biggest change
    std::cout << "InputStorm: Calibrating for capture" << std::endl;
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      int num_axes;
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
        initial_values[joystick_id][axis] = axis_data[axis];
        #ifdef DEBUG_INPUTSTORM
          std::cout << "InputStorm: DEBUG: Calibrated id " << joystick_id
                    << " axis " << axis
                    << ": " << initial_values[joystick_id][axis] << std::endl;
        #endif // DEBUG_INPUTSTORM
      }
    }
    calibrated = true;
    if(calibrate) {
      return;
    }
  }

  float constexpr const deadzone = 0.5f;
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #ifdef DEBUG_INPUTSTORM
        std::stringstream ss;
        ss << "InputStorm: DEBUG: id " << joystick_id << " axis " << axis << ": ";
      #endif // DEBUG_INPUTSTORM
      float const initial_value = initial_values[joystick_id][axis];
      #ifdef DEBUG_INPUTSTORM
        bind_axis(joystick_id, axis, [callback, s = ss.str(), joystick_id, axis, initial_value](float value){
      #else
        bind_axis(joystick_id, axis, [callback, joystick_id, axis, initial_value](float value){
      #endif // DEBUG_INPUTSTORM
        float const offset = value - initial_value;
        if(offset > deadzone) {
          #ifdef DEBUG_INPUTSTORM
            std::cout << s << std::fixed << value << "(offset: pos " << offset << ")" <<  std::endl;
          #endif // DEBUG_INPUTSTORM
          callback(binding_axis{joystick_id, axis, false, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f});
        } else if(offset < -deadzone) {
          #ifdef DEBUG_INPUTSTORM
            std::cout << s << std::fixed << value << "(offset: neg " << offset << ")" <<  std::endl;
          #endif // DEBUG_INPUTSTORM
          callback(binding_axis{joystick_id, axis, true, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f});
        }
      });
    }
  }
}
void joystick::capture_button(std::function<void(unsigned int, unsigned int)> callback) {
  /// Capture a button press and return it to the given callback
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing joystick button" << std::endl;
  #endif // DEBUG_INPUTSTORM
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int button = 0; button != max_button; ++button) {
      bind_button(joystick_id, button, actiontype::RELEASE, []{});              // unbind release actions
      bind_button(joystick_id, button, actiontype::PRESS, [callback,
                                                           joystick_id,
                                                           button]{             // bind on the press action
        callback(joystick_id, button);
      });
    }
  }
}
void joystick::capture_button(std::function<void(binding_button const&)> callback) {
  /// Capture a button press and return it to the given callback as a binding object
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing joystick button to binding" << std::endl;
  #endif // DEBUG_INPUTSTORM
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int button = 0; button != max_button; ++button) {
      bind_button(joystick_id, button, actiontype::RELEASE, []{});              // unbind release actions
      bind_button(joystick_id, button, actiontype::PRESS, [callback,
                                                           joystick_id,
                                                           button]{             // bind on the press action
        callback(binding_button{joystick_id, binding_button::bindtype::SPECIFIC, button});
      });
    }
  }
}

void joystick::update_names() {
  /// Update the list of joystick names
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    if(glfwJoystickPresent(joystick_id)) {
      names[joystick_id] = glfwGetJoystickName(joystick_id);
    } else {
      names[joystick_id].clear();
    }
  }
}

void joystick::poll() {
  /// Check which joysticks are attached and poll them
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    if(!glfwJoystickPresent(joystick_id)) {
      continue;
    }
    {
      // poll the axes
      int num_axes;
      float const *const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
        execute_axis(joystick_id, axis, axis_data[axis]);
      }
    }
    {
      // poll the buttons
      int num_buttons;
      unsigned char const *const button_data = glfwGetJoystickButtons(joystick_id, &num_buttons);
      unsigned int const button_max = std::min(max_button, static_cast<unsigned int>(num_buttons));
      for(unsigned int button = 0; button != button_max; ++button) {
        execute_button(joystick_id, button, static_cast<actiontype>(button_data[button]));
      }
    }
  }
}

void joystick::draw_binding_graphs() const {
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      joystick_axis_bindingtype const &this_binding(axis_binding_at(joystick_id, axis));
      if(!this_binding.enabled) {
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
