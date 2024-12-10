#pragma once

#include <functional>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace inputstorm::input {

class key {
public:
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
    BEGIN = RELEASE,
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
    BEGIN = NONE,
    LAST = SHIFT_CONTROL_ALT_SUPER,
    END = LAST + 1
  };
  struct binding {
    /// Convenience struct for storing and passing all parameters that make up a binding
    enum class bindtype : char {
      SPECIFIC,
      ANY_MOD,
      ANY,
      LAST = ANY,
      END = LAST + 1
    } type;
    keytype key;
    modtype mods;

    bool operator==(const binding &rhs) const {
      /// Equality operator
      // two formulations with the same effect - benchmark to see which performs best in each specific use case
      #ifdef INPUTSTORM_EQUALITY_COMPARISON_SWITCH
        switch(type) {
        case bindtype::SPECIFIC:
          switch(rhs.type) {
          case bindtype::SPECIFIC:
            return (key == rhs.key) && (mods == rhs.mods);
          case bindtype::ANY_MOD:
            return key == rhs.key;
          case bindtype::ANY:
            return true;
          }
          break;
        case bindtype::ANY_MOD:
          switch(rhs.type) {
          case bindtype::SPECIFIC:
          case bindtype::ANY_MOD:
            return key == rhs.key;
          case bindtype::ANY:
            return true;
          }
          break;
        case bindtype::ANY:
          return true;
        default:
          return false;
        }
      #else
        if(type == bindtype::ANY || rhs.type == bindtype::ANY) {
          return true;
        } else if(type == bindtype::ANY_MOD || rhs.type == bindtype::ANY_MOD) {
          return key == rhs.key;
        } else {
          return (key == rhs.key) && (mods == rhs.mods);
        }
      #endif // INPUTSTORM_EQUALITY_COMPARISON_SWITCH
    }

    size_t hash_value() const {
      /// Hash function to return a unique hash for each binding
      size_t constexpr key_max = GLFW_KEY_LAST + 1;
      size_t constexpr type_max = static_cast<size_t>(bindtype::END);
      return (key_max * type_max * static_cast<size_t>(mods)) +
             (key_max * static_cast<size_t>(type)) +
             key;
    }
  };

  // limits
  static unsigned int constexpr max        = GLFW_KEY_LAST + 1;
  static unsigned int constexpr max_action = static_cast<int>(actiontype::END);
  static unsigned int constexpr max_mods   = static_cast<int>(modtype::END);    // modifiers can be combined, we store all options to save processing

private:
  // data
  std::array<std::array<std::array<std::function<void()>, max>, max_mods>, max_action> bindings; // callback functions for keys

public:
  void init();

private:
  #ifdef NDEBUG
    std::string const &name_at(keytype key) const __attribute__((__const__));
    std::function<void()> const &binding_at(keytype this_key, actiontype action, modtype mods) const __attribute__((__const__));
  #else
    std::string const &name_at(keytype key) const;
    std::function<void()> const &binding_at(keytype this_key, actiontype action, modtype mods) const;
  #endif // NDEBUG

public:
  static std::string get_name(keytype this_key);
  static std::string get_actiontype_name(actiontype action);
  static std::string get_mod_name(modtype mods);

  void reset();

  void bind(        keytype key, actiontype action, modtype mods, std::function<void()> func);
  void bind_any_mod(keytype key, actiontype action,               std::function<void()> func);
  void bind_any(                                                  std::function<void()> func);
  void bind(binding const &this_binding, std::function<void()> func_press, std::function<void()> func_release = nullptr, std::function<void()> func_repeat = nullptr);

  void unbind(        keytype key, actiontype action, modtype mods);
  void unbind_any_mod(keytype key, actiontype action);
  void unbind_any();
  void unbind(binding const &this_binding);

  // TODO: add search by function pointer functions

  void execute(keytype key,
               actiontype action = actiontype::PRESS,
               modtype mods = modtype::NONE) const;

  void capture(std::function<void(keytype, modtype)> callback);
  void capture(std::function<void(binding const&)> callback);
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

/// Helper functions to allow key::modtype to be iterated
inline key::modtype operator++(key::modtype &i) {
  return i = static_cast<key::modtype>(std::underlying_type<key::modtype>::type(i) + 1);
}
inline key::modtype operator*(key::modtype c) {
  return c;
}
inline key::modtype begin(key::modtype thistype [[maybe_unused]]) {
  return key::modtype::BEGIN;
}
inline key::modtype end(key::modtype thistype [[maybe_unused]]) {
  return key::modtype::END;
}

/// Helper functions to allow key::actiontype to be iterated
inline key::actiontype operator++(key::actiontype &i) {
  return i = static_cast<key::actiontype>(std::underlying_type<key::actiontype>::type(i) + 1);
}
inline key::actiontype operator*(key::actiontype c) {
  return c;
}
inline key::actiontype begin(key::actiontype thistype [[maybe_unused]]) {
  return key::actiontype::BEGIN;
}
inline key::actiontype end(key::actiontype thistype [[maybe_unused]]) {
  return key::actiontype::END;
}

inline size_t hash_value(key::binding const &this_binding) {
  /// Forward to the binding's hash function
  return this_binding.hash_value();
}

}
