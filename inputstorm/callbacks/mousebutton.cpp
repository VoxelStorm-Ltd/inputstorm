#include "callbacks.h"
#include "inputstorm/manager.h"
#ifndef NDEBUG
  #include <iostream>
#endif

namespace inputstorm {

void mousebutton(GLFWwindow *thiswindow,
                 int button,
                 int action,
                 int mods) {
  /// React to mouse button presses and releases
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  if(button < 0) {
    #ifndef NDEBUG
      std::cout << "InputStorm: DEBUG: Unknown button pressed, this should probably not happen" << std::endl;
    #endif // NDEBUG
    return;
  }
  parent->execute_mousebutton(static_cast<mousebuttontype>(button),
                              static_cast<keyactiontype>(action),
                              static_cast<keymodtype>(mods));
}

}
