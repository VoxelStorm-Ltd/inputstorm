#include "callbacks.h"
#include "inputstorm/manager.h"
#ifdef DEBUG_INPUTSTORM
  #include <iostream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
namespace callback {

void window_refresh(GLFWwindow *thiswindow) {
  /// Apply relevant action for the window getting a refresh request
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Executing window refresh callback" << std::endl;
  #endif // DEBUG_INPUTSTORM
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_refresh();
}

}
}
