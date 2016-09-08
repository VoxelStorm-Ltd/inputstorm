#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void window_size(GLFWwindow *thiswindow,
                 int width,
                 int height) {
  /// Apply relevant action for the window size updating
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_resize({width, height});
}

}
}
