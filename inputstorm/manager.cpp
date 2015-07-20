#include "manager.h"
#include <iostream>
#include <sstream>
#include "callbacks/callbacks.h"
#include "timestorm/timer.h"

namespace inputstorm {

unsigned int constexpr manager::max_key;
unsigned int constexpr manager::max_key_mods;
unsigned int constexpr manager::max_key_action;
unsigned int constexpr manager::max_mousebutton;
unsigned int constexpr manager::max_mouse_action;
unsigned int constexpr manager::max_joystick;
unsigned int constexpr manager::max_joystick_axis;
unsigned int constexpr manager::max_joystick_button;
unsigned int constexpr manager::max_joystick_button_action;

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
  timestorm::timer<unsigned int> timer("InputStorm: Initialised in ");
  current_window = &thiswindow;
  //std::cout << "InputStorm: Initialising keymap..." << std::endl;
  // create default key bindings and initialise key names
  for(keytype key = 0; key <= GLFW_KEY_LAST; ++key) {
    // this is a sparse array, and we don't know which we'll name - so default-name them all first, and override the specific ones after
    std::stringstream ss;
    ss << "UNKNOWN " << key;
    key_name_at(key) = ss.str();
  }
  key_name_at(0                     ) = "UNKNOWN";                              // manually set to use 0 instead of negative numbers
  key_name_at(GLFW_KEY_SPACE        ) = "SPACE";
  key_name_at(GLFW_KEY_APOSTROPHE   ) = "APOSTROPHE";
  key_name_at(GLFW_KEY_COMMA        ) = "COMMA";
  key_name_at(GLFW_KEY_MINUS        ) = "MINUS";
  key_name_at(GLFW_KEY_PERIOD       ) = "PERIOD";
  key_name_at(GLFW_KEY_SLASH        ) = "SLASH";
  key_name_at(GLFW_KEY_0            ) = "0";
  key_name_at(GLFW_KEY_1            ) = "1";
  key_name_at(GLFW_KEY_2            ) = "2";
  key_name_at(GLFW_KEY_3            ) = "3";
  key_name_at(GLFW_KEY_4            ) = "4";
  key_name_at(GLFW_KEY_5            ) = "5";
  key_name_at(GLFW_KEY_6            ) = "6";
  key_name_at(GLFW_KEY_7            ) = "7";
  key_name_at(GLFW_KEY_8            ) = "8";
  key_name_at(GLFW_KEY_9            ) = "9";
  key_name_at(GLFW_KEY_SEMICOLON    ) = "SEMICOLON";
  key_name_at(GLFW_KEY_EQUAL        ) = "EQUAL";
  key_name_at(GLFW_KEY_A            ) = "A";
  key_name_at(GLFW_KEY_B            ) = "B";
  key_name_at(GLFW_KEY_C            ) = "C";
  key_name_at(GLFW_KEY_D            ) = "D";
  key_name_at(GLFW_KEY_E            ) = "E";
  key_name_at(GLFW_KEY_F            ) = "F";
  key_name_at(GLFW_KEY_G            ) = "G";
  key_name_at(GLFW_KEY_H            ) = "H";
  key_name_at(GLFW_KEY_I            ) = "I";
  key_name_at(GLFW_KEY_J            ) = "J";
  key_name_at(GLFW_KEY_K            ) = "K";
  key_name_at(GLFW_KEY_L            ) = "L";
  key_name_at(GLFW_KEY_M            ) = "M";
  key_name_at(GLFW_KEY_N            ) = "N";
  key_name_at(GLFW_KEY_O            ) = "O";
  key_name_at(GLFW_KEY_P            ) = "P";
  key_name_at(GLFW_KEY_Q            ) = "Q";
  key_name_at(GLFW_KEY_R            ) = "R";
  key_name_at(GLFW_KEY_S            ) = "S";
  key_name_at(GLFW_KEY_T            ) = "T";
  key_name_at(GLFW_KEY_U            ) = "U";
  key_name_at(GLFW_KEY_V            ) = "V";
  key_name_at(GLFW_KEY_W            ) = "W";
  key_name_at(GLFW_KEY_X            ) = "X";
  key_name_at(GLFW_KEY_Y            ) = "Y";
  key_name_at(GLFW_KEY_Z            ) = "Z";
  key_name_at(GLFW_KEY_LEFT_BRACKET ) = "LEFT_BRACKET";
  key_name_at(GLFW_KEY_BACKSLASH    ) = "BACKSLASH";
  key_name_at(GLFW_KEY_RIGHT_BRACKET) = "RIGHT_BRACKET";
  key_name_at(GLFW_KEY_GRAVE_ACCENT ) = "GRAVE_ACCENT";
  key_name_at(GLFW_KEY_WORLD_1      ) = "WORLD_1";
  key_name_at(GLFW_KEY_WORLD_2      ) = "WORLD_2";
  key_name_at(GLFW_KEY_ESCAPE       ) = "ESCAPE";
  key_name_at(GLFW_KEY_ENTER        ) = "ENTER";
  key_name_at(GLFW_KEY_TAB          ) = "TAB";
  key_name_at(GLFW_KEY_BACKSPACE    ) = "BACKSPACE";
  key_name_at(GLFW_KEY_INSERT       ) = "INSERT";
  key_name_at(GLFW_KEY_DELETE       ) = "DELETE";
  key_name_at(GLFW_KEY_RIGHT        ) = "RIGHT";
  key_name_at(GLFW_KEY_LEFT         ) = "LEFT";
  key_name_at(GLFW_KEY_DOWN         ) = "DOWN";
  key_name_at(GLFW_KEY_UP           ) = "UP";
  key_name_at(GLFW_KEY_PAGE_UP      ) = "PAGE_UP";
  key_name_at(GLFW_KEY_PAGE_DOWN    ) = "PAGE_DOWN";
  key_name_at(GLFW_KEY_HOME         ) = "HOME";
  key_name_at(GLFW_KEY_END          ) = "END";
  key_name_at(GLFW_KEY_CAPS_LOCK    ) = "CAPS_LOCK";
  key_name_at(GLFW_KEY_SCROLL_LOCK  ) = "SCROLL_LOCK";
  key_name_at(GLFW_KEY_NUM_LOCK     ) = "NUM_LOCK";
  key_name_at(GLFW_KEY_PRINT_SCREEN ) = "PRINT_SCREEN";
  key_name_at(GLFW_KEY_PAUSE        ) = "PAUSE";
  key_name_at(GLFW_KEY_F1           ) = "F1";
  key_name_at(GLFW_KEY_F2           ) = "F2";
  key_name_at(GLFW_KEY_F3           ) = "F3";
  key_name_at(GLFW_KEY_F4           ) = "F4";
  key_name_at(GLFW_KEY_F5           ) = "F5";
  key_name_at(GLFW_KEY_F6           ) = "F6";
  key_name_at(GLFW_KEY_F7           ) = "F7";
  key_name_at(GLFW_KEY_F8           ) = "F8";
  key_name_at(GLFW_KEY_F9           ) = "F9";
  key_name_at(GLFW_KEY_F10          ) = "F10";
  key_name_at(GLFW_KEY_F11          ) = "F11";
  key_name_at(GLFW_KEY_F12          ) = "F12";
  key_name_at(GLFW_KEY_F13          ) = "F13";
  key_name_at(GLFW_KEY_F14          ) = "F14";
  key_name_at(GLFW_KEY_F15          ) = "F15";
  key_name_at(GLFW_KEY_F16          ) = "F16";
  key_name_at(GLFW_KEY_F17          ) = "F17";
  key_name_at(GLFW_KEY_F18          ) = "F18";
  key_name_at(GLFW_KEY_F19          ) = "F19";
  key_name_at(GLFW_KEY_F20          ) = "F20";
  key_name_at(GLFW_KEY_F21          ) = "F21";
  key_name_at(GLFW_KEY_F22          ) = "F22";
  key_name_at(GLFW_KEY_F23          ) = "F23";
  key_name_at(GLFW_KEY_F24          ) = "F24";
  key_name_at(GLFW_KEY_F25          ) = "F25";
  key_name_at(GLFW_KEY_KP_0         ) = "KEYPAD 0";
  key_name_at(GLFW_KEY_KP_1         ) = "KEYPAD 1";
  key_name_at(GLFW_KEY_KP_2         ) = "KEYPAD 2";
  key_name_at(GLFW_KEY_KP_3         ) = "KEYPAD 3";
  key_name_at(GLFW_KEY_KP_4         ) = "KEYPAD 4";
  key_name_at(GLFW_KEY_KP_5         ) = "KEYPAD 5";
  key_name_at(GLFW_KEY_KP_6         ) = "KEYPAD 6";
  key_name_at(GLFW_KEY_KP_7         ) = "KEYPAD 7";
  key_name_at(GLFW_KEY_KP_8         ) = "KEYPAD 8";
  key_name_at(GLFW_KEY_KP_9         ) = "KEYPAD 9";
  key_name_at(GLFW_KEY_KP_DECIMAL   ) = "KEYPAD DECIMAL";
  key_name_at(GLFW_KEY_KP_DIVIDE    ) = "KEYPAD DIVIDE";
  key_name_at(GLFW_KEY_KP_MULTIPLY  ) = "KEYPAD MULTIPLY";
  key_name_at(GLFW_KEY_KP_SUBTRACT  ) = "KEYPAD SUBTRACT";
  key_name_at(GLFW_KEY_KP_ADD       ) = "KEYPAD ADD";
  key_name_at(GLFW_KEY_KP_ENTER     ) = "KEYPAD ENTER";
  key_name_at(GLFW_KEY_KP_EQUAL     ) = "KEYPAD EQUAL";
  key_name_at(GLFW_KEY_LEFT_SHIFT   ) = "LEFT SHIFT";
  key_name_at(GLFW_KEY_LEFT_CONTROL ) = "LEFT CONTROL";
  key_name_at(GLFW_KEY_LEFT_ALT     ) = "LEFT ALT";
  key_name_at(GLFW_KEY_LEFT_SUPER   ) = "LEFT SUPER";
  key_name_at(GLFW_KEY_RIGHT_SHIFT  ) = "RIGHT SHIFT";
  key_name_at(GLFW_KEY_RIGHT_CONTROL) = "RIGHT CONTROL";
  key_name_at(GLFW_KEY_RIGHT_ALT    ) = "RIGHT ALT";
  key_name_at(GLFW_KEY_RIGHT_SUPER  ) = "RIGHT SUPER";
  key_name_at(GLFW_KEY_MENU         ) = "MENU";

