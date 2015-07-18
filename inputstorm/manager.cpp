#include "manager.h"
#include <iostream>
#include <sstream>
#include "callbacks/callbacks.h"
#include "timestorm/timer.h"

namespace inputstorm {

manager::manager(GLFWwindow &thiswindow)
  : current_window(&thiswindow) {
  /// Default constructor
  timestorm::timer<unsigned int> timer("InputStorm: Initialised in ");
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

  // assign a safe default function to all keys
  for(keymodtype mods = keymodtype::NONE; mods != keymodtype::END; mods = static_cast<keymodtype>(static_cast<int>(mods) + 1)) {
    for(keyactiontype action = keyactiontype::RELEASE; action != keyactiontype::END; action = static_cast<keyactiontype>(static_cast<int>(action) + 1)) {
      for(keytype key = 0; key <= GLFW_KEY_LAST; ++key) {
        #ifndef NDEBUG
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound key function called on key " << key << " (" << get_key_name(key) << ")";
          if(mods != keymodtype::NONE) {
            ss << " mods " << get_keymod_name(mods);
          }
          ss << " action " << get_keyaction_name(action);
          if(action == keyactiontype::PRESS) {
            bind_key(key, action, mods, [s = ss.str()]{
              std::cout << s << std::endl;;
            });
          } else {
            bind_key(key, action, mods, []{});
          }
        #else
          bind_key(key, action, mods, []{});                                    // default to noop
        #endif // NDEBUG
      }
    }
  }

  // set callbacks
  //std::cout << "InputStorm: Setting callbacks..." << std::endl;
  glfwSetWindowUserPointer(  current_window, this);                             // have this class passed to future callbacks
  glfwSetKeyCallback(        current_window, key);
  glfwSetCursorPosCallback(  current_window, cursor);
  glfwSetCursorEnterCallback(current_window, cursor_enter);
}

manager::~manager() {
  /// Default destructor
  std::cout << "InputStorm: Shutting down." << std::endl;
  glfwSetWindowUserPointer(  current_window, nullptr);                          // clear the user pointer
  glfwSetKeyCallback(        current_window, nullptr);                          // unset callbacks to avoid unpleasant accidents
  glfwSetCursorPosCallback(  current_window, nullptr);
  glfwSetCursorEnterCallback(current_window, nullptr);
}

std::string &manager::key_name_at(keytype key) {
  /// Accessor for the key function sparse arrays
  #ifndef NDEBUG
    if(key < 0) {
      std::cout << "InputStorm: ERROR! get_key_name_at called with a key number " << key << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! get_key_name_at called with a key number " << key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return key_names[key];
}
std::function<void()> &manager::key_binding_at(keytype key, keyactiontype action, keymodtype mods) {
  /// Accessor for the key function sparse arrays
  #ifndef NDEBUG
    if(key < 0) {
      std::cout << "InputStorm: ERROR! get_key_binding_at called with a key number " << key << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! get_key_binding_at called with a key number " << key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return key_bindings[static_cast<int>(action)][static_cast<int>(mods)][static_cast<int>(key)];
}

std::string const &manager::get_key_name(keytype key) const {
  /// Return the key name from its GLFW key ID number
  // check for negatives first, as GLFW likes to play that game!
  if(key < 0) {
    key = 0;          // default this to unknown key
  }
  #ifndef NDEBUG
    if(key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! get_key_name called with a key number " << key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
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

void manager::bind_key(keytype key, keyactiontype action, keymodtype mods, std::function<void()> func) {
  /// Bind a function to a key
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_key_name(key) << ", this will throw an exception if called!" << std::endl;
    }
  #endif
  key_binding_at(key, action, mods) = func;
}

void manager::execute_key(keytype key, keyactiontype action, keymodtype mods) {
  /// Call the function associated with a given key
  #ifndef NDEBUG
    if(!key_binding_at(key, action, mods)) {
      std::cout << "InputStorm: ERROR: Called key " << get_key_name(key) << " which has a null function, fix this for release!" << std::endl;
      return;
    }
  #endif
  key_binding_at(key, action, mods)();
}

void manager::bind_cursor(std::function<void(Vector2d const&)> func) {
  /// Bind a function to cursor movement
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to cursor movement, this will throw an exception if called!" << std::endl;
    }
  #endif
  cursor_binding = func;
}

void manager::execute_cursor(Vector2d const &change) {
  /// Call the function associated with cursor movements
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

}
