#include "callbacks.h"
#include "inputstorm/manager.h"
#ifdef DEBUG_INPUTSTORM
  #include <iostream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
namespace callback {

void framebuffer_size(GLFWwindow *thiswindow,
                      int width,
                      int height) {
  /// Apply relevant action for the window's framebuffer size updating
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Executing framebuffer resize callback" << std::endl;
  #endif // DEBUG_INPUTSTORM
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_framebuffer_size({width, height});
}

}
}
