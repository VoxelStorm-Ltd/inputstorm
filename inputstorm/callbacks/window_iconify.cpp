#include "callbacks.h"
#include "inputstorm/manager.h"
#ifdef DEBUG_INPUTSTORM
  #include <iostream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
namespace callback {

void window_iconify(GLFWwindow *thiswindow, int iconified) {
  /// Apply relevant action for the window being minimised or restored
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  if(iconified == GLFW_TRUE) {
    #ifdef DEBUG_INPUTSTORM
      std::cout << "InputStorm: DEBUG: Executing window minimise callback" << std::endl;
    #endif // DEBUG_INPUTSTORM
    parent->window.execute_minimise();
  } else {
    #ifdef DEBUG_INPUTSTORM
      std::cout << "InputStorm: DEBUG: Executing window restore callback" << std::endl;
    #endif // DEBUG_INPUTSTORM
    parent->window.execute_restore();
  }
}

}
}
