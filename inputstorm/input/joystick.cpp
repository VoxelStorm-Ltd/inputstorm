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
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      #ifdef DEBUG_INPUTSTORM
        std::stringstream ss;
        ss << "InputStorm: DEBUG: unbound joystick function called on axis " << axis;
        if(joystick != 0) {
          ss << " on joystick " << joystick_id;
        }
        ss << " value ";
        bind_axis(joystick_id, axis, [s = ss.str()](float value){
          std::cout << s << std::fixed << value <<  std::endl;
        });
      #else
        bind_axis(joystick_id, axis, [](float value __attribute__((__unused__))){});  // default to noop
        axis_binding_at(joystick_id, axis).enabled = false;
      #endif // DEBUG_INPUTSTORM
    }
  }
  /// assign a safe default function to all joystick buttons
  for(key::action action = key::action::RELEASE;
      action != static_cast<key::action>(max_button_action);
      action = static_cast<key::action>(static_cast<int>(action) + 1)) {
    for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
      for(unsigned int button = 0; button != max_button; ++button) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound joystick function called on button " << button;
          if(joystick_id != 0) {
            ss << " on joystick " << joystick_id;
          }
          ss << " action " << get_keyaction_name(action);
          if(action == action::PRESS) {
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
    button_state[joystick_id].fill(key::action::RELEASE);
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

joystick_axis_bindingtype &joystick::axis_binding_at(unsigned int joystick_id, unsigned int axis) {
  /// Accessor for the joystick axis structure sparse arrays
  return axis_bindings[axis][joystick_id];
}
joystick_axis_bindingtype const &joystick::axis_binding_at(unsigned int joystick_id, unsigned int axis) const {
  /// Const accessor
  return axis_bindings[axis][joystick_id];
}
std::function<void()> &joystick::button_binding_at(unsigned int joystick_id, unsigned int button, key::action action) {
  /// Accessor for the joystick button function sparse arrays
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
std::string joystick::get_name(unsigned int joystick_id) const {
  /// Return the name of a specific joystick ID
  return names[joystick_id];
}

void joystick::bind_axis(unsigned int joystick_id,
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
      std::cout << "InputStorm: WARNING: Binding a null function to axis " << axis << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  joystick_axis_bindingtype &binding = axis_binding_at(joystick_id, axis);
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
void joystick::bind_axis_half(unsigned int joystick_id, unsigned int axis, std::function<void(float)> func, bool flip) {
  /// Helper function for binding to output on a half-axis, for instance with a throttle control that ranges -1 to 1
  bind_axis(joystick_id, axis, func, flip, 0.0f, 0.0f, -1.0f, 2.0f, -1.0f);
}
void joystick::bind_button(unsigned int joystick_id, unsigned int button, key::action action, std::function<void()> func) {
  /// Bind a function to a joystick button
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to button " << button << " on joystick " << joystick_id << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  button_binding_at(joystick_id, button, action) = func;
}
void joystick::bind_button_any(unsigned int joystick_id, std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons, press event only
  for(unsigned int button = 0; button != max_button; ++button) {
    bind_button(joystick_id, button, key::action::PRESS, func);
  }
}
void joystick::bind_button_any_all(std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons on all joysticks, press event only
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    bind_button_any(joystick_id, func);
  }
}

void joystick::unbind_axis(unsigned int joystick_id, unsigned int axis) {
  joystick_axis_bindingtype &binding = axis_binding_at(joystick_id, axis);
  binding.func = [](float value __attribute__((unused))){};                     // noop
  binding.enabled = false;
}
void joystick::unbind_button(unsigned int joystick_id, unsigned int button, key::action action) {
  /// Unbind a callback on a joystick button with a specific action
  button_binding_at(joystick_id, button, action) = []{};                        // noop
}
void joystick::unbind_button_any(unsigned int joystick_id) {
  /// Helper function to unbind all buttons on a joystick, all actions
  for(unsigned int button = 0; button != max_button; ++button) {
    unbind_button(joystick_id, button, key::action::PRESS);
    unbind_button(joystick_id, button, key::action::RELEASE);
    unbind_button(joystick_id, button, key::action::REPEAT);
  }
}
void joystick::unbind_button_any_all() {
  /// Helper function to unbind all buttons with all actions on all joysticks
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    unbind_button_any(joystick_id);
  }
}

void joystick::execute_axis(unsigned int joystick_id, unsigned int axis, float value) {
  /// Call the function associated with a joystick axis, having transformed the value appropriately
  joystick_axis_bindingtype const &binding = axis_binding_at(joystick_id, axis);
  if(!binding.enabled) {
    return;                                                                     // early exit in case this binding isn't in use
  }
  binding.execute(value);
}
void joystick::execute_button(unsigned int joystick_id, unsigned int button, key::action action) {
  /// Call the function associated with a joystick button
  if(button_state[joystick_id][button] == action) {                             // skip repeat-calling functions when the state hasn't changed
    return;
  }
  button_state[joystick_id][button] = action;
  button_binding_at(joystick_id, button, action)();
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
      float const* const axis_data = glfwGetJoystickAxes(joystick_id, &num_axes);
      unsigned int const axis_max = std::min(max_axis, static_cast<unsigned int>(num_axes));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
        execute_axis(joystick_id, axis, axis_data[axis]);
      }
    }
    {
      // poll the buttons
      int num_buttons;
      unsigned char const* const button_data = glfwGetJoystickButtons(joystick_id, &num_buttons);
      unsigned int const button_max = std::min(max_button, static_cast<unsigned int>(num_buttons));
      for(unsigned int button = 0; button != button_max; ++button) {
        execute_button(joystick_id, button, static_cast<key::action>(button_data[button]));
      }
    }
  }
}

void joystick::draw_binding_graphs() const {
  for(unsigned int joystick_id = 0; joystick_id != max; ++joystick_id) {
    for(unsigned int axis = 0; axis != max_axis; ++axis) {
      joystick_axis_bindingtype const &binding(axis_binding_at(joystick_id, axis));
      if(!binding.enabled) {
        continue;
      }
      std::cout << "InputStorm: Transform function on joystick " << joystick_id << " axis " << axis << ":" << std::endl;
      binding.draw_graph_console();
    }
  }
}

}
}
