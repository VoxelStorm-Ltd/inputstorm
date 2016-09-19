#ifndef INPUTSTORM_INPUT_CURSOR_H_INCLUDED
#define INPUTSTORM_INPUT_CURSOR_H_INCLUDED

#include <functional>
#include "vectorstorm/vector/vector2_forward.h"

namespace inputstorm {
namespace input {

struct cursor {
  // data
private:
  std::function<void(vec2d const&)> binding       = [](vec2d const &change __attribute__((__unused__))){}; // callback function for cursor movement
  std::function<void()>             enter_binding = []{};                       // cursor enters the window
  std::function<void()>             leave_binding = []{};                       // cursor leaves the window

public:
  void bind(std::function<void(vec2d const&)> func);
  void bind_enter(std::function<void()> func);
  void bind_leave(std::function<void()> func);

  void unbind();
  void unbind_enter();
  void unbind_leave();

  void execute(vec2d const &change) const;
  void execute_enter()              const;
  void execute_leave()              const;
};

}
}

#endif // INPUTSTORM_INPUT_CURSOR_H_INCLUDED
