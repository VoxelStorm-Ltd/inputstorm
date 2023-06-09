#include "manager.h"
#include <iostream>
#include "callbacks/callbacks.h"
#include "timestorm/timer.h"

namespace inputstorm {

manager::manager() {
  /// Default constructor - requires separate init() call
}
manager::manager(GLFWwindow &thiswindow)
  : current_window(&thiswindow) {
  /// Specific initialising constructor
  init(thiswindow);
}

void manager::init(GLFWwindow &thiswindow) {
  /// Initialise
  if(initialised) {
    return;
  }
  timestorm::timer<unsigned int> timer("InputStorm: Initialised in ");
  current_window = &thiswindow;
  key.init();
  mousebutton.init();
  joystick.init();

  // set callbacks
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Setting callbacks on GLFW window " << current_window << std::endl;
  #endif // DEBUG_INPUTSTORM
  glfwSetWindowUserPointer(      current_window, this);                         // have this class passed to future callbacks
  glfwSetKeyCallback(            current_window, callback::key);
  glfwSetCursorPosCallback(      current_window, callback::cursor);
  glfwSetCursorEnterCallback(    current_window, callback::cursor_enter);
  glfwSetMouseButtonCallback(    current_window, callback::mousebutton);
  glfwSetScrollCallback(         current_window, callback::scroll);
  glfwSetCharCallback(           current_window, callback::text);
  glfwSetWindowPosCallback(      current_window, callback::window_position);
  glfwSetWindowSizeCallback(     current_window, callback::window_size);
  glfwSetWindowCloseCallback(    current_window, callback::window_close);
  glfwSetWindowRefreshCallback(  current_window, callback::window_refresh);
  glfwSetWindowFocusCallback(    current_window, callback::window_focus);
  glfwSetWindowIconifyCallback(  current_window, callback::window_iconify);
  glfwSetFramebufferSizeCallback(current_window, callback::framebuffer_size);

  initialised = true;
}

manager::~manager() {
  /// Default destructor
  shutdown();
}

void manager::shutdown() {
  /// Shut down and release callbacks
  if(!initialised) {
    return;
  }
  std::cout << "InputStorm: Shutting down." << std::endl;
  glfwSetWindowUserPointer(      current_window, nullptr);                      // clear the user pointer
  glfwSetKeyCallback(            current_window, nullptr);                      // unset callbacks to avoid unpleasant accidents
  glfwSetCursorPosCallback(      current_window, nullptr);
  glfwSetCursorEnterCallback(    current_window, nullptr);
  glfwSetMouseButtonCallback(    current_window, nullptr);
  glfwSetScrollCallback(         current_window, nullptr);
  glfwSetCharCallback(           current_window, nullptr);
  glfwSetWindowPosCallback(      current_window, nullptr);
  glfwSetWindowSizeCallback(     current_window, nullptr);
  glfwSetWindowCloseCallback(    current_window, nullptr);
  glfwSetWindowRefreshCallback(  current_window, nullptr);
  glfwSetWindowFocusCallback(    current_window, nullptr);
  glfwSetWindowIconifyCallback(  current_window, nullptr);
  glfwSetFramebufferSizeCallback(current_window, nullptr);

  initialised = false;
}

bool manager::is_initialised() {
  return initialised;
}

void manager::copy_bindings(manager const &other) {
  /// Duplicate the bindings from a different input manager object
  timestorm::timer<unsigned int> timer("InputStorm: Copied bindings in ");
  key         = other.key;
  cursor      = other.cursor;
  mousebutton = other.mousebutton;
  scroll      = other.scroll;
  joystick    = other.joystick;
  text        = other.text;
  window      = other.window;
}

unsigned int manager::save_bindings() {
  /// Back up the current bindings to the internal store and return a unique ID
  unsigned int i = 0;
  for(; i != std::numeric_limits<unsigned int>::max(); ++i) {
    // iterate until we find a free integer
    if(saved_bindings.find(i) == saved_bindings.end()) {
      break;
    }
  }
  save_bindings(i);
  return i;
}
void manager::save_bindings(unsigned int savenumber) {
  /// Back up the current bindings to a specific ID in the internal store, overwriting if it exists already
  std::stringstream ss;
  ss << "InputStorm: Saved bindings to slot " << savenumber << " in ";
  timestorm::timer<unsigned int> timer(ss.str());
  saved_bindingtype &save = saved_bindings[savenumber];
  save.key         = key;
  save.cursor      = cursor;
  save.mousebutton = mousebutton;
  save.scroll      = scroll;
  save.joystick    = joystick;
  save.text        = text;
  save.window      = window;
}
void manager::load_bindings(unsigned int savenumber) {
  /// Load a saved set of bindings referenced by the specified ID
  std::stringstream ss;
  ss << "InputStorm: Loaded bindings from slot " << savenumber << " in ";
  timestorm::timer<unsigned int> timer(ss.str());
  //saved_bindingtype const &save(saved_bindings.at(savenumber));
  saved_bindingtype &save = saved_bindings[savenumber];
  key         = save.key;
  cursor      = save.cursor;
  mousebutton = save.mousebutton;
  scroll      = save.scroll;
  joystick    = save.joystick;
  text        = save.text;
  window      = save.window;
}
void manager::free_bindings(unsigned int savenumber) {
  /// Delete a binding save referenced by the specified ID
  std::stringstream ss;
  ss << "InputStorm: Erased the saved binding at slot " << savenumber << " in ";
  timestorm::timer<unsigned int> timer(ss.str());
  saved_bindings.erase(savenumber);
}
std::vector<unsigned int> manager::list_saved_bindings() {
  /// Return all saved bindings we know about
  std::vector<unsigned int> out;
  for(auto const &it : saved_bindings) {
    out.emplace_back(it.first);
  }
  return out;
}

}
