#include "inputstorm/manager.h"
#ifndef NDEBUG
  #include <iostream>
#endif

namespace inputstorm {
namespace callback {

void key(GLFWwindow *thiswindow,
         int key,
         int scancode __attribute__((__unused__)),
         int action,
         int mods) {
  /// All the switch-type controls, rather than polled realtime controls
  // get our manager's handle back from GLFW
  manager *parent = static_cast<manager*>(glfwGetWindowUserPointer(thiswindow));
  if(key < 0) {
    #ifndef NDEBUG
      std::cout << "InputStorm: DEBUG: Unknown key pressed, scancode " << scancode << std::endl;
    #endif // NDEBUG
    return;
  }
  parent->key.execute(static_cast<input::key::keytype>(key),
                      static_cast<input::key::action>(action),
                      static_cast<input::key::mod>(mods));
}

}
}
