#include "callbacks.h"
#include "inputstorm/manager.h"
#include "vmath.h"
#ifndef NDEBUG
  #include <iostream>
#endif

namespace inputstorm {
namespace callback {

void scroll(GLFWwindow *thiswindow,
            double xoffset,
            double yoffset) {
  /// Apply relevant action for using the mouse scroll
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  #ifndef NDEBUG
    std::cout << "InputStorm: DEBUG: Scrolled " << xoffset << ", " << yoffset << std::endl;
  #endif // NDEBUG
  parent->scroll.execute({xoffset, yoffset});
}

}
}
