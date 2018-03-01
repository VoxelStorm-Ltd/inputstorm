#include "cursor.h"
#include <iostream>
#ifdef DEBUG_INPUTSTORM
  #include "vectorstorm/vector/vector2.h"
#endif // DEBUG_INPUTSTORM

namespace inputstorm::input {

void cursor::bind(std::function<void(vec2d const&)> func) {
  /// Bind a function to cursor movement
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to cursor movement, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  binding = func;
}
void cursor::bind_enter(std::function<void()> func) {
  /// Bind a function to cursor entering the window
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to cursor entering the window, this will throw an exception if called!" << std::endl;
    }
  #endif
  enter_binding = func;
}
void cursor::bind_leave(std::function<void()> func) {
  /// Bind a function to cursor leaving the window
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to cursor leaving the window, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  leave_binding = func;
}

void cursor::unbind() {
  binding = [](vec2d const &change [[maybe_unused]]){};                         // noop
}
void cursor::unbind_enter() {
  enter_binding = []{};                                                         // noop
}
void cursor::unbind_leave() {
  leave_binding = []{};                                                         // noop
}

void cursor::execute(vec2d const &change) const {
  /// Call the function associated with cursor movements
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Cursor position " << change << std::endl;
  #endif // DEBUG_INPUTSTORM
  binding(change);
}
void cursor::execute_enter() const {
  /// Call the function associated with the cursor entering the window
  enter_binding();
}
void cursor::execute_leave() const {
  /// Call the function associated with the cursor leaving the window
  leave_binding();
}

}
