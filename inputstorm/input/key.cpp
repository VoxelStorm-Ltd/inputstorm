#include "key.h"
#include <sstream>
#include <iostream>

namespace inputstorm {
namespace input {

void key::init() {
  /// create default key bindings and initialise key names
  //std::cout << "InputStorm: Initialising keymap..." << std::endl;
  for(keytype this_key = 0; this_key <= GLFW_KEY_LAST; ++this_key) {
#include "key.h"
    // this is a sparse array, and we don't know which we'll name - so default-name them all first, and override the specific ones after
    std::stringstream ss;
#include <sstream>
    ss << "UNKNOWN " << this_key;
#include <iostream>
    names[this_key] = ss.str();

  }
namespace inputstorm {
namespace input {
  names[0                     ] = "UNKNOWN";                                    // manually set to use 0 instead of negative numbers

  names[GLFW_KEY_SPACE        ] = "SPACE";
void key::init() {
  names[GLFW_KEY_APOSTROPHE   ] = "APOSTROPHE";
  /// create default key bindings and initialise key names
  names[GLFW_KEY_COMMA        ] = "COMMA";
  //std::cout << "InputStorm: Initialising keymap..." << std::endl;
  names[GLFW_KEY_MINUS        ] = "MINUS";
  for(keytype this_key = 0; this_key <= GLFW_KEY_LAST; ++this_key) {
  names[GLFW_KEY_PERIOD       ] = "PERIOD";
    // this is a sparse array, and we don't know which we'll name - so default-name them all first, and override the specific ones after
  names[GLFW_KEY_SLASH        ] = "SLASH";
    std::stringstream ss;
  names[GLFW_KEY_0            ] = "0";
    ss << "UNKNOWN " << this_key;
  names[GLFW_KEY_1            ] = "1";
    names[this_key] = ss.str();
  names[GLFW_KEY_2            ] = "2";
  }
  names[GLFW_KEY_3            ] = "3";
  names[0                     ] = "UNKNOWN";                                    // manually set to use 0 instead of negative numbers
  names[GLFW_KEY_4            ] = "4";
  names[GLFW_KEY_SPACE        ] = "SPACE";
  names[GLFW_KEY_5            ] = "5";
  names[GLFW_KEY_APOSTROPHE   ] = "APOSTROPHE";
  names[GLFW_KEY_6            ] = "6";
  names[GLFW_KEY_COMMA        ] = "COMMA";
  names[GLFW_KEY_7            ] = "7";
  names[GLFW_KEY_MINUS        ] = "MINUS";
  names[GLFW_KEY_8            ] = "8";
  names[GLFW_KEY_PERIOD       ] = "PERIOD";
  names[GLFW_KEY_9            ] = "9";
  names[GLFW_KEY_SLASH        ] = "SLASH";
  names[GLFW_KEY_SEMICOLON    ] = "SEMICOLON";
  names[GLFW_KEY_0            ] = "0";
  names[GLFW_KEY_EQUAL        ] = "EQUALS";
  names[GLFW_KEY_1            ] = "1";
  names[GLFW_KEY_A            ] = "A";
  names[GLFW_KEY_2            ] = "2";
  names[GLFW_KEY_B            ] = "B";
  names[GLFW_KEY_3            ] = "3";
  names[GLFW_KEY_C            ] = "C";
  names[GLFW_KEY_4            ] = "4";
  names[GLFW_KEY_D            ] = "D";
  names[GLFW_KEY_5            ] = "5";
  names[GLFW_KEY_E            ] = "E";
  names[GLFW_KEY_6            ] = "6";
  names[GLFW_KEY_F            ] = "F";
  names[GLFW_KEY_7            ] = "7";
  names[GLFW_KEY_G            ] = "G";
  names[GLFW_KEY_8            ] = "8";
  names[GLFW_KEY_H            ] = "H";
  names[GLFW_KEY_9            ] = "9";
  names[GLFW_KEY_I            ] = "I";
  names[GLFW_KEY_SEMICOLON    ] = "SEMICOLON";
  names[GLFW_KEY_J            ] = "J";
  names[GLFW_KEY_EQUAL        ] = "EQUALS";
  names[GLFW_KEY_K            ] = "K";
  names[GLFW_KEY_A            ] = "A";
  names[GLFW_KEY_L            ] = "L";
  names[GLFW_KEY_B            ] = "B";
  names[GLFW_KEY_M            ] = "M";
  names[GLFW_KEY_C            ] = "C";
  names[GLFW_KEY_N            ] = "N";
  names[GLFW_KEY_D            ] = "D";
  names[GLFW_KEY_O            ] = "O";
  names[GLFW_KEY_E            ] = "E";
  names[GLFW_KEY_P            ] = "P";
  names[GLFW_KEY_F            ] = "F";
  names[GLFW_KEY_Q            ] = "Q";
  names[GLFW_KEY_G            ] = "G";
  names[GLFW_KEY_R            ] = "R";
  names[GLFW_KEY_H            ] = "H";
  names[GLFW_KEY_S            ] = "S";
  names[GLFW_KEY_I            ] = "I";
  names[GLFW_KEY_T            ] = "T";
  names[GLFW_KEY_J            ] = "J";
  names[GLFW_KEY_U            ] = "U";
  names[GLFW_KEY_K            ] = "K";
  names[GLFW_KEY_V            ] = "V";
  names[GLFW_KEY_L            ] = "L";
  names[GLFW_KEY_W            ] = "W";
  names[GLFW_KEY_M            ] = "M";
  names[GLFW_KEY_X            ] = "X";
  names[GLFW_KEY_N            ] = "N";
  names[GLFW_KEY_Y            ] = "Y";
  names[GLFW_KEY_O            ] = "O";
  names[GLFW_KEY_Z            ] = "Z";
  names[GLFW_KEY_P            ] = "P";
  names[GLFW_KEY_LEFT_BRACKET ] = "LEFT BRACKET";
  names[GLFW_KEY_Q            ] = "Q";
  names[GLFW_KEY_BACKSLASH    ] = "BACKSLASH";
  names[GLFW_KEY_R            ] = "R";
  names[GLFW_KEY_RIGHT_BRACKET] = "RIGHT BRACKET";
  names[GLFW_KEY_S            ] = "S";
  names[GLFW_KEY_GRAVE_ACCENT ] = "GRAVE ACCENT";
  names[GLFW_KEY_T            ] = "T";
  names[GLFW_KEY_WORLD_1      ] = "WORLD 1";
  names[GLFW_KEY_U            ] = "U";
  names[GLFW_KEY_WORLD_2      ] = "WORLD 2";
  names[GLFW_KEY_V            ] = "V";
  names[GLFW_KEY_ESCAPE       ] = "ESCAPE";
  names[GLFW_KEY_W            ] = "W";
  names[GLFW_KEY_ENTER        ] = "ENTER";
  names[GLFW_KEY_X            ] = "X";
  names[GLFW_KEY_TAB          ] = "TAB";
  names[GLFW_KEY_Y            ] = "Y";
  names[GLFW_KEY_BACKSPACE    ] = "BACKSPACE";
  names[GLFW_KEY_Z            ] = "Z";
  names[GLFW_KEY_INSERT       ] = "INSERT";
  names[GLFW_KEY_LEFT_BRACKET ] = "LEFT BRACKET";
  names[GLFW_KEY_DELETE       ] = "DELETE";
  names[GLFW_KEY_BACKSLASH    ] = "BACKSLASH";
  names[GLFW_KEY_RIGHT        ] = "RIGHT";
  names[GLFW_KEY_RIGHT_BRACKET] = "RIGHT BRACKET";
  names[GLFW_KEY_LEFT         ] = "LEFT";
  names[GLFW_KEY_GRAVE_ACCENT ] = "GRAVE ACCENT";
  names[GLFW_KEY_DOWN         ] = "DOWN";
  names[GLFW_KEY_WORLD_1      ] = "WORLD 1";
  names[GLFW_KEY_UP           ] = "UP";
  names[GLFW_KEY_WORLD_2      ] = "WORLD 2";
  names[GLFW_KEY_PAGE_UP      ] = "PAGE UP";
  names[GLFW_KEY_ESCAPE       ] = "ESCAPE";
  names[GLFW_KEY_PAGE_DOWN    ] = "PAGE DOWN";
  names[GLFW_KEY_ENTER        ] = "ENTER";
  names[GLFW_KEY_HOME         ] = "HOME";
  names[GLFW_KEY_TAB          ] = "TAB";
  names[GLFW_KEY_END          ] = "END";
  names[GLFW_KEY_BACKSPACE    ] = "BACKSPACE";
  names[GLFW_KEY_CAPS_LOCK    ] = "CAPS LOCK";
  names[GLFW_KEY_INSERT       ] = "INSERT";
  names[GLFW_KEY_SCROLL_LOCK  ] = "SCROLL LOCK";
  names[GLFW_KEY_DELETE       ] = "DELETE";
  names[GLFW_KEY_NUM_LOCK     ] = "NUM LOCK";
  names[GLFW_KEY_RIGHT        ] = "RIGHT";
  names[GLFW_KEY_PRINT_SCREEN ] = "PRINT_SCREEN";
  names[GLFW_KEY_LEFT         ] = "LEFT";
  names[GLFW_KEY_PAUSE        ] = "PAUSE";
  names[GLFW_KEY_DOWN         ] = "DOWN";
  names[GLFW_KEY_F1           ] = "F1";
  names[GLFW_KEY_UP           ] = "UP";
  names[GLFW_KEY_F2           ] = "F2";
  names[GLFW_KEY_PAGE_UP      ] = "PAGE UP";
  names[GLFW_KEY_F3           ] = "F3";
  names[GLFW_KEY_PAGE_DOWN    ] = "PAGE DOWN";
  names[GLFW_KEY_F4           ] = "F4";
  names[GLFW_KEY_HOME         ] = "HOME";
  names[GLFW_KEY_F5           ] = "F5";
  names[GLFW_KEY_END          ] = "END";
  names[GLFW_KEY_F6           ] = "F6";
  names[GLFW_KEY_CAPS_LOCK    ] = "CAPS LOCK";
  names[GLFW_KEY_F7           ] = "F7";
  names[GLFW_KEY_SCROLL_LOCK  ] = "SCROLL LOCK";
  names[GLFW_KEY_F8           ] = "F8";
  names[GLFW_KEY_NUM_LOCK     ] = "NUM LOCK";
  names[GLFW_KEY_F9           ] = "F9";
  names[GLFW_KEY_PRINT_SCREEN ] = "PRINT_SCREEN";
  names[GLFW_KEY_F10          ] = "F10";
  names[GLFW_KEY_PAUSE        ] = "PAUSE";
  names[GLFW_KEY_F11          ] = "F11";
  names[GLFW_KEY_F1           ] = "F1";
  names[GLFW_KEY_F12          ] = "F12";
  names[GLFW_KEY_F2           ] = "F2";
  names[GLFW_KEY_F13          ] = "F13";
  names[GLFW_KEY_F3           ] = "F3";
  names[GLFW_KEY_F14          ] = "F14";
  names[GLFW_KEY_F4           ] = "F4";
  names[GLFW_KEY_F15          ] = "F15";
  names[GLFW_KEY_F5           ] = "F5";
  names[GLFW_KEY_F16          ] = "F16";
  names[GLFW_KEY_F6           ] = "F6";
  names[GLFW_KEY_F17          ] = "F17";
  names[GLFW_KEY_F7           ] = "F7";
  names[GLFW_KEY_F18          ] = "F18";
  names[GLFW_KEY_F8           ] = "F8";
  names[GLFW_KEY_F19          ] = "F19";
  names[GLFW_KEY_F9           ] = "F9";
  names[GLFW_KEY_F20          ] = "F20";
  names[GLFW_KEY_F10          ] = "F10";
  names[GLFW_KEY_F21          ] = "F21";
  names[GLFW_KEY_F11          ] = "F11";
  names[GLFW_KEY_F22          ] = "F22";
  names[GLFW_KEY_F12          ] = "F12";
  names[GLFW_KEY_F23          ] = "F23";
  names[GLFW_KEY_F13          ] = "F13";
  names[GLFW_KEY_F24          ] = "F24";
  names[GLFW_KEY_F14          ] = "F14";
  names[GLFW_KEY_F25          ] = "F25";
  names[GLFW_KEY_F15          ] = "F15";
  names[GLFW_KEY_KP_0         ] = "KEYPAD 0";
  names[GLFW_KEY_F16          ] = "F16";
  names[GLFW_KEY_KP_1         ] = "KEYPAD 1";
  names[GLFW_KEY_F17          ] = "F17";
  names[GLFW_KEY_KP_2         ] = "KEYPAD 2";
  names[GLFW_KEY_F18          ] = "F18";
  names[GLFW_KEY_KP_3         ] = "KEYPAD 3";
  names[GLFW_KEY_F19          ] = "F19";
  names[GLFW_KEY_KP_4         ] = "KEYPAD 4";
  names[GLFW_KEY_F20          ] = "F20";
  names[GLFW_KEY_KP_5         ] = "KEYPAD 5";
  names[GLFW_KEY_F21          ] = "F21";
  names[GLFW_KEY_KP_6         ] = "KEYPAD 6";
  names[GLFW_KEY_F22          ] = "F22";
  names[GLFW_KEY_KP_7         ] = "KEYPAD 7";
  names[GLFW_KEY_F23          ] = "F23";
  names[GLFW_KEY_KP_8         ] = "KEYPAD 8";
  names[GLFW_KEY_F24          ] = "F24";
  names[GLFW_KEY_KP_9         ] = "KEYPAD 9";
  names[GLFW_KEY_F25          ] = "F25";
  names[GLFW_KEY_KP_DECIMAL   ] = "KEYPAD DECIMAL";
  names[GLFW_KEY_KP_0         ] = "KEYPAD 0";
  names[GLFW_KEY_KP_DIVIDE    ] = "KEYPAD DIVIDE";
  names[GLFW_KEY_KP_1         ] = "KEYPAD 1";
  names[GLFW_KEY_KP_MULTIPLY  ] = "KEYPAD MULTIPLY";
  names[GLFW_KEY_KP_2         ] = "KEYPAD 2";
  names[GLFW_KEY_KP_SUBTRACT  ] = "KEYPAD SUBTRACT";
  names[GLFW_KEY_KP_3         ] = "KEYPAD 3";
  names[GLFW_KEY_KP_ADD       ] = "KEYPAD ADD";
  names[GLFW_KEY_KP_4         ] = "KEYPAD 4";
  names[GLFW_KEY_KP_ENTER     ] = "KEYPAD ENTER";
  names[GLFW_KEY_KP_5         ] = "KEYPAD 5";
  names[GLFW_KEY_KP_EQUAL     ] = "KEYPAD EQUAL";
  names[GLFW_KEY_KP_6         ] = "KEYPAD 6";
  names[GLFW_KEY_LEFT_SHIFT   ] = "LEFT SHIFT";
  names[GLFW_KEY_KP_7         ] = "KEYPAD 7";
  names[GLFW_KEY_LEFT_CONTROL ] = "LEFT CONTROL";
  names[GLFW_KEY_KP_8         ] = "KEYPAD 8";
  names[GLFW_KEY_LEFT_ALT     ] = "LEFT ALT";
  names[GLFW_KEY_KP_9         ] = "KEYPAD 9";
  names[GLFW_KEY_LEFT_SUPER   ] = "LEFT SUPER";
  names[GLFW_KEY_KP_DECIMAL   ] = "KEYPAD DECIMAL";
  names[GLFW_KEY_RIGHT_SHIFT  ] = "RIGHT SHIFT";
  names[GLFW_KEY_KP_DIVIDE    ] = "KEYPAD DIVIDE";
  names[GLFW_KEY_RIGHT_CONTROL] = "RIGHT CONTROL";
  names[GLFW_KEY_KP_MULTIPLY  ] = "KEYPAD MULTIPLY";
  names[GLFW_KEY_RIGHT_ALT    ] = "RIGHT ALT";
  names[GLFW_KEY_KP_SUBTRACT  ] = "KEYPAD SUBTRACT";
  names[GLFW_KEY_RIGHT_SUPER  ] = "RIGHT SUPER";
  names[GLFW_KEY_KP_ADD       ] = "KEYPAD ADD";
  names[GLFW_KEY_MENU         ] = "MENU";
  names[GLFW_KEY_KP_ENTER     ] = "KEYPAD ENTER";

  names[GLFW_KEY_KP_EQUAL     ] = "KEYPAD EQUAL";
  mod_names[static_cast<int>(modtype::NONE                   )] = "NONE";
  names[GLFW_KEY_LEFT_SHIFT   ] = "LEFT SHIFT";
  mod_names[static_cast<int>(modtype::SHIFT                  )] = "SHIFT";
  names[GLFW_KEY_LEFT_CONTROL ] = "LEFT CONTROL";
  mod_names[static_cast<int>(modtype::CONTROL                )] = "CONTROL";
  names[GLFW_KEY_LEFT_ALT     ] = "LEFT ALT";
  mod_names[static_cast<int>(modtype::SHIFT_CONTROL          )] = "SHIFT CONTROL";
  names[GLFW_KEY_LEFT_SUPER   ] = "LEFT SUPER";
  mod_names[static_cast<int>(modtype::ALT                    )] = "ALT";
  names[GLFW_KEY_RIGHT_SHIFT  ] = "RIGHT SHIFT";
  mod_names[static_cast<int>(modtype::SHIFT_ALT              )] = "SHIFT ALT";
  names[GLFW_KEY_RIGHT_CONTROL] = "RIGHT CONTROL";
  mod_names[static_cast<int>(modtype::CONTROL_ALT            )] = "CONTROL ALT";
  names[GLFW_KEY_RIGHT_ALT    ] = "RIGHT ALT";
  mod_names[static_cast<int>(modtype::SHIFT_CONTROL_ALT      )] = "SHIFT CONTROL ALT";
  names[GLFW_KEY_RIGHT_SUPER  ] = "RIGHT SUPER";
  mod_names[static_cast<int>(modtype::SUPER                  )] = "SUPER";
  names[GLFW_KEY_MENU         ] = "MENU";

  mod_names[static_cast<int>(modtype::SHIFT_SUPER            )] = "SHIFT SUPER";
  mod_names[static_cast<int>(modtype::NONE                   )] = "NONE";
  mod_names[static_cast<int>(modtype::CONTROL_SUPER          )] = "CONTROL SUPER";
  mod_names[static_cast<int>(modtype::SHIFT                  )] = "SHIFT";
  mod_names[static_cast<int>(modtype::SHIFT_CONTROL_SUPER    )] = "SHIFT CONTROL SUPER";
  mod_names[static_cast<int>(modtype::CONTROL                )] = "CONTROL";
  mod_names[static_cast<int>(modtype::ALT_SUPER              )] = "ALT SUPER";
  mod_names[static_cast<int>(modtype::SHIFT_CONTROL          )] = "SHIFT CONTROL";
  mod_names[static_cast<int>(modtype::SHIFT_ALT_SUPER        )] = "SHIFT ALT SUPER";
  mod_names[static_cast<int>(modtype::ALT                    )] = "ALT";
  mod_names[static_cast<int>(modtype::CONTROL_ALT_SUPER      )] = "CONTROL ALT SUPER";
  mod_names[static_cast<int>(modtype::SHIFT_ALT              )] = "SHIFT ALT";
  mod_names[static_cast<int>(modtype::SHIFT_CONTROL_ALT_SUPER)] = "SHIFT CONTROL ALT SUPER";
  mod_names[static_cast<int>(modtype::CONTROL_ALT            )] = "CONTROL ALT";

  mod_names[static_cast<int>(modtype::SHIFT_CONTROL_ALT      )] = "SHIFT CONTROL ALT";
  action_names[static_cast<int>(actiontype::RELEASE)] = "RELEASE";
  mod_names[static_cast<int>(modtype::SUPER                  )] = "SUPER";
  action_names[static_cast<int>(actiontype::PRESS  )] = "PRESS";
  mod_names[static_cast<int>(modtype::SHIFT_SUPER            )] = "SHIFT SUPER";
  action_names[static_cast<int>(actiontype::REPEAT )] = "REPEAT";
  mod_names[static_cast<int>(modtype::CONTROL_SUPER          )] = "CONTROL SUPER";

  mod_names[static_cast<int>(modtype::SHIFT_CONTROL_SUPER    )] = "SHIFT CONTROL SUPER";
  // assign a safe default function to all keys
  mod_names[static_cast<int>(modtype::ALT_SUPER              )] = "ALT SUPER";
  for(auto const &mods : modtype()) {
  mod_names[static_cast<int>(modtype::SHIFT_ALT_SUPER        )] = "SHIFT ALT SUPER";
    for(auto const &action : actiontype()) {
  mod_names[static_cast<int>(modtype::CONTROL_ALT_SUPER      )] = "CONTROL ALT SUPER";
      for(keytype this_key = 0; this_key != max; ++this_key) {
  mod_names[static_cast<int>(modtype::SHIFT_CONTROL_ALT_SUPER)] = "SHIFT CONTROL ALT SUPER";
        #ifdef DEBUG_INPUTSTORM

          std::stringstream ss;
  action_names[static_cast<int>(actiontype::RELEASE)] = "RELEASE";
          ss << "InputStorm: DEBUG: unbound this_key function called on key " << this_key << " (" << get_name(this_key) << ")";
  action_names[static_cast<int>(actiontype::PRESS  )] = "PRESS";
          if(mods != modtype::NONE) {
  action_names[static_cast<int>(actiontype::REPEAT )] = "REPEAT";
            ss << " mods " << get_mod_name(mods);

          }
  // assign a safe default function to all keys
          ss << " action " << get_actiontype_name(action);
  for(auto const &mods : modtype()) {
          if(action == actiontype::PRESS) {
    for(auto const &action : actiontype()) {
            bind(this_key, action, mods, [s = ss.str()]{
      for(keytype this_key = 0; this_key != max; ++this_key) {
              std::cout << s << std::endl;
        #ifdef DEBUG_INPUTSTORM
            });
          std::stringstream ss;
          } else {
          ss << "InputStorm: DEBUG: unbound this_key function called on key " << this_key << " (" << get_name(this_key) << ")";
            bind(this_key, action, mods, []{});
          if(mods != modtype::NONE) {
          }
            ss << " mods " << get_mod_name(mods);
        #else
          }
          bind(this_key, action, mods, []{});                                   // default to noop
          ss << " action " << get_actiontype_name(action);
        #endif // DEBUG_INPUTSTORM
          if(action == actiontype::PRESS) {
      }
            bind(this_key, action, mods, [s = ss.str()]{
    }
              std::cout << s << std::endl;
  }
            });

          } else {
  // report status
            bind(this_key, action, mods, []{});
  std::cout << "InputStorm: Key bindings:             " << sizeof(bindings) / 1024 << "KB" << std::endl;
          }
}
        #else

          bind(this_key, action, mods, []{});                                   // default to noop
std::string const &key::name_at(keytype this_key) const {
        #endif // DEBUG_INPUTSTORM
  /// Accessor for the this_key name array
      }
  #ifndef NDEBUG
    }
    if(this_key < 0) {
  }
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is below zero - aborting!" << std::endl;

      abort();
  // report status
    }
  std::cout << "InputStorm: Key bindings:             " << sizeof(bindings) / 1024 << "KB" << std::endl;
    if(this_key > GLFW_KEY_LAST) {
}
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;

      abort();
std::string const &key::name_at(keytype this_key) const {
    }
  /// Accessor for the this_key name array
  #endif // NDEBUG
  #ifndef NDEBUG
  return names[this_key];
    if(this_key < 0) {
}
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is below zero - aborting!" << std::endl;
std::function<void()> const &key::binding_at(keytype this_key, actiontype action, modtype mods) const {
      abort();
  /// Accessor for the this_key function sparse arrays
    }
  #ifndef NDEBUG
    if(this_key > GLFW_KEY_LAST) {
    if(this_key < 0) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is below zero - aborting!" << std::endl;
      abort();
      abort();
    }
    }
  #endif // NDEBUG
    if(this_key > GLFW_KEY_LAST) {
  return names[this_key];
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
}
      abort();
std::function<void()> const &key::binding_at(keytype this_key, actiontype action, modtype mods) const {
    }
  /// Accessor for the this_key function sparse arrays
  #endif // NDEBUG
  #ifndef NDEBUG
  return bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)];
    if(this_key < 0) {
}
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is below zero - aborting!" << std::endl;

      abort();
std::string const &key::get_name(keytype this_key) const {
    }
  /// Return the this_key name from its GLFW this_key ID number
    if(this_key > GLFW_KEY_LAST) {
  // check for negatives first, as GLFW likes to play that game!
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
  if(this_key < 0) {
      abort();
    this_key = 0;                                                               // default this to unknown this_key
    }
  }
  #endif // NDEBUG
  #ifndef NDEBUG
  return bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)];
    if(this_key > GLFW_KEY_LAST) {
}
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;

