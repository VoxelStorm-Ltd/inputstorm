#ifndef INPUTSTORM_MANAGER_H_INCLUDED
#define INPUTSTORM_MANAGER_H_INCLUDED

#include <array>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vmath.h>

namespace inputstorm {

using keytype = int;
using mousebuttontype = int;
enum class keyactiontype : int {
  RELEASE = GLFW_RELEASE,
  PRESS   = GLFW_PRESS,
  REPEAT  = GLFW_REPEAT,
  // array bounds
  LAST = REPEAT,
  END = LAST + 1
};
enum class keymodtype : int {
  NONE                      = 0,
  // shift
  SHIFT                     =                                                    GLFW_MOD_SHIFT,
  // control
  CONTROL                   =                                 GLFW_MOD_CONTROL                 ,
  SHIFT_CONTROL             =                                 GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,
  // alt
  ALT                       =                  GLFW_MOD_ALT                                    ,
  SHIFT_ALT                 =                  GLFW_MOD_ALT |                    GLFW_MOD_SHIFT,
  CONTROL_ALT               =                  GLFW_MOD_ALT | GLFW_MOD_CONTROL                 ,
  SHIFT_CONTROL_ALT         =                  GLFW_MOD_ALT | GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,
  // super
  SUPER                     = GLFW_MOD_SUPER                                                   ,
  SHIFT_SUPER               = GLFW_MOD_SUPER |                                   GLFW_MOD_SHIFT,
  CONTROL_SUPER             = GLFW_MOD_SUPER |                GLFW_MOD_CONTROL                 ,
  SHIFT_CONTROL_SUPER       = GLFW_MOD_SUPER |                GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,
  ALT_SUPER                 = GLFW_MOD_SUPER | GLFW_MOD_ALT                                    ,
  SHIFT_ALT_SUPER           = GLFW_MOD_SUPER | GLFW_MOD_ALT |                    GLFW_MOD_SHIFT,
  CONTROL_ALT_SUPER         = GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_CONTROL                 ,
  SHIFT_CONTROL_ALT_SUPER   = GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,
  // array bounds
  LAST = SHIFT_CONTROL_ALT_SUPER,
  END = LAST + 1
};
inline keymodtype operator|(keymodtype lhs, keymodtype rhs) {
  return static_cast<keymodtype>(static_cast<int>(lhs) | static_cast<int>(rhs));
}
inline keymodtype &operator|=(keymodtype &lhs, keymodtype rhs) {
  lhs = static_cast<keymodtype>(static_cast<int>(lhs) | static_cast<int>(rhs));
  return lhs;
}
inline keymodtype operator|(int lhs, keymodtype rhs) {
  return static_cast<keymodtype>(lhs | static_cast<int>(rhs));
}
inline int &operator|=(int &lhs, keymodtype rhs) {
  lhs = lhs | static_cast<int>(rhs);
  return lhs;
}
inline keymodtype operator|(keymodtype lhs, int rhs) {
  return static_cast<keymodtype>(static_cast<int>(lhs) | rhs);
}
inline keymodtype &operator|=(keymodtype &lhs, int rhs) {
  lhs = static_cast<keymodtype>(static_cast<int>(lhs) | rhs);
  return lhs;
}

class manager {
private:
  // keys
  /// Sparse 3D array of key names for each GLFW key code and functions.
  /// Functions are kept separate for cache performance during key lookup.
  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
  ///   1st = GLFW action (GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE)
  ///   2nd = GLFW modifier bits (http://www.glfw.org/docs/latest/group__mods.html)
  ///   3st = GLFW key code (http://www.glfw.org/docs/latest/group__keys.html)
  static unsigned int constexpr max_key        = GLFW_KEY_LAST + 1;
  static unsigned int constexpr max_key_mods   = static_cast<int>(keymodtype::END);     // modifiers can be combined, we store all options to save processing
  static unsigned int constexpr max_key_action = static_cast<int>(keyactiontype::END);
  std::array<std::string, max_key>        key_names;                            // cached human-readable names of keys
  std::array<std::string, max_key_mods>   key_mod_names;                        // cached human-readable names of key modifiers
  std::array<std::string, max_key_action> key_action_names;                     // cached human-readable names of key actions
  std::array<std::array<std::array<std::function<void()>, max_key>, max_key_mods>, max_key_action> key_bindings;    // callback functions for keys

  // cursor
  std::function<void(Vector2d const&)> cursor_binding = [](Vector2d const &change __attribute__((__unused__))){};   // callback function for cursor movement
  std::function<void()> cursor_enter_binding = []{};                            // cursor enters the window
  std::function<void()> cursor_leave_binding = []{};                            // cursor leaves the window

  // mouse buttons
  static unsigned int constexpr max_mousebutton = GLFW_MOUSE_BUTTON_LAST + 1;
  static unsigned int constexpr max_mouse_action = static_cast<int>(keyactiontype::REPEAT);   // there's no repeat action for mouse buttons
  std::array<std::string, max_mousebutton> mousebutton_names;                   // cached human-readable names of buttons
  std::array<std::array<std::array<std::function<void()>, max_mousebutton>, max_key_mods>, max_mouse_action> mousebutton_bindings;  // callback functions for keys

