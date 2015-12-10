#include "scroll.h"
#include <iostream>

namespace inputstorm {
namespace input {

void scroll::bind(std::function<void(Vector2d const&)> func) {
  /// Bind a function to scrolling
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to scroll, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  binding = func;
}

void scroll::unbind() {
  binding = [](Vector2d const &change __attribute__((__unused__))){};           // noop
}

void scroll::execute(Vector2d const &offset) {
  /// Call the function associated with scrolling
  binding(offset);
}

}
}