      abort();
std::string const &key::get_name(keytype this_key) const {
    }
  /// Return the this_key name from its GLFW this_key ID number
  #endif // NDEBUG
  // check for negatives first, as GLFW likes to play that game!
  return names[this_key];
  if(this_key < 0) {
}
    this_key = 0;                                                               // default this to unknown this_key
std::string const &key::get_actiontype_name(actiontype action) const {
  }
  /// Return a human-readable name for this key actiontype
  #ifndef NDEBUG
  return action_names[static_cast<int>(action)];
    if(this_key > GLFW_KEY_LAST) {
}
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
std::string const &key::get_mod_name(modtype mods) const {
      abort();
  /// Return a human-readable name for this key modifier
    }
  return mod_names[static_cast<int>(mods)];
  #endif // NDEBUG
}
  return names[this_key];

}
void key::bind(keytype this_key, actiontype action, modtype mods, std::function<void()> func) {
std::string const &key::get_actiontype_name(actiontype action) const {
  /// Bind a function to a key
  /// Return a human-readable name for this key actiontype
  #ifndef NDEBUG
  return action_names[static_cast<int>(action)];
    if(!func) {
}
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(this_key) << ", this will throw an exception if called!" << std::endl;
std::string const &key::get_mod_name(modtype mods) const {
    }
  /// Return a human-readable name for this key modifier
  #endif // NDEBUG
  return mod_names[static_cast<int>(mods)];
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = func;
}
}

