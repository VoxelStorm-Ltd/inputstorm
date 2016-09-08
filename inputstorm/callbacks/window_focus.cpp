#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void window_focus(GLFWwindow *thiswindow, int focused) {
  /// Apply relevant action for the window gaining or losing focus
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  if(focused == GLFW_TRUE) {
    parent->window.execute_focus_gain();
  } else {
    parent->window.execute_focus_lose();
  }
}

}
}
