#include "callbacks.h"
#include "inputstorm/manager.h"
#include "vmath.h"

namespace inputstorm {
namespace callback {

void scroll(GLFWwindow *thiswindow,
            double xoffset,
            double yoffset) {
  /// Apply relevant action for using the mouse scroll
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->scroll.execute({xoffset, yoffset});
}

}
}
