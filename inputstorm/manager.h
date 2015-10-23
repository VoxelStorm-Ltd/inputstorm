#ifndef INPUTSTORM_MANAGER_H_INCLUDED
#define INPUTSTORM_MANAGER_H_INCLUDED

#include <unordered_map>
#include "input/key.h"
#include "input/cursor.h"
#include "input/mousebutton.h"
#include "input/scroll.h"
#include "input/joystick.h"

namespace inputstorm {

class manager {
public:
  input::key         key;                                                       // keyboard
  input::cursor      cursor;                                                    // cursor
  input::mousebutton mousebutton;                                               // mouse buttons
  input::scroll      scroll;                                                    // scroll wheel
  input::joystick    joystick;                                                  // joystick / gamepad / controller

private:
  GLFWwindow *current_window = nullptr;                                         // the GLFW window this input manager is handling

  struct saved_bindingtype {
    input::key         key;                                                     // keyboard
    input::cursor      cursor;                                                  // cursor
    input::mousebutton mousebutton;                                             // mouse buttons
    input::scroll      scroll;                                                  // scroll wheel
    input::joystick    joystick;                                                // joystick / gamepad / controller
  };
  std::unordered_map<unsigned int, saved_bindingtype> saved_bindings;           // a collection of bindings we can load at any time

  bool initialised = false;                                                     // whether this has been initialised

public:
  manager();
  manager(GLFWwindow &thiswindow);
  ~manager();

  void init(GLFWwindow &thiswindow);
  void shutdown();

  bool is_initialised() __attribute__((__pure__));

public:
  void copy_bindings(manager const &other);

  unsigned int save_bindings();
  void save_bindings(unsigned int savenumber);
  void load_bindings(unsigned int savenumber);
  void free_bindings(unsigned int savenumber);
  std::vector<unsigned int> list_saved_bindings();
};

}

#endif // INPUTSTORM_MANAGER_H_INCLUDED
