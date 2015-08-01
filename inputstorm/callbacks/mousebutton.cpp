#include "inputstorm/manager.h"
//#include "inputstorm/input/mousebutton.h"
#ifndef NDEBUG
  #include <iostream>
#endif

namespace inputstorm {
namespace callback {

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
  parent->mousebutton.execute(static_cast<input::mousebutton::buttontype>(button),
                              static_cast<input::key::action>(action),
                              static_cast<input::key::mod>(mods));
}

}
}
