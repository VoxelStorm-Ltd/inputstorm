#include "callbacks.h"
#include "inputstorm/manager.h"
#ifdef DEBUG_INPUTSTORM
  #include <iostream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
namespace callback {

void window_focus(GLFWwindow *thiswindow, int focused) {
  /// Apply relevant action for the window gaining or losing focus
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  if(focused == GLFW_TRUE) {
    #ifdef DEBUG_INPUTSTORM
      std::cout << "InputStorm: DEBUG: Executing window focus gain callback" << std::endl;
    #endif // DEBUG_INPUTSTORM
    parent->window.execute_focus_gain();
  } else {
    #ifdef DEBUG_INPUTSTORM
      std::cout << "InputStorm: DEBUG: Executing window focus lose callback" << std::endl;
    #endif // DEBUG_INPUTSTORM
    parent->window.execute_focus_lose();
  }
}

}
}
