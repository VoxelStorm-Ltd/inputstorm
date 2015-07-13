#ifndef INPUTSTORM_MANAGER_H_INCLUDED
#define INPUTSTORM_MANAGER_H_INCLUDED

#include <array>
#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace inputstorm {

using keytype = int;
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
  std::array<std::array<std::array<std::function<void()>, max_key>, max_key_mods>, max_key_action> key_bindings;

  GLFWwindow *current_window = nullptr;                                         // the GLFW window this input manager is handling

public:
  manager(GLFWwindow &thiswindow);
  ~manager();

private:
  std::string &key_name_at(keytype key);
  std::function<void()> &key_binding_at(keytype key, keyactiontype action, keymodtype mods);
public:
  std::string const &get_key_name(      keytype key)          const;
  std::string const &get_keyaction_name(keyactiontype action) const;
  std::string const &get_keymod_name(   keymodtype mods)      const;

  void execute_key(keytype key, keyactiontype action, keymodtype mods = keymodtype::NONE);
};

}

#endif // INPUTSTORM_MANAGER_H_INCLUDED
