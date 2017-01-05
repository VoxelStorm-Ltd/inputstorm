        }
      #endif // INPUTSTORM_EQUALITY_COMPARISON_SWITCH
    }

    size_t hash_value() const {
      /// Hash function to return a unique hash for each binding
      size_t constexpr const key_max = GLFW_KEY_LAST + 1;
      size_t constexpr const type_max = static_cast<size_t>(bindtype::END);
      return (key_max * type_max * static_cast<size_t>(mods)) +
             (key_max * static_cast<size_t>(type)) +
             key;
    }
  };

#ifndef INPUTSTORM_INPUT_KEY_H_INCLUDED
  // limits
#define INPUTSTORM_INPUT_KEY_H_INCLUDED
  static unsigned int constexpr const max        = GLFW_KEY_LAST + 1;

  static unsigned int constexpr const max_action = static_cast<int>(actiontype::END);
#include <functional>
#include <GL/glew.h>
  static unsigned int constexpr const max_mods   = static_cast<int>(modtype::END); // modifiers can be combined, we store all options to save processing
#include <GLFW/glfw3.h>


private:
namespace inputstorm {
  // data
namespace input {
  std::array<std::array<std::array<std::function<void()>, max>, max_mods>, max_action> bindings; // callback functions for keys


class key {
public:
public:
  void init();
  /// Sparse 3D array of key names for each GLFW key code and functions.

  /// Functions are kept separate for cache performance during key lookup.
private:
  /// Dimensions are arranged for speed, lowest first to minimise total number of array objects.
  #ifdef NDEBUG
  ///   1st = GLFW action (GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE)
    std::string const &name_at(keytype key) const __attribute__((__const__));
  ///   2nd = GLFW modifier bits (http://www.glfw.org/docs/latest/group__mods.html)
    std::function<void()> const &binding_at(keytype this_key, actiontype action, modtype mods) const __attribute__((__const__));
  ///   3st = GLFW key code (http://www.glfw.org/docs/latest/group__keys.html)
  #else

    std::string const &name_at(keytype key) const;
  // types
    std::function<void()> const &binding_at(keytype this_key, actiontype action, modtype mods) const;
  using keytype = int;
  #endif // NDEBUG
  enum class actiontype : int {

    RELEASE = GLFW_RELEASE,
public:
    PRESS   = GLFW_PRESS,
  static std::string get_name(keytype this_key);
    REPEAT  = GLFW_REPEAT,
    // array bounds
  static std::string get_actiontype_name(actiontype action);
    BEGIN = RELEASE,
  static std::string get_mod_name(modtype mods);
    LAST = REPEAT,

    END = LAST + 1
  void reset();
  };

  enum class modtype : int {
  void bind(        keytype key, actiontype action, modtype mods, std::function<void()> func);
    NONE                      = 0,
  void bind_any_mod(keytype key, actiontype action,               std::function<void()> func);
    // shift
  void bind_any(                                                  std::function<void()> func);
    SHIFT                     =                                                    GLFW_MOD_SHIFT,
  void bind(binding const &this_binding, std::function<void()> func_press, std::function<void()> func_release = nullptr, std::function<void()> func_repeat = nullptr);
    // control

    CONTROL                   =                                 GLFW_MOD_CONTROL                 ,
  void unbind(        keytype key, actiontype action, modtype mods);
    SHIFT_CONTROL             =                                 GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,
  void unbind_any_mod(keytype key, actiontype action);
    // alt
  void unbind_any();
    ALT                       =                  GLFW_MOD_ALT                                    ,
  void unbind(binding const &this_binding);
    SHIFT_ALT                 =                  GLFW_MOD_ALT |                    GLFW_MOD_SHIFT,

    CONTROL_ALT               =                  GLFW_MOD_ALT | GLFW_MOD_CONTROL                 ,
  // TODO: add search by function pointer functions
    SHIFT_CONTROL_ALT         =                  GLFW_MOD_ALT | GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,

    // super
  void execute(keytype key,
    SUPER                     = GLFW_MOD_SUPER                                                   ,
               actiontype action = actiontype::PRESS,
    SHIFT_SUPER               = GLFW_MOD_SUPER |                                   GLFW_MOD_SHIFT,
               modtype mods = modtype::NONE) const;
    CONTROL_SUPER             = GLFW_MOD_SUPER |                GLFW_MOD_CONTROL                 ,

    SHIFT_CONTROL_SUPER       = GLFW_MOD_SUPER |                GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,
  void capture(std::function<void(keytype, modtype)> callback);
    ALT_SUPER                 = GLFW_MOD_SUPER | GLFW_MOD_ALT                                    ,
  void capture(std::function<void(binding const&)> callback);
    SHIFT_ALT_SUPER           = GLFW_MOD_SUPER | GLFW_MOD_ALT |                    GLFW_MOD_SHIFT,
};
    CONTROL_ALT_SUPER         = GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_CONTROL                 ,

