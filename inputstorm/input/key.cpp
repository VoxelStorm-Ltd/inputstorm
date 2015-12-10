#include "key.h"
#include <sstream>
#include <iostream>

namespace inputstorm {
namespace input {

unsigned int constexpr key::max;
unsigned int constexpr key::max_mods;
unsigned int constexpr key::max_action;

void key::init() {
  /// create default key bindings and initialise key names
  //std::cout << "InputStorm: Initialising keymap..." << std::endl;
  for(keytype this_key = 0; this_key <= GLFW_KEY_LAST; ++this_key) {
    // this is a sparse array, and we don't know which we'll name - so default-name them all first, and override the specific ones after
    std::stringstream ss;
    ss << "UNKNOWN " << this_key;
    name_at(this_key) = ss.str();
  }
  name_at(0                     ) = "UNKNOWN";                                  // manually set to use 0 instead of negative numbers
  name_at(GLFW_KEY_SPACE        ) = "SPACE";
  name_at(GLFW_KEY_APOSTROPHE   ) = "APOSTROPHE";
  name_at(GLFW_KEY_COMMA        ) = "COMMA";
  name_at(GLFW_KEY_MINUS        ) = "MINUS";
  name_at(GLFW_KEY_PERIOD       ) = "PERIOD";
  name_at(GLFW_KEY_SLASH        ) = "SLASH";
  name_at(GLFW_KEY_0            ) = "0";
  name_at(GLFW_KEY_1            ) = "1";
  name_at(GLFW_KEY_2            ) = "2";
  name_at(GLFW_KEY_3            ) = "3";
  name_at(GLFW_KEY_4            ) = "4";
  name_at(GLFW_KEY_5            ) = "5";
  name_at(GLFW_KEY_6            ) = "6";
  name_at(GLFW_KEY_7            ) = "7";
  name_at(GLFW_KEY_8            ) = "8";
  name_at(GLFW_KEY_9            ) = "9";
  name_at(GLFW_KEY_SEMICOLON    ) = "SEMICOLON";
  name_at(GLFW_KEY_EQUAL        ) = "EQUAL";
  name_at(GLFW_KEY_A            ) = "A";
  name_at(GLFW_KEY_B            ) = "B";
  name_at(GLFW_KEY_C            ) = "C";
  name_at(GLFW_KEY_D            ) = "D";
  name_at(GLFW_KEY_E            ) = "E";
  name_at(GLFW_KEY_F            ) = "F";
  name_at(GLFW_KEY_G            ) = "G";
  name_at(GLFW_KEY_H            ) = "H";
  name_at(GLFW_KEY_I            ) = "I";
  name_at(GLFW_KEY_J            ) = "J";
  name_at(GLFW_KEY_K            ) = "K";
  name_at(GLFW_KEY_L            ) = "L";
  name_at(GLFW_KEY_M            ) = "M";
  name_at(GLFW_KEY_N            ) = "N";
  name_at(GLFW_KEY_O            ) = "O";
  name_at(GLFW_KEY_P            ) = "P";
  name_at(GLFW_KEY_Q            ) = "Q";
  name_at(GLFW_KEY_R            ) = "R";
  name_at(GLFW_KEY_S            ) = "S";
  name_at(GLFW_KEY_T            ) = "T";
  name_at(GLFW_KEY_U            ) = "U";
  name_at(GLFW_KEY_V            ) = "V";
  name_at(GLFW_KEY_W            ) = "W";
  name_at(GLFW_KEY_X            ) = "X";
  name_at(GLFW_KEY_Y            ) = "Y";
  name_at(GLFW_KEY_Z            ) = "Z";
  name_at(GLFW_KEY_LEFT_BRACKET ) = "LEFT_BRACKET";
  name_at(GLFW_KEY_BACKSLASH    ) = "BACKSLASH";
  name_at(GLFW_KEY_RIGHT_BRACKET) = "RIGHT_BRACKET";
  name_at(GLFW_KEY_GRAVE_ACCENT ) = "GRAVE_ACCENT";
  name_at(GLFW_KEY_WORLD_1      ) = "WORLD_1";
  name_at(GLFW_KEY_WORLD_2      ) = "WORLD_2";
  name_at(GLFW_KEY_ESCAPE       ) = "ESCAPE";
  name_at(GLFW_KEY_ENTER        ) = "ENTER";
  name_at(GLFW_KEY_TAB          ) = "TAB";
  name_at(GLFW_KEY_BACKSPACE    ) = "BACKSPACE";
  name_at(GLFW_KEY_INSERT       ) = "INSERT";
  name_at(GLFW_KEY_DELETE       ) = "DELETE";
  name_at(GLFW_KEY_RIGHT        ) = "RIGHT";
  name_at(GLFW_KEY_LEFT         ) = "LEFT";
  name_at(GLFW_KEY_DOWN         ) = "DOWN";
  name_at(GLFW_KEY_UP           ) = "UP";
  name_at(GLFW_KEY_PAGE_UP      ) = "PAGE_UP";
  name_at(GLFW_KEY_PAGE_DOWN    ) = "PAGE_DOWN";
  name_at(GLFW_KEY_HOME         ) = "HOME";
  name_at(GLFW_KEY_END          ) = "END";
  name_at(GLFW_KEY_CAPS_LOCK    ) = "CAPS_LOCK";
  name_at(GLFW_KEY_SCROLL_LOCK  ) = "SCROLL_LOCK";
  name_at(GLFW_KEY_NUM_LOCK     ) = "NUM_LOCK";
  name_at(GLFW_KEY_PRINT_SCREEN ) = "PRINT_SCREEN";
  name_at(GLFW_KEY_PAUSE        ) = "PAUSE";
  name_at(GLFW_KEY_F1           ) = "F1";
  name_at(GLFW_KEY_F2           ) = "F2";
  name_at(GLFW_KEY_F3           ) = "F3";
  name_at(GLFW_KEY_F4           ) = "F4";
  name_at(GLFW_KEY_F5           ) = "F5";
  name_at(GLFW_KEY_F6           ) = "F6";
  name_at(GLFW_KEY_F7           ) = "F7";
  name_at(GLFW_KEY_F8           ) = "F8";
  name_at(GLFW_KEY_F9           ) = "F9";
  name_at(GLFW_KEY_F10          ) = "F10";
  name_at(GLFW_KEY_F11          ) = "F11";
  name_at(GLFW_KEY_F12          ) = "F12";
  name_at(GLFW_KEY_F13          ) = "F13";
  name_at(GLFW_KEY_F14          ) = "F14";
  name_at(GLFW_KEY_F15          ) = "F15";
  name_at(GLFW_KEY_F16          ) = "F16";
  name_at(GLFW_KEY_F17          ) = "F17";
  name_at(GLFW_KEY_F18          ) = "F18";
  name_at(GLFW_KEY_F19          ) = "F19";
  name_at(GLFW_KEY_F20          ) = "F20";
  name_at(GLFW_KEY_F21          ) = "F21";
  name_at(GLFW_KEY_F22          ) = "F22";
  name_at(GLFW_KEY_F23          ) = "F23";
  name_at(GLFW_KEY_F24          ) = "F24";
  name_at(GLFW_KEY_F25          ) = "F25";
  name_at(GLFW_KEY_KP_0         ) = "KEYPAD 0";
  name_at(GLFW_KEY_KP_1         ) = "KEYPAD 1";
  name_at(GLFW_KEY_KP_2         ) = "KEYPAD 2";
  name_at(GLFW_KEY_KP_3         ) = "KEYPAD 3";
  name_at(GLFW_KEY_KP_4         ) = "KEYPAD 4";
  name_at(GLFW_KEY_KP_5         ) = "KEYPAD 5";
  name_at(GLFW_KEY_KP_6         ) = "KEYPAD 6";
  name_at(GLFW_KEY_KP_7         ) = "KEYPAD 7";
  name_at(GLFW_KEY_KP_8         ) = "KEYPAD 8";
  name_at(GLFW_KEY_KP_9         ) = "KEYPAD 9";
  name_at(GLFW_KEY_KP_DECIMAL   ) = "KEYPAD DECIMAL";
  name_at(GLFW_KEY_KP_DIVIDE    ) = "KEYPAD DIVIDE";
  name_at(GLFW_KEY_KP_MULTIPLY  ) = "KEYPAD MULTIPLY";
  name_at(GLFW_KEY_KP_SUBTRACT  ) = "KEYPAD SUBTRACT";
  name_at(GLFW_KEY_KP_ADD       ) = "KEYPAD ADD";
  name_at(GLFW_KEY_KP_ENTER     ) = "KEYPAD ENTER";
  name_at(GLFW_KEY_KP_EQUAL     ) = "KEYPAD EQUAL";
  name_at(GLFW_KEY_LEFT_SHIFT   ) = "LEFT SHIFT";
  name_at(GLFW_KEY_LEFT_CONTROL ) = "LEFT CONTROL";
  name_at(GLFW_KEY_LEFT_ALT     ) = "LEFT ALT";
  name_at(GLFW_KEY_LEFT_SUPER   ) = "LEFT SUPER";
  name_at(GLFW_KEY_RIGHT_SHIFT  ) = "RIGHT SHIFT";
  name_at(GLFW_KEY_RIGHT_CONTROL) = "RIGHT CONTROL";
  name_at(GLFW_KEY_RIGHT_ALT    ) = "RIGHT ALT";
  name_at(GLFW_KEY_RIGHT_SUPER  ) = "RIGHT SUPER";
  name_at(GLFW_KEY_MENU         ) = "MENU";

  mod_names[static_cast<int>(mod::NONE                   )] = "NONE";
  mod_names[static_cast<int>(mod::SHIFT                  )] = "SHIFT";
  mod_names[static_cast<int>(mod::CONTROL                )] = "CONTROL";
  mod_names[static_cast<int>(mod::SHIFT_CONTROL          )] = "SHIFT_CONTROL";
  mod_names[static_cast<int>(mod::ALT                    )] = "ALT";
  mod_names[static_cast<int>(mod::SHIFT_ALT              )] = "SHIFT_ALT";
  mod_names[static_cast<int>(mod::CONTROL_ALT            )] = "CONTROL_ALT";
  mod_names[static_cast<int>(mod::SHIFT_CONTROL_ALT      )] = "SHIFT_CONTROL_ALT";
  mod_names[static_cast<int>(mod::SUPER                  )] = "SUPER";
  mod_names[static_cast<int>(mod::SHIFT_SUPER            )] = "SHIFT_SUPER";
  mod_names[static_cast<int>(mod::CONTROL_SUPER          )] = "CONTROL_SUPER";
  mod_names[static_cast<int>(mod::SHIFT_CONTROL_SUPER    )] = "SHIFT_CONTROL_SUPER";
  mod_names[static_cast<int>(mod::ALT_SUPER              )] = "ALT_SUPER";
  mod_names[static_cast<int>(mod::SHIFT_ALT_SUPER        )] = "SHIFT_ALT_SUPER";
  mod_names[static_cast<int>(mod::CONTROL_ALT_SUPER      )] = "CONTROL_ALT_SUPER";
  mod_names[static_cast<int>(mod::SHIFT_CONTROL_ALT_SUPER)] = "SHIFT_CONTROL_ALT_SUPER";

  action_names[static_cast<int>(action::RELEASE)] = "RELEASE";
  action_names[static_cast<int>(action::PRESS  )] = "PRESS";
  action_names[static_cast<int>(action::REPEAT )] = "REPEAT";

  // assign a safe default function to all keys
  for(mod mods = mod::NONE;
      mods != static_cast<mod>(max_mods);
      mods = static_cast<mod>(static_cast<int>(mods) + 1)) {
    for(action thisaction = action::RELEASE;
        thisaction != static_cast<action>(max_action);
        thisaction = static_cast<action>(static_cast<int>(thisaction) + 1)) {
      for(keytype this_key = 0; this_key != max; ++this_key) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound this_key function called on key " << this_key << " (" << get_name(this_key) << ")";
          if(mods != mod::NONE) {
            ss << " mods " << get_mod_name(mods);
          }
          ss << " action " << get_action_name(thisaction);
          if(thisaction == action::PRESS) {
            bind(this_key, thisaction, mods, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind(this_key, thisaction, mods, []{});
          }
        #else
          bind(this_key, thisaction, mods, []{});                               // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }

  // report status
  std::cout << "InputStorm: Key bindings:             " << sizeof(bindings) / 1024 << "KB" << std::endl;
}

std::string &key::name_at(keytype this_key) {
  /// Accessor for the this_key name array
  #ifndef NDEBUG
    if(this_key < 0) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(this_key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return names[this_key];
}
std::function<void()> &key::binding_at(keytype this_key, action this_action, mod mods) {
  /// Accessor for the this_key function sparse arrays
  #ifndef NDEBUG
    if(this_key < 0) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is below zero - aborting!" << std::endl;
      abort();
    }
    if(this_key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return bindings[static_cast<unsigned int>(this_action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)];
}

std::string const &key::get_name(keytype this_key) const {
  /// Return the this_key name from its GLFW this_key ID number
  // check for negatives first, as GLFW likes to play that game!
  if(this_key < 0) {
    this_key = 0;          // default this to unknown this_key
  }
  #ifndef NDEBUG
    if(this_key > GLFW_KEY_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return names[this_key];
}
std::string const &key::get_action_name(action this_action) const {
  /// Return a human-readable name for this key action
  return action_names[static_cast<int>(this_action)];
}
std::string const &key::get_mod_name(mod mods) const {
  /// Return a human-readable name for this key modifier
  return mod_names[static_cast<int>(mods)];
}

void key::bind(keytype this_key, action this_action, mod mods, std::function<void()> func) {
  /// Bind a function to a key
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(this_key) << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  binding_at(this_key, this_action, mods) = func;
}
void key::bind_any_mod(keytype this_key, action this_action, std::function<void()> func) {
  /// Helper function to bind a callback to a key with any modifier combination
  for(mod mods = mod::NONE; mods != static_cast<mod>(max_mods); mods = static_cast<mod>(static_cast<int>(mods) + 1)) {
    bind(this_key, this_action, mods, func);
  }
}
void key::bind_any(std::function<void()> func) {
  /// Helper function to bind a callback to all keys, press event only
  for(keytype this_key = 0; this_key != max; ++this_key) {
    bind_any_mod(this_key, action::PRESS, func);
  }
}

void key::unbind(keytype this_key, action this_action, mod mods) {
  binding_at(this_key, this_action, mods) = []{};                               // noop
}
void key::unbind_any_mod(keytype this_key, action this_action) {
  /// Helper function to unbind callbacks from a key with any modifier
  for(mod mods = mod::NONE; mods != static_cast<mod>(max_mods); mods = static_cast<mod>(static_cast<int>(mods) + 1)) {
    unbind(this_key, this_action, mods);
  }
}
void key::unbind_any() {
  /// Helper function to unbind callbacks from all keys, all events
  for(keytype this_key = 0; this_key != max; ++this_key) {
    unbind_any_mod(this_key, action::PRESS);
    unbind_any_mod(this_key, action::RELEASE);
    unbind_any_mod(this_key, action::REPEAT);
  }
}

void key::execute(keytype this_key, action this_action, mod mods) {
  /// Call the function associated with a given key
  #ifndef NDEBUG
    if(!binding_at(this_key, this_action, mods)) {
      std::cout << "InputStorm: ERROR: Called key " << get_name(this_key) << " which has a null function, fix this for release!" << std::endl;
      return;
    }
  #endif // NDEBUG
  binding_at(this_key, this_action, mods)();
}

}
}
