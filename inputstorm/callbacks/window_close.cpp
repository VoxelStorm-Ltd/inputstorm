#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void window_close(GLFWwindow *thiswindow) {
  /// Apply relevant action for the window receiving a close request
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_close();
  glfwSetWindowShouldClose(thiswindow, GLFW_FALSE);                             // reset the close flag after firing once
}

}
}
