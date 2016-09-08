#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void window_iconify(GLFWwindow *thiswindow, int iconified) {
  /// Apply relevant action for the window being minimised or restored
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  if(iconified == GLFW_TRUE) {
    parent->window.execute_minimise();
  } else {
    parent->window.execute_restore();
  }
}

}
}