  key_mod_names[static_cast<int>(keymodtype::NONE                   )] = "NONE";
  key_mod_names[static_cast<int>(keymodtype::SHIFT                  )] = "SHIFT";
  key_mod_names[static_cast<int>(keymodtype::CONTROL                )] = "CONTROL";
  key_mod_names[static_cast<int>(keymodtype::SHIFT_CONTROL          )] = "SHIFT_CONTROL";
  key_mod_names[static_cast<int>(keymodtype::ALT                    )] = "ALT";
  key_mod_names[static_cast<int>(keymodtype::SHIFT_ALT              )] = "SHIFT_ALT";
  key_mod_names[static_cast<int>(keymodtype::CONTROL_ALT            )] = "CONTROL_ALT";
  key_mod_names[static_cast<int>(keymodtype::SHIFT_CONTROL_ALT      )] = "SHIFT_CONTROL_ALT";
  key_mod_names[static_cast<int>(keymodtype::SUPER                  )] = "SUPER";
  key_mod_names[static_cast<int>(keymodtype::SHIFT_SUPER            )] = "SHIFT_SUPER";
  key_mod_names[static_cast<int>(keymodtype::CONTROL_SUPER          )] = "CONTROL_SUPER";
  key_mod_names[static_cast<int>(keymodtype::SHIFT_CONTROL_SUPER    )] = "SHIFT_CONTROL_SUPER";
  key_mod_names[static_cast<int>(keymodtype::ALT_SUPER              )] = "ALT_SUPER";
  key_mod_names[static_cast<int>(keymodtype::SHIFT_ALT_SUPER        )] = "SHIFT_ALT_SUPER";
  key_mod_names[static_cast<int>(keymodtype::CONTROL_ALT_SUPER      )] = "CONTROL_ALT_SUPER";
  key_mod_names[static_cast<int>(keymodtype::SHIFT_CONTROL_ALT_SUPER)] = "SHIFT_CONTROL_ALT_SUPER";

