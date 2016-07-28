#ifndef INPUTSTORM_INPUT_MOUSEBUTTON_H_INCLUDED
#define INPUTSTORM_INPUT_MOUSEBUTTON_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "key.h"

namespace inputstorm {
namespace input {

struct mousebutton {
  // types
  using buttontype = int;

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
      constexpr const size_t button_max = GLFW_MOUSE_BUTTON_LAST + 1;
      constexpr const size_t type_max = static_cast<size_t>(bindtype::END);
      return (button_max * type_max * static_cast<size_t>(mods)) +
             (button_max * static_cast<size_t>(type)) +
             button;
    }
  };

  // limits
  static unsigned int constexpr max = GLFW_MOUSE_BUTTON_LAST + 1;
  static unsigned int constexpr max_action = static_cast<int>(key::actiontype::REPEAT); // there's no repeat action for mouse buttons

  // data
private:
  std::array<std::string, max> names;                                           // cached human-readable names of buttons
  std::array<std::array<std::array<std::function<void()>, max>, key::max_mods>, max_action> bindings; // callback functions for keys

public:
  void init();

private:
  #ifdef NDEBUG
    std::string &name_at(buttontype button) __attribute__((__const__));
    std::function<void()> &binding_at(buttontype button,
                                      key::actiontype action = key::actiontype::PRESS,
                                      key::modtype mods = key::modtype::NONE) __attribute__((__const__));
  #else
    std::string &name_at(buttontype button);
    std::function<void()> &binding_at(buttontype button,
                                      key::actiontype action = key::actiontype::PRESS,
                                      key::modtype mods = key::modtype::NONE);
  #endif // NDEBUG

public:
  #ifdef NDEBUG
    std::string const &get_name(buttontype button) const __attribute__((__const__));
  #else
    std::string const &get_name(buttontype button) const;
  #endif // NDEBUG

  void bind(        buttontype button, key::actiontype action, key::modtype mods, std::function<void()> func);
  void bind_any_mod(buttontype button, key::actiontype action,                    std::function<void()> func);
  void bind_any(                                                                  std::function<void()> func);
  void bind(binding const &this_binding, std::function<void()> func_press, std::function<void()> func_release = nullptr);

  void unbind(        buttontype button, key::actiontype action, key::modtype mods);
  void unbind_any_mod(buttontype button, key::actiontype action);
  void unbind_any();
  void unbind(binding const &this_binding);

  void execute(buttontype button,
               key::actiontype action = key::actiontype::PRESS,
               key::modtype mods = key::modtype::NONE);
};

inline size_t hash_value(mousebutton::binding const &this_binding) {
  /// Forward to the binding's hash function
  return this_binding.hash_value();
}

}
}

#endif // INPUTSTORM_INPUT_MOUSEBUTTON_H_INCLUDED
