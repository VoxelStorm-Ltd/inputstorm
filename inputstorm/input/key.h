#ifndef INPUTSTORM_INPUT_KEY_H_INCLUDED
#define INPUTSTORM_INPUT_KEY_H_INCLUDED

#include <functional>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace inputstorm {
namespace input {

struct key {
  /// Sparse 3D array of key names for each GLFW key code and functions.
  /// Functions are kept separate for cache performance during key lookup.
  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
  ///   1st = GLFW action (GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE)
  ///   2nd = GLFW modifier bits (http://www.glfw.org/docs/latest/group__mods.html)
  ///   3st = GLFW key code (http://www.glfw.org/docs/latest/group__keys.html)

  // types
  using keytype = int;
  enum class actiontype : int {
    RELEASE = GLFW_RELEASE,
    PRESS   = GLFW_PRESS,
    REPEAT  = GLFW_REPEAT,
    // array bounds
    LAST = REPEAT,
    END = LAST + 1
  };
  enum class modtype : int {
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
  struct binding {
    /// Convenience struct for storing and passing all parameters that make up a binding
    keytype key;
    actiontype action;
    modtype mods;
  };

  // limits
  static unsigned int constexpr max        = GLFW_KEY_LAST + 1;
  static unsigned int constexpr max_action = static_cast<int>(actiontype::END);
  static unsigned int constexpr max_mods   = static_cast<int>(modtype::END);    // modifiers can be combined, we store all options to save processing

  // data
private:
  std::array<std::string, max>        names;                                    // cached human-readable names of keys
  std::array<std::string, max_mods>   mod_names;                                // cached human-readable names of key modifiers
  std::array<std::string, max_action> action_names;                             // cached human-readable names of key actions
  std::array<std::array<std::array<std::function<void()>, max>, max_mods>, max_action> bindings; // callback functions for keys

public:
  void init();

private:
  #ifdef NDEBUG
    std::string &name_at(keytype key) __attribute__((__const__));
    std::function<void()> &binding_at(keytype this_key, actiontype action, modtype mods) __attribute__((__const__));
  #else
    std::string &name_at(keytype key);
    std::function<void()> &binding_at(keytype this_key, actiontype action, modtype mods);
  #endif // NDEBUG

public:
  #ifdef NDEBUG
    std::string const &get_name(keytype this_key) const __attribute__((__const__));
  #else
    std::string const &get_name(keytype this_key) const;
  #endif // NDEBUG
  std::string const &get_actiontype_name(actiontype action) const __attribute__((__const__));
  std::string const &get_mod_name(       modtype mods)      const __attribute__((__const__));

  void bind(        keytype key, actiontype action, modtype mods, std::function<void()> func);
  void bind_any_mod(keytype key, actiontype action,               std::function<void()> func);
  void bind_any(std::function<void()> func);

  void unbind(        keytype key, actiontype action, modtype mods);
  void unbind_any_mod(keytype key, actiontype action);
  void unbind_any();

  // TODO: add search by function pointer functions

  void execute(keytype key,
               actiontype action = actiontype::PRESS,
               modtype mods = modtype::NONE);
};

inline key::modtype operator|(key::modtype lhs, key::modtype rhs) {
  return static_cast<key::modtype>(static_cast<int>(lhs) | static_cast<int>(rhs));
}
inline key::modtype &operator|=(key::modtype &lhs, key::modtype rhs) {
  lhs = static_cast<key::modtype>(static_cast<int>(lhs) | static_cast<int>(rhs));
  return lhs;
}
inline key::modtype operator|(int lhs, key::modtype rhs) {
  return static_cast<key::modtype>(lhs | static_cast<int>(rhs));
}
inline int &operator|=(int &lhs, key::modtype rhs) {
  lhs = lhs | static_cast<int>(rhs);
  return lhs;
}
inline key::modtype operator|(key::modtype lhs, int rhs) {
  return static_cast<key::modtype>(static_cast<int>(lhs) | rhs);
}
inline key::modtype &operator|=(key::modtype &lhs, int rhs) {
  lhs = static_cast<key::modtype>(static_cast<int>(lhs) | rhs);
  return lhs;
}

}
}

#endif // INPUTSTORM_INPUT_KEY_H_INCLUDED
