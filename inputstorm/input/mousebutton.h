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
  std::string &name_at(buttontype button);
  std::function<void()> &binding_at(buttontype button, key::action action = key::action::PRESS, key::mod mods = key::mod::NONE);

public:
  std::string const &get_name(buttontype button) const;

  void bind(        buttontype button, key::action action, key::mod mods, std::function<void()> func);
  void bind_any_mod(buttontype button, key::action action,                         std::function<void()> func);
  void bind_any(std::function<void()> func);

  void execute(buttontype button, key::action action = key::action::PRESS, key::mod mods = key::mod::NONE);
};

}
}

#endif // INPUTSTORM_INPUT_MOUSEBUTTON_H_INCLUDED
