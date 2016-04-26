#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void cursor(GLFWwindow *thiswindow,
            double x,
            double y) {
  /// React to cursor position updates
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->cursor.execute({x, y});
}

}
}
