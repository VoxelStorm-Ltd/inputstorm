  std::function<void()>             leave_binding = []{};                       // cursor leaves the window

public:
#ifndef INPUTSTORM_INPUT_CURSOR_H_INCLUDED
  void bind(std::function<void(vec2d const&)> func);
#define INPUTSTORM_INPUT_CURSOR_H_INCLUDED
  void bind_enter(std::function<void()> func);

  void bind_leave(std::function<void()> func);

#include <functional>
  void unbind();
#include "vectorstorm/vector/vector2_forward.h"
  void unbind_enter();

  void unbind_leave();
namespace inputstorm {

namespace input {
  void execute(vec2d const &change) const;

  void execute_enter()              const;
struct cursor {
  void execute_leave()              const;
  // data
};
private:

  std::function<void(vec2d const&)> binding       = [](vec2d const &change __attribute__((__unused__))){}; // callback function for cursor movement
}
  std::function<void()>             enter_binding = []{};                       // cursor enters the window
}
  std::function<void()>             leave_binding = []{};                       // cursor leaves the window


#endif // INPUTSTORM_INPUT_CURSOR_H_INCLUDED
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
