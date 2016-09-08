#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void window_refresh(GLFWwindow *thiswindow) {
  /// Apply relevant action for the window getting a refresh request
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_refresh();
}

}
}
