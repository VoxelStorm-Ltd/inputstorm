#include "callbacks.h"
#include "inputstorm/manager.h"
#ifndef NDEBUG
  #include <iostream>
#endif

namespace inputstorm {

void scroll(GLFWwindow *thiswindow,
            double xoffset,
            double yoffset) {
  /// Apply relevant action for using the mouse scroll
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  #ifndef NDEBUG
    std::cout << "InputStorm: DEBUG: Scrolled " << xoffset << ", " << yoffset << std::endl;
  #endif // NDEBUG
  parent->execute_scroll({xoffset, yoffset});
}

}
