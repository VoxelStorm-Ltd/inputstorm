#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "key.h"

namespace inputstorm::input {

class mousebutton {
public:
  // types
  using buttontype = int;

  enum class actiontype : int {
    RELEASE = GLFW_RELEASE,
    PRESS   = GLFW_PRESS,
    // array bounds
    BEGIN = RELEASE,
    LAST = PRESS,
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
    buttontype button;
    key::modtype mods;

    bool operator==(const binding &rhs) const {
      /// Equality operator
      // two formulations with the same effect - benchmark to see which performs best in each specific use case
      #ifdef INPUTSTORM_EQUALITY_COMPARISON_SWITCH
        switch(type) {
        case bindtype::SPECIFIC:
          switch(rhs.type) {
          case bindtype::SPECIFIC:
            return (button == rhs.button) && (mods == rhs.mods);
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
            return button == rhs.button;
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
          return button == rhs.button;
        } else {
          return (button == rhs.button) && (mods == rhs.mods);
        }
      #endif // INPUTSTORM_EQUALITY_COMPARISON_SWITCH
    }

    size_t hash_value() const {
      /// Hash function to return a unique hash for each binding
      size_t constexpr button_max = GLFW_MOUSE_BUTTON_LAST + 1;
      size_t constexpr type_max = static_cast<size_t>(bindtype::END);
      return (button_max * type_max * static_cast<size_t>(mods)) +
             (button_max * static_cast<size_t>(type)) +
             button;
    }
  };

  // limits
  static unsigned int constexpr max = GLFW_MOUSE_BUTTON_LAST + 1;

  // data
private:
  std::array<std::array<std::array<std::function<void()>, max>, key::max_mods>, static_cast<unsigned int>(actiontype::END)> bindings; // callback functions for keys

public:
  void init();

private:
  #ifdef NDEBUG
    std::function<void()> const &binding_at(buttontype button,
                                            actiontype action = actiontype::PRESS,
                                            key::modtype mods = key::modtype::NONE) const __attribute__((__const__));
  #else
    std::string const &name_at(buttontype button) const;
    std::function<void()> const &binding_at(buttontype button,
                                            actiontype action = actiontype::PRESS,
                                            key::modtype mods = key::modtype::NONE) const;
  #endif // NDEBUG

public:
  static std::string get_name(buttontype button);
  static std::string get_actiontype_name(actiontype action);

  void bind(        buttontype button, actiontype action, key::modtype mods, std::function<void()> func);
  void bind_any_mod(buttontype button, actiontype action,                    std::function<void()> func);
  void bind_any(                                                             std::function<void()> func);
  void bind(binding const &this_binding, std::function<void()> func_press, std::function<void()> func_release = nullptr);

  void unbind(        buttontype button, actiontype action, key::modtype mods);
  void unbind_any_mod(buttontype button, actiontype action);
  void unbind_any();
  void unbind(binding const &this_binding);

  void execute(buttontype button,
               actiontype action = actiontype::PRESS,
               key::modtype mods = key::modtype::NONE) const;

  void capture(std::function<void(buttontype, key::modtype)> callback);
  void capture(std::function<void(binding const&)> callback);
};

/// Helper functions to allow mousebutton::actiontype to be iterated
inline mousebutton::actiontype operator++(mousebutton::actiontype &i) {
  return i = static_cast<mousebutton::actiontype>(std::underlying_type<mousebutton::actiontype>::type(i) + 1);
}
inline mousebutton::actiontype operator*(mousebutton::actiontype c) {
  return c;
}
inline mousebutton::actiontype begin(mousebutton::actiontype thistype [[maybe_unused]]) {
  return mousebutton::actiontype::BEGIN;
}
inline mousebutton::actiontype end(mousebutton::actiontype thistype [[maybe_unused]]) {
  return mousebutton::actiontype::END;
}

inline size_t hash_value(mousebutton::binding const &this_binding) {
  /// Forward to the binding's hash function
  return this_binding.hash_value();
}

}

namespace std {

template<>
struct hash<inputstorm::input::mousebutton::binding> {
  /// Forward the binding's hash function for std::hash specialisation
  size_t operator()(inputstorm::input::mousebutton::binding const &this_binding) const {
    return this_binding.hash_value();
  }
};

}
