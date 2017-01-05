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
#ifndef INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
        }
#define INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
      #endif // INPUTSTORM_EQUALITY_COMPARISON_SWITCH

    }
#include <vector>

#include <GL/glew.h>
    size_t hash_value() const {
#include <GLFW/glfw3.h>
      /// Hash function to return a unique hash for each binding
#include "joystick_axis_bindingtype.h"
      return max_button * joystick_id +

             button;
namespace inputstorm {
    }
namespace input {
  };


class joystick {
  // limits
public:
  static unsigned int constexpr const max = GLFW_JOYSTICK_LAST + 1;
  /// Sparse 2D / 3D arrays of joystick axes and buttons and joystick names.
  static unsigned int constexpr const max_axis = 8;                             // empirically chosen based on what's available on the market
  /// Each is stored together with the parameters for a transformation to
  static unsigned int constexpr const max_button = 60;                          // empirically chosen based on what's available on the market
  /// allow for configurable deadzones, saturation zones and axis asymmetry.

  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
  // data
  /// Axes:
private:
  ///   1st = GLFW joystick axis (total number is NOT known until runtime, so we set a hard limit here)
  ///   2nd = GLFW Joystick ID
  std::array<bool, max> enabled;                                                // whether each joystick is enabled or not
  /// Buttons:
  std::array<std::string, max> names;                                           // cached human-readable names of joysticks
  ///   1st = GLFW action (GLFW_PRESS or GLFW_RELEASE);
  std::array<std::array<joystick_axis_bindingtype, max_axis>, max> axis_bindings; // callback functions for joystick axes

  std::array<std::array<actiontype, max_button>, max> button_state;             // last pressed or released states
  enum class actiontype : int {
  std::array<std::array<std::array<std::function<void()>, max_button>, max>, static_cast<int>(actiontype::END)> button_bindings; // callback functions for joystick buttons
    RELEASE = GLFW_RELEASE,

    PRESS   = GLFW_PRESS,
public:
    // array bounds
  void init();
    BEGIN = RELEASE,

    LAST = PRESS,
private:
    END = LAST + 1
  };
  joystick_axis_bindingtype const &axis_binding_at(unsigned int joystick,
  struct binding_axis {
                                                   unsigned int axis) const __attribute__((__const__));
    /// Convenience struct for storing and passing all parameters that make up an axis binding
  std::function<void()> const &button_binding_at(  unsigned int joystick,
    unsigned int joystick_id;
                                                   unsigned int button,
    unsigned int axis;
                                                   actiontype action = actiontype::PRESS) const __attribute__((__const__));
    bool flip;

    float deadzone_min;
public:
    float deadzone_max;
  std::vector<unsigned int> get_connected_ids() const;
    float saturation_min;
  std::string const &get_name(unsigned int joystick_id) const __attribute__((__const__));
    float saturation_max;
  static std::string get_actiontype_name(actiontype action);
    float centre;

  };
  void bind_axis(          unsigned int joystick,
  struct binding_button {
                           unsigned int axis,
    /// Convenience struct for storing and passing all parameters that make up a button binding
    unsigned int joystick_id;
                           std::function<void(float)> func,
    enum class bindtype : char {
                           bool flip = false,
      SPECIFIC,                                                                 // button binding with an action (press or release)
                           float deadzone_min = 0.0f,
                           float deadzone_max = 0.0f,
      ANY,                                                                      // button binding with any action (press or release)
                           float saturation_min = -1.0f,
      ANY_ALL                                                                   // button binding on any joystick with any action
                           float saturation_max = 1.0f,
    } type;
                           float centre = 0.0f);
    unsigned int button;                                                        // unused if bindtype is ANY or ANY_ALL
  void bind_axis_half(     unsigned int joystick,

                           unsigned int axis,
    bool operator==(const binding_button &rhs) const {
      /// Equality operator
                           std::function<void(float)> func,
      // two formulations with the same effect - benchmark to see which performs best in each specific use case
                           bool flip = false);
      #ifdef INPUTSTORM_EQUALITY_COMPARISON_SWITCH
  void bind_axis(          binding_axis const &this_binding,
        switch(type) {
                           std::function<void(float)> func);
        case bindtype::SPECIFIC:
  void bind_button(        unsigned int joystick,
          switch(rhs.type) {
                           unsigned int button,
          case bindtype::SPECIFIC:
                           actiontype action,
            return (joystick_id == rhs.joystick_id) && (button == rhs.button);
                           std::function<void()> func);
          case bindtype::ANY:
  void bind_button_any(    unsigned int joystick,
            return joystick_id == rhs.joystick_id;
                           std::function<void()> func);
          case bindtype::ANY_ALL:
  void bind_button_any_all(std::function<void()> func);
            return true;
  void bind_button(        binding_button const &this_binding,
          }
                           std::function<void()> func_press,
          break;
        case bindtype::ANY:
                           std::function<void()> func_release = nullptr);
          switch(rhs.type) {

          case bindtype::SPECIFIC:
  void unbind_axis(    unsigned int joystick,
          case bindtype::ANY:
                       unsigned int axis);
            return joystick_id == rhs.joystick_id;
  void unbind_axis_any(unsigned int joystick);
          case bindtype::ANY_ALL:
  void unbind_axis_any_all();
            return true;
  void unbind_axis(binding_axis const &this_binding);
          }
  void unbind_button(    unsigned int joystick,
          break;
                         unsigned int button,
        case bindtype::ANY_ALL:
                         actiontype action);
          return true;
  void unbind_button_any(unsigned int joystick);
        default:
  void unbind_button_any_all();
          return false;
  void unbind_button(binding_button const &this_binding);
        }

      #else
  void execute_axis(  unsigned int joystick,
        if(type == bindtype::ANY_ALL || rhs.type == bindtype::ANY_ALL) {
                      unsigned int axis,
          return true;
                      float value = 0.0f) const;
        } else if(type == bindtype::ANY || rhs.type == bindtype::ANY) {
  void execute_button(unsigned int joystick,
          return joystick_id == rhs.joystick_id;
                      unsigned int button,
        } else {
                      actiontype action = actiontype::PRESS);
          return (joystick_id == rhs.joystick_id) && (button == rhs.button);

        }
      #endif // INPUTSTORM_EQUALITY_COMPARISON_SWITCH
  void capture_axis(  std::function<void(unsigned int, unsigned int, bool)> callback,
    }
                      bool calibrate = false);

  void capture_axis(  std::function<void(binding_axis const&             )> callback,
    size_t hash_value() const {
                      bool calibrate = false);
      /// Hash function to return a unique hash for each binding
  void capture_button(std::function<void(unsigned int, unsigned int      )> callback);
      return max_button * joystick_id +
  void capture_button(std::function<void(binding_button const&           )> callback);
             button;

    }
  void update_names();
  };
  void poll();


  // limits
  void draw_binding_graphs() const;
  static unsigned int constexpr const max = GLFW_JOYSTICK_LAST + 1;
};
  static unsigned int constexpr const max_axis = 8;                             // empirically chosen based on what's available on the market

  static unsigned int constexpr const max_button = 60;                          // empirically chosen based on what's available on the market
/// Helper functions to allow joystick::actiontype to be iterated

inline joystick::actiontype operator++(joystick::actiontype &i) {
  // data
  return i = static_cast<joystick::actiontype>(std::underlying_type<joystick::actiontype>::type(i) + 1);
private:
}
  std::array<bool, max> enabled;                                                // whether each joystick is enabled or not
inline joystick::actiontype operator*(joystick::actiontype c) {
  std::array<std::string, max> names;                                           // cached human-readable names of joysticks
  return c;
  std::array<std::array<joystick_axis_bindingtype, max_axis>, max> axis_bindings; // callback functions for joystick axes
}
  std::array<std::array<actiontype, max_button>, max> button_state;             // last pressed or released states
inline joystick::actiontype begin(joystick::actiontype thistype __attribute__((__unused__))) {
  std::array<std::array<std::array<std::function<void()>, max_button>, max>, static_cast<int>(actiontype::END)> button_bindings; // callback functions for joystick buttons
  return joystick::actiontype::BEGIN;

}
public:
  void init();
inline joystick::actiontype end(joystick::actiontype thistype __attribute__((__unused__))) {

  return joystick::actiontype::END;
private:
}
  joystick_axis_bindingtype const &axis_binding_at(unsigned int joystick,

                                                   unsigned int axis) const __attribute__((__const__));
inline size_t hash_value(joystick::binding_button const &this_binding) {
  std::function<void()> const &button_binding_at(  unsigned int joystick,
  /// Forward to the binding's hash function
                                                   unsigned int button,
  return this_binding.hash_value();
                                                   actiontype action = actiontype::PRESS) const __attribute__((__const__));
}


public:
}
  std::vector<unsigned int> get_connected_ids() const;
}
  std::string const &get_name(unsigned int joystick_id) const __attribute__((__const__));

  static std::string get_actiontype_name(actiontype action);
#endif // INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED

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
inline joystick::actiontype begin(joystick::actiontype thistype __attribute__((__unused__))) {
  return joystick::actiontype::BEGIN;
}
inline joystick::actiontype end(joystick::actiontype thistype __attribute__((__unused__))) {
  return joystick::actiontype::END;
}

inline size_t hash_value(joystick::binding_button const &this_binding) {
  /// Forward to the binding's hash function
  return this_binding.hash_value();
}

}
}

#endif // INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
