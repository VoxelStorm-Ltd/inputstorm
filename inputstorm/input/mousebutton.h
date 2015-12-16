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

  // limits
  static unsigned int constexpr max = GLFW_MOUSE_BUTTON_LAST + 1;
  static unsigned int constexpr max_action = static_cast<int>(key::action::REPEAT);   // there's no repeat action for mouse buttons

  // data
private:
  std::array<std::string, max> names;                                           // cached human-readable names of buttons
  std::array<std::array<std::array<std::function<void()>, max>, key::max_mods>, max_action> bindings;  // callback functions for keys

public:
  void init();

private:
  #ifdef NDEBUG
    std::string &name_at(buttontype button) __attribute__((__const__));
    std::function<void()> &binding_at(buttontype button, key::action action = key::action::PRESS, key::mod mods = key::mod::NONE) __attribute__((__const__));
  #else
    std::string &name_at(buttontype button);
    std::function<void()> &binding_at(buttontype button, key::action action = key::action::PRESS, key::mod mods = key::mod::NONE);
  #endif // NDEBUG

public:
  #ifdef NDEBUG
    std::string const &get_name(buttontype button) const __attribute__((__const__));
  #else
    std::string const &get_name(buttontype button) const;
  #endif // NDEBUG

  void bind(        buttontype button, key::action action, key::mod mods, std::function<void()> func);
  void bind_any_mod(buttontype button, key::action action,                std::function<void()> func);
  void bind_any(                                                          std::function<void()> func);

  void unbind(        buttontype button, key::action action, key::mod mods);
  void unbind_any_mod(buttontype button, key::action action);
  void unbind_any();

  void execute(buttontype button, key::action action = key::action::PRESS, key::mod mods = key::mod::NONE);
};

}
}

#endif // INPUTSTORM_INPUT_MOUSEBUTTON_H_INCLUDED