  key_action_names[static_cast<int>(keyactiontype::RELEASE)] = "RELEASE";
  key_action_names[static_cast<int>(keyactiontype::PRESS  )] = "PRESS";
  key_action_names[static_cast<int>(keyactiontype::REPEAT )] = "REPEAT";

  mousebutton_name_at(GLFW_MOUSE_BUTTON_1) = "MOUSE LEFT";
  mousebutton_name_at(GLFW_MOUSE_BUTTON_2) = "MOUSE RIGHT";
  mousebutton_name_at(GLFW_MOUSE_BUTTON_3) = "MOUSE MIDDLE";
  mousebutton_name_at(GLFW_MOUSE_BUTTON_4) = "MOUSE 4";
  mousebutton_name_at(GLFW_MOUSE_BUTTON_5) = "MOUSE 5";
  mousebutton_name_at(GLFW_MOUSE_BUTTON_6) = "MOUSE 6";
  mousebutton_name_at(GLFW_MOUSE_BUTTON_7) = "MOUSE 7";
  mousebutton_name_at(GLFW_MOUSE_BUTTON_8) = "MOUSE 8";

  // assign a safe default function to all keys
  for(keymodtype mods = keymodtype::NONE; mods != static_cast<keymodtype>(max_key_mods); mods = static_cast<keymodtype>(static_cast<int>(mods) + 1)) {
    for(keyactiontype action = keyactiontype::RELEASE; action != static_cast<keyactiontype>(max_key_action); action = static_cast<keyactiontype>(static_cast<int>(action) + 1)) {
      for(keytype key = 0; key != max_key; ++key) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound key function called on key " << key << " (" << get_key_name(key) << ")";
          if(mods != keymodtype::NONE) {
            ss << " mods " << get_keymod_name(mods);
          }
          ss << " action " << get_keyaction_name(action);
          if(action == keyactiontype::PRESS) {
            bind_key(key, action, mods, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind_key(key, action, mods, []{});
          }
        #else
          bind_key(key, action, mods, []{});                                    // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }
  // assign a safe default function to all mouse buttons
  for(keymodtype mods = keymodtype::NONE; mods != static_cast<keymodtype>(max_key_mods); mods = static_cast<keymodtype>(static_cast<int>(mods) + 1)) {
    for(keyactiontype action = keyactiontype::RELEASE; action != static_cast<keyactiontype>(max_mouse_action); action = static_cast<keyactiontype>(static_cast<int>(action) + 1)) {
      for(mousebuttontype button = 0; button != max_mousebutton; ++button) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound mouse function called on button " << button << " (" << get_mousebutton_name(button) << ")";
          if(mods != keymodtype::NONE) {
            ss << " mods " << get_keymod_name(mods);
          }
          ss << " action " << get_keyaction_name(action);
          if(action == keyactiontype::PRESS) {
            bind_mousebutton(button, action, mods, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind_mousebutton(button, action, mods, []{});
          }
        #else
          bind_mousebutton(button, action, mods, []{});                         // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }
  // assign a safe default function to all joystick axes
  for(unsigned int axis = 0; axis != max_joystick_axis; ++axis) {
    for(unsigned int joystick = 0; joystick != max_joystick; ++joystick) {
      #ifdef DEBUG_INPUTSTORM
        std::stringstream ss;
        ss << "InputStorm: DEBUG: unbound joystick function called on axis " << axis;
        if(joystick != 0) {
          ss << " on joystick " << joystick;
        }
        ss << " value ";
        bind_joystick_axis(joystick, axis, [s = ss.str()](float value){
          std::cout << s << std::fixed << value <<  std::endl;
        });
      #else
        bind_joystick_axis(joystick, axis, [](float value __attribute__((__unused__))){});  // default to noop
        joystick_axis_binding_at(joystick, axis).enabled = false;
      #endif // DEBUG_INPUTSTORM
    }
  }
  // assign a safe default function to all joystick buttons
  for(keyactiontype action = keyactiontype::RELEASE; action != static_cast<keyactiontype>(max_joystick_button_action); action = static_cast<keyactiontype>(static_cast<int>(action) + 1)) {
    for(unsigned int button = 0; button != max_joystick_button; ++button) {
      for(unsigned int joystick = 0; joystick != max_joystick; ++joystick) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound joystick function called on button " << button;
          if(joystick != 0) {
            ss << " on joystick " << joystick;
          }
          ss << " action " << get_keyaction_name(action);
          if(action == keyactiontype::PRESS) {
            bind_joystick_button(joystick, button, action, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind_joystick_button(joystick, button, action, []{});
          }
        #else
          bind_joystick_button(joystick, button, action, []{});                 // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }

  // enable all the joysticks by default
  joystick_enabled.fill(true);
  update_joystick_names();

  // set callbacks
  //std::cout << "InputStorm: Setting callbacks..." << std::endl;
  glfwSetWindowUserPointer(  current_window, this);                             // have this class passed to future callbacks
  glfwSetKeyCallback(        current_window, key);
  glfwSetCursorPosCallback(  current_window, cursor);
  glfwSetCursorEnterCallback(current_window, cursor_enter);
  glfwSetMouseButtonCallback(current_window, mousebutton);
  glfwSetScrollCallback(     current_window, scroll);

  // report status
  std::cout << "InputStorm: Key bindings:             " << sizeof(key_bindings) / 1024 << "KB" << std::endl;
  std::cout << "InputStorm: Mouse button bindings:    " << sizeof(mousebutton_bindings) / 1024 << "KB" << std::endl;
  std::cout << "InputStorm: Joystick axis bindings:   " << sizeof(joystick_axis_bindings) / 1024 << "KB" << std::endl;
  std::cout << "InputStorm: Joystick button bindings: " << sizeof(joystick_button_bindings) / 1024 << "KB" << std::endl;
  for(unsigned int joystick = 0; joystick != max_joystick; ++joystick) {
    if(glfwJoystickPresent(joystick)) {
      std::cout << "InputStorm: Joystick " << joystick << ": " << joystick_names[joystick] << std::endl;
    }
  }
}

manager::~manager() {
  /// Default destructor
  std::cout << "InputStorm: Shutting down." << std::endl;
  glfwSetWindowUserPointer(  current_window, nullptr);                          // clear the user pointer
  glfwSetKeyCallback(        current_window, nullptr);                          // unset callbacks to avoid unpleasant accidents
  glfwSetCursorPosCallback(  current_window, nullptr);
  glfwSetCursorEnterCallback(current_window, nullptr);
  glfwSetMouseButtonCallback(current_window, nullptr);
  glfwSetScrollCallback(     current_window, nullptr);
}

std::string &manager::key_name_at(keytype key) {
  /// Accessor for the key name array
  #ifndef NDEBUG
    if(key < 0) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << key << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return key_names[key];
}
std::string &manager::mousebutton_name_at(mousebuttontype button) {
  /// Accessor for the mousebutton button name arrays
  #ifndef NDEBUG
    if(button < 0) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a button number " << button << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(button > GLFW_MOUSE_BUTTON_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a button number " << button << " which is past the last button " << GLFW_MOUSE_BUTTON_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return mousebutton_names[button];
}

std::function<void()> &manager::key_binding_at(keytype key, keyactiontype action, keymodtype mods) {
  /// Accessor for the key function sparse arrays
  #ifndef NDEBUG
    if(key < 0) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << key << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return key_bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(key)];
}
std::function<void()> &manager::mousebutton_binding_at(mousebuttontype button, keyactiontype action, keymodtype mods) {
  /// Accessor for the mousebutton function sparse arrays
  #ifndef NDEBUG
    if(button < 0) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a button number " << button << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(button > GLFW_MOUSE_BUTTON_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a button number " << button << " which is past the last key " << GLFW_MOUSE_BUTTON_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return mousebutton_bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)];
}
manager::joystick_axis_bindingtype &manager::joystick_axis_binding_at(unsigned int joystick, unsigned int axis) {
  /// Accessor for the joystick axis structure sparse arrays
  return joystick_axis_bindings[axis][joystick];
}
std::function<void()> &manager::joystick_button_binding_at(unsigned int joystick, unsigned int button, keyactiontype action) {
  /// Accessor for the joystick button function sparse arrays
  return joystick_button_bindings[static_cast<unsigned int>(action)][button][joystick];
}

std::string const &manager::get_key_name(keytype key) const {
  /// Return the key name from its GLFW key ID number
  // check for negatives first, as GLFW likes to play that game!
  if(key < 0) {
    key = 0;          // default this to unknown key
  }
  #ifndef NDEBUG
    if(key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return key_names[key];
}
std::string const &manager::get_keyaction_name(keyactiontype action) const {
  /// Return a human-readable name for this key action
  return key_action_names[static_cast<int>(action)];
}
std::string const &manager::get_keymod_name(keymodtype mods) const {
  /// Return a human-readable name for this key modifier
  return key_mod_names[static_cast<int>(mods)];
}
std::string const &manager::get_mousebutton_name(mousebuttontype button) const {
  /// Return the button name from its GLFW button ID number
  // check for negatives first, as GLFW likes to play that game!
  if(button < 0) {
    button = 0;          // default this to unknown button
  }
  #ifndef NDEBUG
    if(button > GLFW_MOUSE_BUTTON_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a mouse button number " << button << " which is past the last button " << GLFW_MOUSE_BUTTON_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return mousebutton_names[button];
}

void manager::bind_key(keytype key, keyactiontype action, keymodtype mods, std::function<void()> func) {
  /// Bind a function to a key
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_key_name(key) << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  key_binding_at(key, action, mods) = func;
}
void manager::bind_key_any_mod(keytype key, keyactiontype action, std::function<void()> func) {
  /// Helper function to bind a callback to a key with any modifier combination
  for(keymodtype mods = keymodtype::NONE; mods != static_cast<keymodtype>(max_key_mods); mods = static_cast<keymodtype>(static_cast<int>(mods) + 1)) {
    bind_key(key, action, mods, func);
  }
}
void manager::bind_key_any(std::function<void()> func) {
  /// Helper function to bind a callback to all keys, press event only
  for(keytype key = 0; key != max_key; ++key) {
    bind_key_any_mod(key, keyactiontype::PRESS, func);
  }
}

void manager::bind_cursor(std::function<void(Vector2d const&)> func) {
  /// Bind a function to cursor movement
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to cursor movement, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  cursor_binding = func;
}
void manager::bind_cursor_enter(std::function<void()> func) {
  /// Bind a function to cursor entering the window
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to cursor entering the window, this will throw an exception if called!" << std::endl;
    }
  #endif
  cursor_enter_binding = func;
}
void manager::bind_cursor_leave(std::function<void()> func) {
  /// Bind a function to cursor leaving the window
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to cursor leaving the window, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  cursor_leave_binding = func;
}
void manager::bind_mousebutton(mousebuttontype button, keyactiontype action, keymodtype mods, std::function<void()> func) {
  /// Bind a function to a mouse button
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_mousebutton_name(button) << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  mousebutton_binding_at(button, action, mods) = func;
}
void manager::bind_mousebutton_any_mod(mousebuttontype button, keyactiontype action, std::function<void()> func) {
  /// Helper function to bind a callback to a key with any modifier combination
  for(keymodtype mods = keymodtype::NONE; mods != static_cast<keymodtype>(max_key_mods); mods = static_cast<keymodtype>(static_cast<int>(mods) + 1)) {
    bind_mousebutton(button, action, mods, func);
  }
}
void manager::bind_mousebutton_any(std::function<void()> func) {
  /// Helper function to bind a callback to all mouse buttons, press event only
  for(mousebuttontype button = 0; button != max_mousebutton; ++button) {
    bind_mousebutton_any_mod(button, keyactiontype::PRESS, func);
  }
}
void manager::bind_scroll(std::function<void(Vector2d const&)> func) {
  /// Bind a function to scrolling
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to scroll, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  scroll_binding = func;
}
void manager::bind_joystick_axis(unsigned int joystick,
                                 unsigned int axis, std::function<void(float)> func,
                                 float deadzone_min,
                                 float deadzone_max,
                                 float saturation_min,
                                 float saturation_max) {
  /// Bind a function to a joystick axis, with the specified parameters
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to axis " << axis << " on joystick " << joystick << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  joystick_axis_bindingtype &binding = joystick_axis_binding_at(joystick, axis);
  binding.deadzone_min = deadzone_min;
  binding.deadzone_max = deadzone_max;
  binding.saturation_min = saturation_min;
  binding.saturation_max = saturation_max;
  binding.update_scales();
  binding.func = func;
  binding.enabled = true;
}
void manager::bind_joystick_button(unsigned int joystick, unsigned int button, keyactiontype action, std::function<void()> func) {
  /// Bind a function to a joystick button
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to button " << button << " on joystick " << joystick << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  joystick_button_binding_at(joystick, button, action) = func;
}
void manager::bind_joystick_button_any(unsigned int joystick, std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons, press event only
  for(unsigned int button = 0; button != max_joystick_button; ++button) {
    bind_joystick_button(joystick, button, keyactiontype::PRESS, func);
  }
}
void manager::bind_joystick_button_any_all(std::function<void()> func) {
  /// Helper function to bind a callback to all joystick buttons on all joysticks, press event only
  for(unsigned int joystick = 0; joystick != max_joystick; ++joystick) {
    bind_joystick_button_any(joystick, func);
  }
}

void manager::execute_key(keytype key, keyactiontype action, keymodtype mods) {
  /// Call the function associated with a given key
  #ifndef NDEBUG
    if(!key_binding_at(key, action, mods)) {
      std::cout << "InputStorm: ERROR: Called key " << get_key_name(key) << " which has a null function, fix this for release!" << std::endl;
      return;
    }
  #endif // NDEBUG
  key_binding_at(key, action, mods)();
}
void manager::execute_cursor(Vector2d const &change) {
  /// Call the function associated with cursor movements
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Cursor position " << change << std::endl;
  #endif // DEBUG_INPUTSTORM
  cursor_binding(change);
}
void manager::execute_cursor_enter() {
  /// Call the function associated with the cursor entering the window
  cursor_enter_binding();
}
void manager::execute_cursor_leave() {
  /// Call the function associated with the cursor leaving the window
  cursor_leave_binding();
}
void manager::execute_mousebutton(mousebuttontype button, keyactiontype action, keymodtype mods) {
  /// Call the function associated with a given key
  #ifndef NDEBUG
    if(!mousebutton_binding_at(button, action, mods)) {
      std::cout << "InputStorm: ERROR: Called mousebutton " << get_mousebutton_name(button) << " which has a null function, fix this for release!" << std::endl;
      return;
    }
  #endif // NDEBUG
  mousebutton_binding_at(button, action, mods)();
}
void manager::execute_scroll(Vector2d const &offset) {
  /// Call the function associated with scrolling
  scroll_binding(offset);
}
void manager::execute_joystick_axis(unsigned int joystick, unsigned int axis, float value) {
  /// Call the function associated with a joystick axis, having transformed the value appropriately
  joystick_axis_bindingtype const &binding = joystick_axis_binding_at(joystick, axis);
  if(!binding.enabled) {
    return;                                                                     // early exit in case this binding isn't in use
  }
  float value_transformed = value;
  if(value_transformed >= 0) {
    value_transformed -= binding.deadzone_max;
    value_transformed *= binding.scale_pos;
  } else {
    value_transformed -= binding.deadzone_min;
    value_transformed *= binding.scale_neg;
  }
  // TODO: optimise this - perhaps use integer flags and multiplication instead of the branch
  binding.func(value_transformed);
}
void manager::execute_joystick_button(unsigned int joystick, unsigned int button, keyactiontype action) {
  /// Call the function associated with a joystick button
  joystick_button_binding_at(joystick, button, action)();
}

void manager::update_joystick_names() {
  /// Update the list of joystick names
  for(unsigned int joystick = 0; joystick != max_joystick; ++joystick) {
    //if(glfwJoystickPresent(joystick)) {
      joystick_names[joystick] = glfwGetJoystickName(GLFW_JOYSTICK_1);
    //} else {
    //  joystick_names[joystick].clear();
    //}
  }
}

void manager::poll_joysticks() {
  /// Check which joysticks are attached and poll them
  for(unsigned int joystick = 0; joystick != max_joystick; ++joystick) {
    if(!glfwJoystickPresent(joystick)) {
      continue;
    }
    {
      // poll the axes
      int num_axes;
      float const* const axis_data = glfwGetJoystickAxes(joystick, &num_axes);
      unsigned int const axis_max = std::min(max_joystick_axis, static_cast<unsigned int>(num_axes));
      for(unsigned int axis = 0; axis != axis_max; ++axis) {
        execute_joystick_axis(joystick, axis, axis_data[axis]);
      }
    }
    {
      // poll the buttons
      int num_buttons;
      unsigned char const* const button_data = glfwGetJoystickButtons(joystick, &num_buttons);
      unsigned int const button_max = std::min(max_joystick_button, static_cast<unsigned int>(num_buttons));
      for(unsigned int button = 0; button != button_max; ++button) {
        execute_joystick_button(joystick, button, static_cast<keyactiontype>(button_data[button]));
      }
    }
  }
}

}
