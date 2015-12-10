#ifndef INPUTSTORM_INPUT_CURSOR_H_INCLUDED
#define INPUTSTORM_INPUT_CURSOR_H_INCLUDED

#include <functional>
#include "vmath_forward_dec.h"

namespace inputstorm {
namespace input {

struct cursor {
  // data
private:
  std::function<void(Vector2d const&)> binding = [](Vector2d const &change __attribute__((__unused__))){};   // callback function for cursor movement
  std::function<void()> enter_binding = []{};                                   // cursor enters the window
  std::function<void()> leave_binding = []{};                                   // cursor leaves the window

public:
  void bind(std::function<void(Vector2d const&)> func);
  void bind_enter(std::function<void()> func);
  void bind_leave(std::function<void()> func);

  void unbind();
  void unbind_enter();
  void unbind_leave();

  void execute(Vector2d const &change);
  void execute_enter();
  void execute_leave();
};

}
}

#endif // INPUTSTORM_INPUT_CURSOR_H_INCLUDED
