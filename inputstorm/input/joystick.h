#ifndef INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
#define INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED

#include <vector>
#include "key.h"
#include "joystick_axis_bindingtype.h"

namespace inputstorm {
namespace input {

struct joystick {
  /// Sparse 2D / 3D arrays of joystick axes and buttons and joystick names.
  /// Each is stored together with the parameters for a transformation to
  /// allow for configurable deadzones, saturation zones and axis asymmetry.
  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
  /// Axes:
  ///   1st = GLFW joystick axis (total number is NOT known until runtime, so we set a hard limit here)
  ///   2nd = GLFW Joystick ID
  /// Buttons:
  ///   1st = GLFW action (GLFW_PRESS or GLFW_RELEASE);

  // limits
  static unsigned int constexpr max = GLFW_JOYSTICK_LAST + 1;
  static unsigned int constexpr max_axis = 8;                                   // empirically chosen based on what's available on the market
  static unsigned int constexpr max_button = 60;                                // empirically chosen based on what's available on the market
  static unsigned int constexpr max_button_action = static_cast<int>(key::actiontype::REPEAT); // there's no repeat action for joystick buttons

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
  joystick_axis_bindingtype &axis_binding_at(      unsigned int joystick, unsigned int axis) __attribute__((__const__));
  joystick_axis_bindingtype const &axis_binding_at(unsigned int joystick, unsigned int axis) const __attribute__((__const__));
  std::function<void()> &button_binding_at(        unsigned int joystick, unsigned int button, key::actiontype action = key::actiontype::PRESS) __attribute__((__const__));

public:
  std::vector<unsigned int> get_connected_ids() const;
  std::string get_name(unsigned int joystick_id) const;

  void bind_axis(      unsigned int joystick, unsigned int axis, std::function<void(float)> func, bool flip = false, float deadzone_min = 0.0f, float deadzone_max = 0.0f, float saturation_min = -1.0f, float saturation_max = 1.0f, float centre = 0.0f);
  void bind_axis_half( unsigned int joystick, unsigned int axis, std::function<void(float)> func, bool flip = false);
  void bind_button(    unsigned int joystick, unsigned int button, key::actiontype action, std::function<void()> func);
  void bind_button_any(unsigned int joystick, std::function<void()> func);
  void bind_button_any_all(std::function<void()> func);

  void unbind_axis(      unsigned int joystick, unsigned int axis);
  void unbind_button(    unsigned int joystick, unsigned int button, key::actiontype action);
  void unbind_button_any(unsigned int joystick);
  void unbind_button_any_all();

  void execute_axis(  unsigned int joystick, unsigned int axis, float value = 0.0f);
  void execute_button(unsigned int joystick, unsigned int button, key::actiontype action = key::actiontype::PRESS);

  void update_names();
  void poll();

  void draw_binding_graphs() const;
};

}
}

#endif // INPUTSTORM_INPUT_JOYSTICK_H_INCLUDED
