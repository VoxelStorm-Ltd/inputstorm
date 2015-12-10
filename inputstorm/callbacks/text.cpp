#include "callbacks.h"
#include "inputstorm/manager.h"

namespace inputstorm {
namespace callback {

void text(GLFWwindow *thiswindow, unsigned int codepoint) {
  /// React to cursor position updates
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  parent->text.execute(codepoint);
}

}
}
