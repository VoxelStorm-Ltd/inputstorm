#include "joystick.h"
#include <iostream>

namespace inputstorm {
namespace input {

unsigned int constexpr joystick::max;
unsigned int constexpr joystick::max_axis;
unsigned int constexpr joystick::max_button;
unsigned int constexpr joystick::max_button_action;

void joystick::init() {
  /// assign a safe default function to all joystick axes
  for(unsigned int joystick = 0; joystick != max; ++joystick) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #ifdef DEBUG_INPUTSTORM
        std::stringstream ss;
        ss << "InputStorm: DEBUG: unbound joystick function called on axis " << axis;
        if(joystick != 0) {
          ss << " on joystick " << joystick;
        }
        ss << " value ";
        bind_axis(joystick, axis, [s = ss.str()](float value){
          std::cout << s << std::fixed << value <<  std::endl;
        });
      #else
        bind_axis(joystick, axis, [](float value __attribute__((__unused__))){});  // default to noop
        axis_binding_at(joystick, axis).enabled = false;
      #endif // DEBUG_INPUTSTORM
    }
  }
  /// assign a safe default function to all joystick buttons
  for(key::action action = key::action::RELEASE;
      action != static_cast<key::action>(max_button_action);
      action = static_cast<key::action>(static_cast<int>(action) + 1)) {
    for(unsigned int joystick = 0; joystick != max; ++joystick) {
      for(unsigned int button = 0; button != max_button; ++button) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound joystick function called on button " << button;
          if(joystick != 0) {
            ss << " on joystick " << joystick;
          }
          ss << " action " << get_keyaction_name(action);
          if(action == action::PRESS) {
            bind_button(joystick, button, action, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind_button(joystick, button, action, []{});
          }
        #else
          bind_button(joystick, button, action, []{});                 // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }

  // all previous states are released
  for(unsigned int joystick = 0; joystick != max; ++joystick) {
    button_state[joystick].fill(key::action::RELEASE);
  }

  // enable all the joysticks by default
  enabled.fill(true);
  update_names();

  // report status
  std::cout << "InputStorm: Joystick axis bindings:   " << sizeof(axis_bindings) / 1024 << "KB" << std::endl;
  std::cout << "InputStorm: Joystick button bindings: " << sizeof(button_bindings) / 1024 << "KB" << std::endl;
  for(unsigned int joystick = 0; joystick != max; ++joystick) {
    if(glfwJoystickPresent(joystick)) {
      std::cout << "InputStorm: Joystick " << joystick << ": " << names[joystick] << std::endl;
    }
  }
}

joystick_axis_bindingtype &joystick::axis_binding_at(unsigned int joystick, unsigned int axis) {
  /// Accessor for the joystick axis structure sparse arrays
  return axis_bindings[axis][joystick];
}
joystick_axis_bindingtype const &joystick::axis_binding_at(unsigned int joystick, unsigned int axis) const {
  /// Const accessor
  return axis_bindings[axis][joystick];
}
std::function<void()> &joystick::button_binding_at(unsigned int joystick, unsigned int button, key::action action) {
  /// Accessor for the joystick button function sparse arrays
  return button_bindings[static_cast<unsigned int>(action)][joystick][button];
}

void joystick::bind_axis(unsigned int joystick,
                         unsigned int axis, std::function<void(float)> func,
                         bool flip,
                         float deadzone_min,
                         float deadzone_max,
                         float saturation_min,
                         float saturation_max,
                         float centre) {
  /// Bind a function to a joystick axis, with the specified parameters
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to axis " << axis << " on joystick " << joystick << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  joystick_axis_bindingtype &binding = axis_binding_at(joystick, axis);
  binding.deadzone_min = deadzone_min;
  binding.deadzone_max = deadzone_max;
  binding.saturation_min = saturation_min;
  binding.saturation_max = saturation_max;
  binding.centre = centre;
  if(flip) {                                                                    // invert the axis if requested
    binding.premultiply *= -1.0f;
  }
  binding.update_scales();
  binding.func = func;
  binding.enabled = true;
}
void joystick::bind_axis_half(unsigned int joystick, unsigned int axis, std::function<void(float)> func, bool flip) {
  /// Helper function for binding to output on a half-axis, for instance with a throttle control that ranges -1 to 1
  bind_axis(joystick, axis, func, flip, 0.0f, 0.0f, -1.0f, 2.0f, -1.0f);
}
void joystick::bind_button(unsigned int joystick, unsigned int button, key::action action, std::function<void()> func) {
  /// Bind a function to a joystick button
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to button " << button << " on joystick " << joystick << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  button_binding_at(joystick, button, action) = func;
}
void joystick::bind_button_any(unsigned int joystick, std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons, press event only
  for(unsigned int button = 0; button != max_button; ++button) {
    bind_button(joystick, button, key::action::PRESS, func);
  }
}
void joystick::bind_button_any_all(std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons on all joysticks, press event only
  for(unsigned int joystick = 0; joystick != max; ++joystick) {
    bind_button_any(joystick, func);
  }
}

void joystick::execute_axis(unsigned int joystick, unsigned int axis, float value) {
  /// Call the function associated with a joystick axis, having transformed the value appropriately
  joystick_axis_bindingtype const &binding = axis_binding_at(joystick, axis);
  if(!binding.enabled) {
    return;                                                                     // early exit in case this binding isn't in use
  }
  binding.execute(value);
}
void joystick::execute_button(unsigned int joystick, unsigned int button, key::action action) {
  /// Call the function associated with a joystick button
  if(button_state[joystick][button] == action) {                                // skip repeat-calling functions when the state hasn't changed
    return;
  }
  button_state[joystick][button] = action;
  button_binding_at(joystick, button, action)();
}

void joystick::update_names() {
  /// Update the list of joystick names
  for(unsigned int joystick = 0; joystick != max; ++joystick) {
    if(glfwJoystickPresent(joystick)) {
      names[joystick] = glfwGetJoystickName(joystick);
    } else {
      names[joystick].clear();
    }
  }
}

void joystick::poll() {
  /// Check which joysticks are attached and poll them
  for(unsigned int joystick = 0; joystick != max; ++joystick) {
    if(!glfwJoystickPresent(joystick)) {
      continue;
    }
    {
      // poll the axes
      int num_axes;
      float const* const axis_data = glfwGetJoystickAxes(joystick, &num_axes);
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
        execute_axis(joystick, axis, axis_data[axis]);
      }
    }
    {
      // poll the buttons
      int num_buttons;
      unsigned char const* const button_data = glfwGetJoystickButtons(joystick, &num_buttons);
      unsigned int const button_max = std::min(max_button, static_cast<unsigned int>(num_buttons));
      for(unsigned int button = 0; button != button_max; ++button) {
        execute_button(joystick, button, static_cast<key::action>(button_data[button]));
      }
    }
  }
}

void joystick::draw_binding_graphs() const {
  for(unsigned int joystick = 0; joystick != max; ++joystick) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      joystick_axis_bindingtype const &binding(axis_binding_at(joystick, axis));
      if(!binding.enabled) {
        continue;
      }
      std::cout << "InputStorm: Transform function on joystick " << joystick << " axis " << axis << ":" << std::endl;
      binding.draw_graph_console();
    }
  }
}

}
}
