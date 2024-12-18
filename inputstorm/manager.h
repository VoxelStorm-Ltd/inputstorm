#pragma once

#include <unordered_map>
#include "input/cursor.h"
#include "input/mousebutton.h"
#include "input/scroll.h"
#include "input/joystick.h"
#include "input/text.h"
#include "input/window.h"

namespace inputstorm {

class manager {
public:
  input::key         key;                                                       // keyboard
  input::cursor      cursor;                                                    // cursor
  input::mousebutton mousebutton;                                               // mouse buttons
  input::scroll      scroll;                                                    // scroll wheel
  input::joystick    joystick;                                                  // joystick / gamepad / controller
  input::text        text;                                                      // text input
  input::window      window;                                                    // window events

private:
  GLFWwindow *current_window = nullptr;                                         // the GLFW window this input manager is handling

  struct saved_bindingtype {
    input::key         key;                                                     // keyboard
    input::cursor      cursor;                                                  // cursor
    input::mousebutton mousebutton;                                             // mouse buttons
    input::scroll      scroll;                                                  // scroll wheel
    input::joystick    joystick;                                                // joystick / gamepad / controller
    input::text        text;                                                    // text input
    input::window      window;                                                  // window events
  };
  std::unordered_map<unsigned int, saved_bindingtype> saved_bindings;           // a collection of bindings we can load at any time

public:
  bool initialised = false;                                                     // whether this has been initialised

  manager();
  explicit manager(GLFWwindow &thiswindow);
  ~manager();

  void init(GLFWwindow &thiswindow);
  void shutdown();

  bool is_initialised() __attribute__((__pure__));

  // manage saved raw binding sets
  void copy_bindings(manager const &other);
  unsigned int save_bindings();
  void save_bindings(unsigned int savenumber);
  void load_bindings(unsigned int savenumber);
  void free_bindings(unsigned int savenumber);
  std::vector<unsigned int> list_saved_bindings();
};

}
