#include "callbacks.h"
#include "inputstorm/manager.h"
#ifdef DEBUG_INPUTSTORM
  #include <iostream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
namespace callback {

void window_close(GLFWwindow *thiswindow) {
  /// Apply relevant action for the window receiving a close request
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Executing window close callback" << std::endl;
  #endif // DEBUG_INPUTSTORM
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_close();
  glfwSetWindowShouldClose(thiswindow, GLFW_FALSE);                             // reset the close flag after firing once
}

}
}