    SHIFT_CONTROL_ALT_SUPER   = GLFW_MOD_SUPER | GLFW_MOD_ALT | GLFW_MOD_CONTROL | GLFW_MOD_SHIFT,
inline key::modtype operator|(key::modtype lhs, key::modtype rhs) {
    // array bounds
    BEGIN = NONE,
  return static_cast<key::modtype>(static_cast<int>(lhs) | static_cast<int>(rhs));
    LAST = SHIFT_CONTROL_ALT_SUPER,
}
    END = LAST + 1
inline key::modtype &operator|=(key::modtype &lhs, key::modtype rhs) {
  };
  lhs = static_cast<key::modtype>(static_cast<int>(lhs) | static_cast<int>(rhs));
  struct binding {
  return lhs;
    /// Convenience struct for storing and passing all parameters that make up a binding
}
    enum class bindtype : char {
inline key::modtype operator|(int lhs, key::modtype rhs) {
      SPECIFIC,
  return static_cast<key::modtype>(lhs | static_cast<int>(rhs));
      ANY_MOD,
}
      ANY,
inline int &operator|=(int &lhs, key::modtype rhs) {
      LAST = ANY,
  lhs = lhs | static_cast<int>(rhs);
      END = LAST + 1
  return lhs;
    } type;
}
    keytype key;
    modtype mods;
inline key::modtype operator|(key::modtype lhs, int rhs) {

  return static_cast<key::modtype>(static_cast<int>(lhs) | rhs);
    bool operator==(const binding &rhs) const {
}
      /// Equality operator
inline key::modtype &operator|=(key::modtype &lhs, int rhs) {
      // two formulations with the same effect - benchmark to see which performs best in each specific use case
  lhs = static_cast<key::modtype>(static_cast<int>(lhs) | rhs);
      #ifdef INPUTSTORM_EQUALITY_COMPARISON_SWITCH
  return lhs;
        switch(type) {
}
        case bindtype::SPECIFIC:

          switch(rhs.type) {
/// Helper functions to allow key::modtype to be iterated
          case bindtype::SPECIFIC:
inline key::modtype operator++(key::modtype &i) {
            return (key == rhs.key) && (mods == rhs.mods);
  return i = static_cast<key::modtype>(std::underlying_type<key::modtype>::type(i) + 1);
          case bindtype::ANY_MOD:
}
            return key == rhs.key;
inline key::modtype operator*(key::modtype c) {
          case bindtype::ANY:
  return c;
            return true;
}
          }
          break;
inline key::modtype begin(key::modtype thistype __attribute__((__unused__))) {
        case bindtype::ANY_MOD:
  return key::modtype::BEGIN;
          switch(rhs.type) {
}
          case bindtype::SPECIFIC:
inline key::modtype end(key::modtype thistype __attribute__((__unused__))) {
          case bindtype::ANY_MOD:
  return key::modtype::END;
            return key == rhs.key;
}
          case bindtype::ANY:

            return true;
/// Helper functions to allow key::actiontype to be iterated
          }
inline key::actiontype operator++(key::actiontype &i) {
          break;
  return i = static_cast<key::actiontype>(std::underlying_type<key::actiontype>::type(i) + 1);
        case bindtype::ANY:
}
          return true;
inline key::actiontype operator*(key::actiontype c) {
        default:
  return c;
          return false;
}
        }
      #else
inline key::actiontype begin(key::actiontype thistype __attribute__((__unused__))) {
        if(type == bindtype::ANY || rhs.type == bindtype::ANY) {
  return key::actiontype::BEGIN;
          return true;
}
        } else if(type == bindtype::ANY_MOD || rhs.type == bindtype::ANY_MOD) {
inline key::actiontype end(key::actiontype thistype __attribute__((__unused__))) {
          return key == rhs.key;
  return key::actiontype::END;
        } else {
}
          return (key == rhs.key) && (mods == rhs.mods);

        }
inline size_t hash_value(key::binding const &this_binding) {
      #endif // INPUTSTORM_EQUALITY_COMPARISON_SWITCH
  /// Forward to the binding's hash function
    }
  return this_binding.hash_value();

}
    size_t hash_value() const {

      /// Hash function to return a unique hash for each binding
}
      size_t constexpr const key_max = GLFW_KEY_LAST + 1;
}
      size_t constexpr const type_max = static_cast<size_t>(bindtype::END);

      return (key_max * type_max * static_cast<size_t>(mods)) +
#endif // INPUTSTORM_INPUT_KEY_H_INCLUDED
             (key_max * static_cast<size_t>(type)) +
             key;
    }
  };

  // limits
  static unsigned int constexpr const max        = GLFW_KEY_LAST + 1;
  static unsigned int constexpr const max_action = static_cast<int>(actiontype::END);
  static unsigned int constexpr const max_mods   = static_cast<int>(modtype::END); // modifiers can be combined, we store all options to save processing

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
inline key::modtype begin(key::modtype thistype __attribute__((__unused__))) {
  return key::modtype::BEGIN;
}
inline key::modtype end(key::modtype thistype __attribute__((__unused__))) {
  return key::modtype::END;
}

/// Helper functions to allow key::actiontype to be iterated
inline key::actiontype operator++(key::actiontype &i) {
  return i = static_cast<key::actiontype>(std::underlying_type<key::actiontype>::type(i) + 1);
}
inline key::actiontype operator*(key::actiontype c) {
  return c;
}
inline key::actiontype begin(key::actiontype thistype __attribute__((__unused__))) {
  return key::actiontype::BEGIN;
}
inline key::actiontype end(key::actiontype thistype __attribute__((__unused__))) {
  return key::actiontype::END;
}

inline size_t hash_value(key::binding const &this_binding) {
  /// Forward to the binding's hash function
  return this_binding.hash_value();
}

}
}

#endif // INPUTSTORM_INPUT_KEY_H_INCLUDED
