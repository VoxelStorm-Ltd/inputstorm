#include "inputstorm/manager.h"
#ifndef NDEBUG
  #include <iostream>
#endif

namespace inputstorm {

void cursor_enter(GLFWwindow *thiswindow, int entered) {
  /// Callback for cursor entering or exiting the window
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  if(static_cast<bool>(entered)) {
    // The cursor entered the client area of the window
    #ifndef NDEBUG
      std::cout << "InputStorm: DEBUG: The cursor entered the window." << std::endl;
    #endif // NDEBUG
    parent->execute_cursor_enter();
  } else {
    // The cursor left the client area of the window
    #ifndef NDEBUG
      std::cout << "InputStorm: DEBUG: The cursor left the window." << std::endl;
    #endif // NDEBUG
    parent->execute_cursor_leave();
  }
}

}
