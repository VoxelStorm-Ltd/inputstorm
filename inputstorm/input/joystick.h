            return joystick_id == rhs.joystick_id;
          case bindtype::ANY_ALL:
            return true;
#ifndef INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
          }
#define INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
          break;

        case bindtype::ANY:
#include <vector>
          switch(rhs.type) {
#include "key.h"
          case bindtype::SPECIFIC:
#include "joystick_axis_bindingtype.h"
          case bindtype::ANY:

            return joystick_id == rhs.joystick_id;
namespace inputstorm {
          case bindtype::ANY_ALL:
namespace input {
            return true;

          }
struct joystick {
          break;
  /// Sparse 2D / 3D arrays of joystick axes and buttons and joystick names.
        case bindtype::ANY_ALL:
          return true;
  /// Each is stored together with the parameters for a transformation to
        }
  /// allow for configurable deadzones, saturation zones and axis asymmetry.
      #else
  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
        if(type == bindtype::ANY_ALL || rhs.type == bindtype::ANY_ALL) {
  /// Axes:
          return true;
  ///   1st = GLFW joystick axis (total number is NOT known until runtime, so we set a hard limit here)
        } else if(type == bindtype::ANY || rhs.type == bindtype::ANY) {
  ///   2nd = GLFW Joystick ID
          return joystick_id == rhs.joystick_id;
  /// Buttons:
        } else {
  ///   1st = GLFW action (GLFW_PRESS or GLFW_RELEASE);
          return (joystick_id == rhs.joystick_id) && (button == rhs.button);

        }
      #endif // INPUTSTORM_EQUALITY_COMPARISON_SWITCH
    }

    size_t hash_value() const {
      /// Hash function to return a unique hash for each binding
      return max_button * joystick_id +
             button;
    }
  };

  // limits
  static unsigned int constexpr const max = GLFW_JOYSTICK_LAST + 1;
  static unsigned int constexpr const max_axis = 8;                             // empirically chosen based on what's available on the market
  static unsigned int constexpr const max_button = 60;                          // empirically chosen based on what's available on the market
  static unsigned int constexpr const max_button_action = static_cast<int>(key::actiontype::REPEAT); // there's no repeat action for joystick buttons

  // data
private:
  std::array<bool, max> enabled;                                                // whether each joystick is enabled or not
  std::array<std::string, max> names;                                           // cached human-readable names of joysticks
  std::array<std::array<joystick_axis_bindingtype, max_axis>, max> axis_bindings; // callback functions for joystick axes
  std::array<std::array<key::actiontype, max_button>, max> button_state;        // last pressed or released states
  std::array<std::array<std::array<std::function<void()>, max_button>, max>, max_button_action> button_bindings; // callback functions for joystick buttons

public:
  void init();

private:
  joystick_axis_bindingtype const &axis_binding_at(unsigned int joystick,
                                                   unsigned int axis) const __attribute__((__const__));
  std::function<void()> &button_binding_at(        unsigned int joystick,
                                                   unsigned int button,
                                                   key::actiontype action = key::actiontype::PRESS) __attribute__((__const__));

public:
  std::vector<unsigned int> get_connected_ids() const;
  std::string get_name(unsigned int joystick_id) const;

  void bind_axis(          unsigned int joystick,
                           unsigned int axis, std::function<void(float)> func,
                           bool flip = false,
                           float deadzone_min = 0.0f,
                           float deadzone_max = 0.0f,
                           float saturation_min = -1.0f,
                           float saturation_max = 1.0f,
                           float centre = 0.0f);
  void bind_axis_half(     unsigned int joystick,
                           unsigned int axis, std::function<void(float)> func,
                           bool flip = false);
  void bind_axis(          binding_axis const &this_binding,
                           std::function<void(float)> func);
  void bind_button(        unsigned int joystick,
                           unsigned int button,
                           key::actiontype action,
                           std::function<void()> func);
  void bind_button_any(    unsigned int joystick,
                           std::function<void()> func);
  void bind_button_any_all(std::function<void()> func);
  void bind_button(        binding_button const &this_binding,
                           std::function<void()> func_press,
                           std::function<void()> func_release = nullptr,
                           std::function<void()> func_repeat = nullptr);

  void unbind_axis(    unsigned int joystick, unsigned int axis);
  void unbind_axis_any(unsigned int joystick);
  void unbind_axis_any_all();
  void unbind_axis(binding_axis const &this_binding);
  void unbind_button(    unsigned int joystick,
                         unsigned int button, key::actiontype action);
  void unbind_button_any(unsigned int joystick);
  void unbind_button_any_all();
  void unbind_button(binding_button const &this_binding);

  void execute_axis(  unsigned int joystick,
                      unsigned int axis,
                      float value = 0.0f) const;
  void execute_button(unsigned int joystick,
                      unsigned int button,
                      key::actiontype action = key::actiontype::PRESS);

  void capture_axis(  std::function<void(unsigned int, unsigned int, bool)> callback,
                      bool calibrate = false);
  void capture_button(std::function<void(unsigned int, unsigned int      )> callback);

  void update_names();
  void poll();

  void draw_binding_graphs() const;
};

inline size_t hash_value(joystick::binding_button const &this_binding) {
  /// Forward to the binding's hash function
  return this_binding.hash_value();
}

}
}

#endif // INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
