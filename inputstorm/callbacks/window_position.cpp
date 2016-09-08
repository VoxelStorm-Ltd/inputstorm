#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void window_position(GLFWwindow *thiswindow,
                     int xpos,
                     int ypos) {
  /// Apply relevant action for the window position updating
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->window.execute_position({xpos, ypos});
}

}
}
