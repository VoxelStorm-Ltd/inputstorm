#include "inputstorm/manager.h"
#ifndef NDEBUG
  #include <iostream>
#endif

namespace inputstorm {

void cursor(GLFWwindow *thiswindow __attribute__((__unused__)),
            double x,
            double y) {
  /// React to cursor position updates
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->execute_cursor({x, y});
}

}