  // scroll
  std::function<void(Vector2d const&)> scroll_binding = [](Vector2d const &change __attribute__((__unused__))){};   // callback function for scroll

  // joystick
  /// Sparse 2D / 3D arrays of joystick axes and buttons and joystick names.
  /// Each is stored together with the parameters for a transformation to
  /// allow for configurable deadzones, saturation zones and axis asymmetry.
  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
  /// Axes:
  ///   1st = GLFW joystick axis (total number is NOT known until runtime, so we set a hard limit here)
  ///   2nd = GLFW Joystick ID
  /// Buttons:
  ///   1st = GLFW action (GLFW_PRESS or GLFW_RELEASE);
  static unsigned int constexpr max_joystick = GLFW_JOYSTICK_LAST + 1;
  static unsigned int constexpr max_joystick_axis = 8;                          // empirically chosen based on what's available on the market
  static unsigned int constexpr max_joystick_button = 60;                       // empirically chosen based on what's available on the market
  static unsigned int constexpr max_joystick_button_action = static_cast<int>(keyactiontype::REPEAT);   // there's no repeat action for joystick buttons
  struct joystick_axis_bindingtype {
    bool enabled = false;                                                       // whether to try this axis' function
    float deadzone_min   =  0.0f;                                               // values within this range are clamped to zero
    float deadzone_max   =  0.0f;
    float saturation_min = -1.0f;                                               // values beyond this range are clamped to one
    float saturation_max =  1.0f;
    float scale_pos = saturation_max - deadzone_max;                            // cached scale values - output values are scaled to fill the above range
    float scale_neg = deadzone_min - saturation_min;
    std::function<void(float)> func = [](float value __attribute__((__unused__))){};  // the function to call
    void update_scales() {
      /// Re-cache scale values after changing deadzones or saturation values
      scale_pos = saturation_max - deadzone_max;
      scale_neg = deadzone_min - saturation_min;
    }
  };
  std::array<bool, max_joystick> joystick_enabled;                              // whether each joystick is enabled or not
  std::array<std::string, max_joystick> joystick_names;                         // cached human-readable names of joysticks
  std::array<std::array<joystick_axis_bindingtype, max_joystick>, max_joystick_axis> joystick_axis_bindings;    // callback functions for joystick axes
  std::array<std::array<std::array<std::function<void()>, max_joystick>, max_joystick_button>, max_joystick_button_action> joystick_button_bindings;    // callback functions for joystick buttons

  GLFWwindow *current_window = nullptr;                                         // the GLFW window this input manager is handling

public:
  manager(GLFWwindow &thiswindow);
  ~manager();

private:
  std::string &key_name_at(keytype key);
  std::string &mousebutton_name_at(mousebuttontype button);
  std::function<void()> &key_binding_at(keytype key, keyactiontype action, keymodtype mods);
  std::function<void()> &mousebutton_binding_at(mousebuttontype button, keyactiontype action, keymodtype mods);
  joystick_axis_bindingtype &joystick_axis_binding_at(unsigned int joystick, unsigned int axis);
  std::function<void()> &joystick_button_binding_at(unsigned int joystick, unsigned int button, keyactiontype action);
public:
  std::string const &get_key_name(        keytype key)            const;
  std::string const &get_keyaction_name(  keyactiontype action)   const;
  std::string const &get_keymod_name(     keymodtype mods)        const;
  std::string const &get_mousebutton_name(mousebuttontype button) const;

  void bind_key(keytype key, keyactiontype action, keymodtype mods, std::function<void()> func);
  void bind_cursor(std::function<void(Vector2d const&)> func);
  void bind_cursor_enter(std::function<void()> func);
  void bind_cursor_leave(std::function<void()> func);
  void bind_mousebutton(mousebuttontype button, keyactiontype action, keymodtype mods, std::function<void()> func);
  void bind_scroll(std::function<void(Vector2d const&)> func);
  void bind_joystick_axis(unsigned int joystick, unsigned int axis, std::function<void(float)> func, float deadzone_min = 0.0f, float deadzone_max = 0.0f, float saturation_min = -1.0f, float saturation_max = 1.0f);
  void bind_joystick_button(unsigned int joystick, unsigned int button, keyactiontype action, std::function<void()> func);

  // TODO: add unbind functions

  // TODO: add search by function pointer functions

  void execute_key(keytype key, keyactiontype action = keyactiontype::PRESS, keymodtype mods = keymodtype::NONE);
  void execute_cursor(Vector2d const &change);
  void execute_cursor_enter();
  void execute_cursor_leave();
  void execute_mousebutton(mousebuttontype button, keyactiontype action = keyactiontype::PRESS, keymodtype mods = keymodtype::NONE);
  void execute_scroll(Vector2d const &offset);
  void execute_joystick_axis(unsigned int joystick, unsigned int axis, float value = 0.0f);
  void execute_joystick_button(unsigned int joystick, unsigned int button, keyactiontype action = keyactiontype::PRESS);

  void update_joystick_names();
  void poll_joysticks();
};

}

#endif // INPUTSTORM_MANAGER_H_INCLUDED
