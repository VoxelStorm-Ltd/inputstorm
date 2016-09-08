#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void framebuffer_size(GLFWwindow *thiswindow,
                      int width,
                      int height) {
  /// Apply relevant action for the window's framebuffer size updating
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_framebuffer_size({width, height});
}

}
}
