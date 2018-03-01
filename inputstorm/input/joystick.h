#ifndef INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
#define INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "joystick_axis_bindingtype.h"

namespace inputstorm::input {

class joystick {
public:
  /// Sparse 2D / 3D arrays of joystick axes and buttons and joystick names.
  /// Each is stored together with the parameters for a transformation to
  /// allow for configurable deadzones, saturation zones and axis asymmetry.
  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
  /// Axes:
  ///   1st = GLFW joystick axis (total number is NOT known until runtime, so we set a hard limit here)
  ///   2nd = GLFW Joystick ID
  /// Buttons:
  ///   1st = GLFW action (GLFW_PRESS or GLFW_RELEASE);

  enum class actiontype : int {
    RELEASE = GLFW_RELEASE,
    PRESS   = GLFW_PRESS,
    // array bounds
    BEGIN = RELEASE,
    LAST = PRESS,
    END = LAST + 1
  };
  struct binding_axis {
    /// Convenience struct for storing and passing all parameters that make up an axis binding
    unsigned int joystick_id;
    unsigned int axis;
    bool flip;
    float deadzone_min;
    float deadzone_max;
    float saturation_min;
    float saturation_max;
    float centre;
  };
  struct binding_button {
    /// Convenience struct for storing and passing all parameters that make up a button binding
    unsigned int joystick_id;
    enum class bindtype : char {
      SPECIFIC,                                                                 // button binding with an action (press or release)
      ANY,                                                                      // button binding with any action (press or release)
      ANY_ALL                                                                   // button binding on any joystick with any action
    } type;
    unsigned int button;                                                        // unused if bindtype is ANY or ANY_ALL

    bool operator==(const binding_button &rhs) const {
      /// Equality operator
      // two formulations with the same effect - benchmark to see which performs best in each specific use case
      #ifdef INPUTSTORM_EQUALITY_COMPARISON_SWITCH
        switch(type) {
        case bindtype::SPECIFIC:
          switch(rhs.type) {
          case bindtype::SPECIFIC:
            return (joystick_id == rhs.joystick_id) && (button == rhs.button);
          case bindtype::ANY:
            return joystick_id == rhs.joystick_id;
          case bindtype::ANY_ALL:
            return true;
          }
          break;
        case bindtype::ANY:
          switch(rhs.type) {
          case bindtype::SPECIFIC:
          case bindtype::ANY:
            return joystick_id == rhs.joystick_id;
          case bindtype::ANY_ALL:
            return true;
          }
          break;
        case bindtype::ANY_ALL:
          return true;
        default:
          return false;
        }
      #else
        if(type == bindtype::ANY_ALL || rhs.type == bindtype::ANY_ALL) {
          return true;
        } else if(type == bindtype::ANY || rhs.type == bindtype::ANY) {
          return joystick_id == rhs.joystick_id;
        } else {
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

  // data
private:
  std::array<bool, max> enabled;                                                // whether each joystick is enabled or not
  std::array<std::string, max> names;                                           // cached human-readable names of joysticks
  std::array<std::array<joystick_axis_bindingtype, max_axis>, max> axis_bindings; // callback functions for joystick axes
  std::array<std::array<actiontype, max_button>, max> button_state;             // last pressed or released states
  std::array<std::array<std::array<std::function<void()>, max_button>, max>, static_cast<int>(actiontype::END)> button_bindings; // callback functions for joystick buttons

public:
  void init();

private:
  joystick_axis_bindingtype const &axis_binding_at(unsigned int joystick,
                                                   unsigned int axis) const __attribute__((__const__));
  std::function<void()> const &button_binding_at(  unsigned int joystick,
                                                   unsigned int button,
                                                   actiontype action = actiontype::PRESS) const __attribute__((__const__));

public:
  std::vector<unsigned int> get_connected_ids() const;
  std::string const &get_name(unsigned int joystick_id) const __attribute__((__const__));
  static std::string get_actiontype_name(actiontype action);

  void bind_axis(          unsigned int joystick,
                           unsigned int axis,
                           std::function<void(float)> func,
                           bool flip = false,
                           float deadzone_min = 0.0f,
                           float deadzone_max = 0.0f,
                           float saturation_min = -1.0f,
                           float saturation_max = 1.0f,
                           float centre = 0.0f);
  void bind_axis_half(     unsigned int joystick,
                           unsigned int axis,
                           std::function<void(float)> func,
                           bool flip = false);
  void bind_axis(          binding_axis const &this_binding,
                           std::function<void(float)> func);
  void bind_button(        unsigned int joystick,
                           unsigned int button,
                           actiontype action,
                           std::function<void()> func);
  void bind_button_any(    unsigned int joystick,
                           std::function<void()> func);
  void bind_button_any_all(std::function<void()> func);
  void bind_button(        binding_button const &this_binding,
                           std::function<void()> func_press,
                           std::function<void()> func_release = nullptr);

  void unbind_axis(    unsigned int joystick,
                       unsigned int axis);
  void unbind_axis_any(unsigned int joystick);
  void unbind_axis_any_all();
  void unbind_axis(binding_axis const &this_binding);
  void unbind_button(    unsigned int joystick,
                         unsigned int button,
                         actiontype action);
  void unbind_button_any(unsigned int joystick);
  void unbind_button_any_all();
  void unbind_button(binding_button const &this_binding);

  void execute_axis(  unsigned int joystick,
                      unsigned int axis,
                      float value = 0.0f) const;
  void execute_button(unsigned int joystick,
                      unsigned int button,
                      actiontype action = actiontype::PRESS);

  void capture_axis(  std::function<void(unsigned int, unsigned int, bool)> callback,
                      bool calibrate = false);
  void capture_axis(  std::function<void(binding_axis const&             )> callback,
                      bool calibrate = false);
  void capture_button(std::function<void(unsigned int, unsigned int      )> callback);
  void capture_button(std::function<void(binding_button const&           )> callback);

  void update_names();
  void poll();

  void draw_binding_graphs() const;
};

/// Helper functions to allow joystick::actiontype to be iterated
inline joystick::actiontype operator++(joystick::actiontype &i) {
  return i = static_cast<joystick::actiontype>(std::underlying_type<joystick::actiontype>::type(i) + 1);
}
inline joystick::actiontype operator*(joystick::actiontype c) {
  return c;
}
inline joystick::actiontype begin(joystick::actiontype thistype [[maybe_unused]]) {
  return joystick::actiontype::BEGIN;
}
inline joystick::actiontype end(joystick::actiontype thistype [[maybe_unused]]) {
  return joystick::actiontype::END;
}

inline size_t hash_value(joystick::binding_button const &this_binding) {
  /// Forward to the binding's hash function
  return this_binding.hash_value();
}

}

namespace std {

template<>
struct hash<inputstorm::input::joystick::binding_button> {
  /// Forward the binding's hash function for std::hash specialisation
  size_t operator()(inputstorm::input::joystick::binding_button const &this_binding) const {
    return this_binding.hash_value();
  }
};

}

#endif // INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
