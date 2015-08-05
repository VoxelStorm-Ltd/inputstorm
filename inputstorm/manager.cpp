#include "manager.h"
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
  //std::cout << "InputStorm: Setting callbacks..." << std::endl;
  glfwSetWindowUserPointer(  current_window, this);                             // have this class passed to future callbacks
  glfwSetKeyCallback(        current_window, callback::key);
  glfwSetCursorPosCallback(  current_window, callback::cursor);
  glfwSetCursorEnterCallback(current_window, callback::cursor_enter);
  glfwSetMouseButtonCallback(current_window, callback::mousebutton);
  glfwSetScrollCallback(     current_window, callback::scroll);

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
  glfwSetWindowUserPointer(  current_window, nullptr);                          // clear the user pointer
  glfwSetKeyCallback(        current_window, nullptr);                          // unset callbacks to avoid unpleasant accidents
  glfwSetCursorPosCallback(  current_window, nullptr);
  glfwSetCursorEnterCallback(current_window, nullptr);
  glfwSetMouseButtonCallback(current_window, nullptr);
  glfwSetScrollCallback(     current_window, nullptr);

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