void key::bind_any_mod(keytype this_key, actiontype action, std::function<void()> func) {
void key::bind(keytype this_key, actiontype action, modtype mods, std::function<void()> func) {
  /// Helper function to bind a callback to a key with any modifier combination
  /// Bind a function to a key
  for(auto const &mods : modtype()) {
  #ifndef NDEBUG
    bind(this_key, action, mods, func);
    if(!func) {
  }
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(this_key) << ", this will throw an exception if called!" << std::endl;
}
    }
void key::bind_any(std::function<void()> func) {
  #endif // NDEBUG
  /// Helper function to bind a callback to all keys, press event only
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = func;
  for(keytype this_key = 0; this_key != max; ++this_key) {
}
    bind_any_mod(this_key, actiontype::PRESS, func);
void key::bind_any_mod(keytype this_key, actiontype action, std::function<void()> func) {
  }
  /// Helper function to bind a callback to a key with any modifier combination
}
  for(auto const &mods : modtype()) {
void key::bind(key::binding const &this_binding,
    bind(this_key, action, mods, func);
               std::function<void()> func_press,
  }
               std::function<void()> func_release,
}
               std::function<void()> func_repeat) {
void key::bind_any(std::function<void()> func) {
  /// Helper function to load binding settings from a binding object
  /// Helper function to bind a callback to all keys, press event only
  switch(this_binding.type) {
  for(keytype this_key = 0; this_key != max; ++this_key) {
  case binding::bindtype::SPECIFIC:
    bind_any_mod(this_key, actiontype::PRESS, func);
    if(func_press) {
  }
      bind(this_binding.key, actiontype::PRESS, this_binding.mods, func_press);
}
    }
void key::bind(key::binding const &this_binding,
    if(func_release) {
               std::function<void()> func_press,
      bind(this_binding.key, actiontype::RELEASE, this_binding.mods, func_release);
               std::function<void()> func_release,
    }
               std::function<void()> func_repeat) {
    if(func_repeat) {
  /// Helper function to load binding settings from a binding object
      bind(this_binding.key, actiontype::REPEAT, this_binding.mods, func_repeat);
  switch(this_binding.type) {
    }
  case binding::bindtype::SPECIFIC:
    break;
    if(func_press) {
  case binding::bindtype::ANY_MOD:
      bind(this_binding.key, actiontype::PRESS, this_binding.mods, func_press);
    if(func_press) {
    }
      bind_any_mod(this_binding.key, actiontype::PRESS, func_press);
    if(func_release) {
    }
      bind(this_binding.key, actiontype::RELEASE, this_binding.mods, func_release);
    if(func_release) {
    }
      bind_any_mod(this_binding.key, actiontype::RELEASE, func_release);
    if(func_repeat) {
    }
      bind(this_binding.key, actiontype::REPEAT, this_binding.mods, func_repeat);
    if(func_repeat) {
    }
      bind_any_mod(this_binding.key, actiontype::REPEAT, func_repeat);
    break;
    }
  case binding::bindtype::ANY_MOD:
    break;
    if(func_press) {
  case binding::bindtype::ANY:
      bind_any_mod(this_binding.key, actiontype::PRESS, func_press);
    if(func_press) {
    }
      bind_any(func_press);
    if(func_release) {
    } else {
      bind_any_mod(this_binding.key, actiontype::RELEASE, func_release);
      std::cout << "InputStorm: Key: WARNING - requested to bind to any key with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
    }
    }
    if(func_repeat) {
    break;
      bind_any_mod(this_binding.key, actiontype::REPEAT, func_repeat);
  case binding::bindtype::END:
    }
    #ifndef NDEBUG
    break;
  case binding::bindtype::ANY:
      std::cout << "InputStorm: ERROR: bind target has an invalid bindtype END!" << std::endl;
    if(func_press) {
    #endif // NDEBUG
      bind_any(func_press);
    break;
    } else {
  }
}
      std::cout << "InputStorm: Key: WARNING - requested to bind to any key with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;

    }
void key::unbind(keytype this_key, actiontype action, modtype mods) {
    break;
  case binding::bindtype::END:
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = []{}; // noop
    #ifndef NDEBUG
}
      std::cout << "InputStorm: ERROR: bind target has an invalid bindtype END!" << std::endl;
void key::unbind_any_mod(keytype this_key, actiontype action) {
    #endif // NDEBUG
  /// Helper function to unbind callbacks from a key with any modifier
    break;
  for(auto const &mods : modtype()) {
  }
    unbind(this_key, action, mods);
}
  }

}
void key::unbind(keytype this_key, actiontype action, modtype mods) {
void key::unbind_any() {
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = []{}; // noop
  /// Helper function to unbind callbacks from all keys, all events
}
  for(keytype this_key = 0; this_key != max; ++this_key) {
void key::unbind_any_mod(keytype this_key, actiontype action) {
    unbind_any_mod(this_key, actiontype::PRESS);
  /// Helper function to unbind callbacks from a key with any modifier
    unbind_any_mod(this_key, actiontype::RELEASE);
  for(auto const &mods : modtype()) {
    unbind_any_mod(this_key, actiontype::REPEAT);
    unbind(this_key, action, mods);
  }
  }
}
}
void key::unbind(binding const &this_binding) {
void key::unbind_any() {
  switch(this_binding.type) {
  /// Helper function to unbind callbacks from all keys, all events
  case binding::bindtype::SPECIFIC:
  for(keytype this_key = 0; this_key != max; ++this_key) {
    unbind(this_binding.key, actiontype::PRESS,   this_binding.mods);
    unbind_any_mod(this_key, actiontype::PRESS);
    unbind(this_binding.key, actiontype::RELEASE, this_binding.mods);
    unbind_any_mod(this_key, actiontype::RELEASE);
    unbind(this_binding.key, actiontype::REPEAT,  this_binding.mods);
    unbind_any_mod(this_key, actiontype::REPEAT);
    break;
  }
  case binding::bindtype::ANY_MOD:
}
    unbind_any_mod(this_binding.key, actiontype::PRESS);
void key::unbind(binding const &this_binding) {
    unbind_any_mod(this_binding.key, actiontype::RELEASE);
  switch(this_binding.type) {
    unbind_any_mod(this_binding.key, actiontype::REPEAT);
  case binding::bindtype::SPECIFIC:
    break;
    unbind(this_binding.key, actiontype::PRESS,   this_binding.mods);
  case binding::bindtype::ANY:
    unbind(this_binding.key, actiontype::RELEASE, this_binding.mods);
    unbind_any();
    unbind(this_binding.key, actiontype::REPEAT,  this_binding.mods);
    break;
    break;
  case binding::bindtype::END:
  case binding::bindtype::ANY_MOD:
    #ifndef NDEBUG
    unbind_any_mod(this_binding.key, actiontype::PRESS);
      std::cout << "InputStorm: ERROR: unbind target has an invalid bindtype END!" << std::endl;
    unbind_any_mod(this_binding.key, actiontype::RELEASE);
    #endif // NDEBUG
    unbind_any_mod(this_binding.key, actiontype::REPEAT);
    break;
    break;
  }
  case binding::bindtype::ANY:
}
    unbind_any();

    break;
void key::execute(keytype this_key, actiontype action, modtype mods) const {
  case binding::bindtype::END:
  /// Call the function associated with a given key
    #ifndef NDEBUG
  #ifndef NDEBUG
      std::cout << "InputStorm: ERROR: unbind target has an invalid bindtype END!" << std::endl;
    if(!binding_at(this_key, action, mods)) {
    #endif // NDEBUG
      std::cout << "InputStorm: ERROR: Called key " << get_name(this_key) << " which has a null function, fix this for release!" << std::endl;
    break;
      return;
  }
    }
}
  #endif // NDEBUG

  binding_at(this_key, action, mods)();
void key::execute(keytype this_key, actiontype action, modtype mods) const {
}
  /// Call the function associated with a given key

  #ifndef NDEBUG
void key::capture(std::function<void(keytype, modtype)> callback) {
    if(!binding_at(this_key, action, mods)) {
  /// Capture a keystroke and return it to the given callback
      std::cout << "InputStorm: ERROR: Called key " << get_name(this_key) << " which has a null function, fix this for release!" << std::endl;
  for(keytype this_key = 0; this_key != max; ++this_key) {                      // create a new callback for each key
      return;
    for(auto const &mods : modtype()) {
    }
      bind(this_key, actiontype::PRESS,   mods, []{});                          // unbind press actions
  #endif // NDEBUG
      bind(this_key, actiontype::REPEAT,  mods, []{});                          // unbind repeat actions
  binding_at(this_key, action, mods)();
}
      bind(this_key, actiontype::RELEASE, mods, [callback, this_key, mods]{

        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
void key::capture(std::function<void(keytype, modtype)> callback) {
        callback(this_key, mods);
  /// Capture a keystroke and return it to the given callback
      });
  for(keytype this_key = 0; this_key != max; ++this_key) {                      // create a new callback for each key
    }
    for(auto const &mods : modtype()) {
  }
}
      bind(this_key, actiontype::PRESS,   mods, []{});                          // unbind press actions

      bind(this_key, actiontype::REPEAT,  mods, []{});                          // unbind repeat actions
}
      bind(this_key, actiontype::RELEASE, mods, [callback, this_key, mods]{
}
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
        callback(this_key, mods);
      });
    }
  }
}

}
}
