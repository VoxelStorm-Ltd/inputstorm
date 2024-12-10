#pragma once

#include <functional>
#include "vectorstorm/vector/vector2_forward.h"

namespace inputstorm::input {

class cursor {
  // data
  std::function<void(vec2d const&)> binding       = [](vec2d const &change [[maybe_unused]]){}; // callback function for cursor movement
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
