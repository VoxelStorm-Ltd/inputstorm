#include "scroll.h"
#ifndef NDEBUG
  #include <iostream>
#endif // NDEBUG

namespace inputstorm {
namespace input {

std::string scroll::get_name(scroll::direction this_direction) const {
  /// Return the this_key name from its GLFW this_key ID number
  switch(this_direction) {
  case direction::RIGHT:
    return "RIGHT";
  case direction::LEFT:
    return "LEFT";
  case direction::UP:
    return "UP";
  case direction::DOWN:
    return "DOWN";
  default:
    return "UNKNOWN";
  }
}

void scroll::bind(std::function<void(vec2d const&)> func) {
  /// Bind a function to scrolling
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to scroll, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  binding = func;
}

void scroll::unbind() {
  binding = [](vec2d const &change __attribute__((__unused__))){};              // noop
}

void scroll::execute(vec2d const &offset) {
  /// Call the function associated with scrolling
  binding(offset);
}

}
}
