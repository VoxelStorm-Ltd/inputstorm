  case GLFW_KEY_PAUSE:
    return "PAUSE";
  case GLFW_KEY_F1:
    return "F1";
  case GLFW_KEY_F2:
    return "F2";
  case GLFW_KEY_F3:
    return "F3";
  case GLFW_KEY_F4:
    return "F4";
  case GLFW_KEY_F5:
    return "F5";
  case GLFW_KEY_F6:
    return "F6";
  case GLFW_KEY_F7:
    return "F7";
  case GLFW_KEY_F8:
    return "F8";
  case GLFW_KEY_F9:
    return "F9";
  case GLFW_KEY_F10:
    return "F10";
  case GLFW_KEY_F11:
    return "F11";
  case GLFW_KEY_F12:
    return "F12";
  case GLFW_KEY_F13:
#include "key.h"
    return "F13";
  case GLFW_KEY_F14:
#include <iostream>
    return "F14";
#ifdef DEBUG_INPUTSTORM
  case GLFW_KEY_F15:
  #include <sstream>
    return "F15";
#endif // DEBUG_INPUTSTORM
  case GLFW_KEY_F16:

    return "F16";
namespace inputstorm {
  case GLFW_KEY_F17:
namespace input {
    return "F17";

  case GLFW_KEY_F18:
void key::init() {
    return "F18";
  /// create default key bindings and initialise key names
  case GLFW_KEY_F19:
  //std::cout << "InputStorm: Initialising keymap..." << std::endl;
    return "F19";
  reset();
  case GLFW_KEY_F20:
  // report status
    return "F20";
  std::cout << "InputStorm: Key bindings:             " << sizeof(bindings) / 1024 << "KB" << std::endl;
  case GLFW_KEY_F21:
}
    return "F21";

  case GLFW_KEY_F22:
std::function<void()> const &key::binding_at(keytype this_key, actiontype action, modtype mods) const {
    return "F22";
  /// Accessor for the this_key function sparse arrays
  #ifndef NDEBUG
  case GLFW_KEY_F23:
    if(this_key < 0) {
    return "F23";
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is below zero - aborting!" << std::endl;
  case GLFW_KEY_F24:
      abort();
    return "F24";
    }
  case GLFW_KEY_F25:
    if(this_key > GLFW_KEY_LAST) {
    return "F25";
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a key number " << this_key << " which is past the last key " << GLFW_KEY_LAST << ", aborting!" << std::endl;
  case GLFW_KEY_KP_0:
      abort();
    return "KEYPAD 0";
    }
  case GLFW_KEY_KP_1:
  #endif // NDEBUG
    return "KEYPAD 1";
  return bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)];
  case GLFW_KEY_KP_2:
}
    return "KEYPAD 2";

  case GLFW_KEY_KP_3:
std::string key::get_name(keytype this_key) {
    return "KEYPAD 3";
  /// Return the this_key name from its GLFW this_key ID number
  case GLFW_KEY_KP_4:
  switch(this_key) {
    return "KEYPAD 4";
  case GLFW_KEY_SPACE:
  case GLFW_KEY_KP_5:
    return "SPACE";
    return "KEYPAD 5";
  case GLFW_KEY_APOSTROPHE:
  case GLFW_KEY_KP_6:
    return "APOSTROPHE";
    return "KEYPAD 6";
  case GLFW_KEY_COMMA:
  case GLFW_KEY_KP_7:
    return "COMMA";
    return "KEYPAD 7";
  case GLFW_KEY_MINUS:
  case GLFW_KEY_KP_8:
    return "MINUS";
    return "KEYPAD 8";
  case GLFW_KEY_PERIOD:
  case GLFW_KEY_KP_9:
    return "PERIOD";
    return "KEYPAD 9";
  case GLFW_KEY_SLASH:
    return "SLASH";
  case GLFW_KEY_KP_DECIMAL:
  case GLFW_KEY_0:
    return "KEYPAD DECIMAL";
    return "0";
  case GLFW_KEY_KP_DIVIDE:
  case GLFW_KEY_1:
    return "KEYPAD DIVIDE";
    return "1";
  case GLFW_KEY_KP_MULTIPLY:
  case GLFW_KEY_2:
    return "KEYPAD MULTIPLY";
    return "2";
  case GLFW_KEY_KP_SUBTRACT:
  case GLFW_KEY_3:
    return "KEYPAD SUBTRACT";
    return "3";
  case GLFW_KEY_KP_ADD:
  case GLFW_KEY_4:
    return "KEYPAD ADD";
    return "4";
  case GLFW_KEY_KP_ENTER:
  case GLFW_KEY_5:
    return "KEYPAD ENTER";
    return "5";
  case GLFW_KEY_KP_EQUAL:
  case GLFW_KEY_6:
    return "KEYPAD EQUAL";
    return "6";
  case GLFW_KEY_7:
  case GLFW_KEY_LEFT_SHIFT:
    return "7";
    return "LEFT SHIFT";
  case GLFW_KEY_8:
  case GLFW_KEY_LEFT_CONTROL:
    return "8";
    return "LEFT CONTROL";
  case GLFW_KEY_9:
  case GLFW_KEY_LEFT_ALT:
    return "9";
    return "LEFT ALT";
  case GLFW_KEY_SEMICOLON:
  case GLFW_KEY_LEFT_SUPER:
    return "SEMICOLON";
    return "LEFT SUPER";
  case GLFW_KEY_EQUAL:
  case GLFW_KEY_RIGHT_SHIFT:
    return "EQUALS";
  case GLFW_KEY_A:
    return "RIGHT SHIFT";
    return "A";
  case GLFW_KEY_RIGHT_CONTROL:
  case GLFW_KEY_B:
    return "RIGHT CONTROL";
    return "B";
  case GLFW_KEY_RIGHT_ALT:
  case GLFW_KEY_C:
    return "RIGHT ALT";
    return "C";
  case GLFW_KEY_RIGHT_SUPER:
  case GLFW_KEY_D:
    return "RIGHT SUPER";
    return "D";
  case GLFW_KEY_MENU:
  case GLFW_KEY_E:
    return "MENU";
    return "E";
  default:
  case GLFW_KEY_F:
    return "UNKNOWN";
    return "F";
  }
  case GLFW_KEY_G:
}
    return "G";
  case GLFW_KEY_H:
std::string key::get_actiontype_name(actiontype action) {
    return "H";
  /// Return a human-readable name for this key actiontype
  case GLFW_KEY_I:
  switch(action) {
    return "I";
  case actiontype::RELEASE:
  case GLFW_KEY_J:
    return "RELEASE";
    return "J";
  case actiontype::PRESS:
  case GLFW_KEY_K:
    return "PRESS";
    return "K";
  case actiontype::REPEAT:
  case GLFW_KEY_L:
    return "REPEAT";
    return "L";
  default:
  case GLFW_KEY_M:
    return "";
    return "M";
  }
  case GLFW_KEY_N:
}
    return "N";
  case GLFW_KEY_O:
std::string key::get_mod_name(modtype mods) {
    return "O";
  /// Return a human-readable name for this key modifier
  case GLFW_KEY_P:
  switch(mods) {
    return "P";
  case modtype::NONE:
  case GLFW_KEY_Q:
    return "NONE";
    return "Q";
  case modtype::SHIFT:
  case GLFW_KEY_R:
    return "SHIFT";
    return "R";
  case modtype::CONTROL:
  case GLFW_KEY_S:
    return "CONTROL";
    return "S";
  case modtype::SHIFT_CONTROL:
  case GLFW_KEY_T:
    return "SHIFT CONTROL";
    return "T";
  case modtype::ALT:
  case GLFW_KEY_U:
    return "ALT";
    return "U";
  case modtype::SHIFT_ALT:
  case GLFW_KEY_V:
    return "SHIFT ALT";
    return "V";
  case GLFW_KEY_W:
  case modtype::CONTROL_ALT:
    return "W";
    return "CONTROL ALT";
  case GLFW_KEY_X:
  case modtype::SHIFT_CONTROL_ALT:
    return "X";
    return "SHIFT CONTROL ALT";
  case GLFW_KEY_Y:
  case modtype::SUPER:
    return "Y";
    return "SUPER";
  case GLFW_KEY_Z:
  case modtype::SHIFT_SUPER:
    return "Z";
    return "SHIFT SUPER";
  case GLFW_KEY_LEFT_BRACKET:
  case modtype::CONTROL_SUPER:
    return "LEFT BRACKET";
    return "CONTROL SUPER";
  case GLFW_KEY_BACKSLASH:
  case modtype::SHIFT_CONTROL_SUPER:
    return "BACKSLASH";
    return "SHIFT CONTROL SUPER";
  case GLFW_KEY_RIGHT_BRACKET:
  case modtype::ALT_SUPER:
    return "RIGHT BRACKET";
    return "ALT SUPER";
  case GLFW_KEY_GRAVE_ACCENT:
    return "GRAVE ACCENT";
  case modtype::SHIFT_ALT_SUPER:
  case GLFW_KEY_WORLD_1:
    return "SHIFT ALT SUPER";
    return "WORLD 1";
  case modtype::CONTROL_ALT_SUPER:
  case GLFW_KEY_WORLD_2:
    return "CONTROL ALT SUPER";
    return "WORLD 2";
  case modtype::SHIFT_CONTROL_ALT_SUPER:
  case GLFW_KEY_ESCAPE:
    return "SHIFT CONTROL ALT SUPER";
    return "ESCAPE";
  default:
  case GLFW_KEY_ENTER:
    return "";
    return "ENTER";
  }
  case GLFW_KEY_TAB:
}
    return "TAB";

  case GLFW_KEY_BACKSPACE:
void key::reset() {
    return "BACKSPACE";
  case GLFW_KEY_INSERT:
  /// Assign a safe default non-functional function to all keys
    return "INSERT";
  for(auto const &mods : modtype()) {
  case GLFW_KEY_DELETE:
    for(auto const &action : actiontype()) {
    return "DELETE";
      for(keytype this_key = 0; this_key != max; ++this_key) {
  case GLFW_KEY_RIGHT:
        #ifdef DEBUG_INPUTSTORM
    return "RIGHT";
          std::stringstream ss;
  case GLFW_KEY_LEFT:
          ss << "InputStorm: DEBUG: unbound this_key function called on key " << this_key << " (" << get_name(this_key) << ")";
    return "LEFT";
  case GLFW_KEY_DOWN:
          if(mods != modtype::NONE) {
    return "DOWN";
            ss << " mods " << get_mod_name(mods);
  case GLFW_KEY_UP:
          }
    return "UP";
          ss << " action " << get_actiontype_name(action);
  case GLFW_KEY_PAGE_UP:
          if(action == actiontype::PRESS) {
    return "PAGE UP";
            bind(this_key, action, mods, [s = ss.str()]{
  case GLFW_KEY_PAGE_DOWN:
              std::cout << s << std::endl;
    return "PAGE DOWN";
  case GLFW_KEY_HOME:
            });
    return "HOME";
          } else {
  case GLFW_KEY_END:
            bind(this_key, action, mods, []{});
    return "END";
          }
  case GLFW_KEY_CAPS_LOCK:
        #else
    return "CAPS LOCK";
          bind(this_key, action, mods, []{});                                   // default to noop
  case GLFW_KEY_SCROLL_LOCK:
        #endif // DEBUG_INPUTSTORM
    return "SCROLL LOCK";
      }
  case GLFW_KEY_NUM_LOCK:
    }
    return "NUM LOCK";
  }
  case GLFW_KEY_PRINT_SCREEN:
}
    return "PRINT_SCREEN";

  case GLFW_KEY_PAUSE:
    return "PAUSE";
void key::bind(keytype this_key, actiontype action, modtype mods, std::function<void()> func) {
  case GLFW_KEY_F1:
  /// Bind a function to a key
    return "F1";
  #ifndef NDEBUG
  case GLFW_KEY_F2:
    if(!func) {
    return "F2";
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(this_key) << ", this will throw an exception if called!" << std::endl;
  case GLFW_KEY_F3:
    }
    return "F3";
  #endif // NDEBUG
  case GLFW_KEY_F4:
    return "F4";
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = func;
  case GLFW_KEY_F5:
}
    return "F5";
void key::bind_any_mod(keytype this_key, actiontype action, std::function<void()> func) {
  case GLFW_KEY_F6:
  /// Helper function to bind a callback to a key with any modifier combination
    return "F6";
  for(auto const &mods : modtype()) {
  case GLFW_KEY_F7:
    bind(this_key, action, mods, func);
    return "F7";
  }
  case GLFW_KEY_F8:
}
    return "F8";
void key::bind_any(std::function<void()> func) {
  case GLFW_KEY_F9:
    return "F9";
  /// Helper function to bind a callback to all keys, press event only
  case GLFW_KEY_F10:
  for(keytype this_key = 0; this_key != max; ++this_key) {
    return "F10";
    bind_any_mod(this_key, actiontype::PRESS, func);
  case GLFW_KEY_F11:
  }
    return "F11";
}
  case GLFW_KEY_F12:
void key::bind(key::binding const &this_binding,
    return "F12";
               std::function<void()> func_press,
  case GLFW_KEY_F13:
               std::function<void()> func_release,
    return "F13";
               std::function<void()> func_repeat) {
  case GLFW_KEY_F14:
  /// Helper function to load binding settings from a binding object
    return "F14";
  case GLFW_KEY_F15:
  switch(this_binding.type) {
    return "F15";
  case binding::bindtype::SPECIFIC:
  case GLFW_KEY_F16:
    if(func_press) {
    return "F16";
      bind(this_binding.key, actiontype::PRESS, this_binding.mods, func_press);
  case GLFW_KEY_F17:
    }
    return "F17";
    if(func_release) {
  case GLFW_KEY_F18:
      bind_any_mod(this_binding.key, actiontype::RELEASE, func_release);        // for release actions, always accept any modifier
    return "F18";
    }
  case GLFW_KEY_F19:
    if(func_repeat) {
    return "F19";
  case GLFW_KEY_F20:
      bind(this_binding.key, actiontype::REPEAT, this_binding.mods, func_repeat);
    return "F20";
    }
  case GLFW_KEY_F21:
    break;
    return "F21";
  case binding::bindtype::ANY_MOD:
  case GLFW_KEY_F22:
    if(func_press) {
    return "F22";
      bind_any_mod(this_binding.key, actiontype::PRESS, func_press);
  case GLFW_KEY_F23:
    }
    return "F23";
    if(func_release) {
  case GLFW_KEY_F24:
      bind_any_mod(this_binding.key, actiontype::RELEASE, func_release);
    return "F24";
    }
  case GLFW_KEY_F25:
    if(func_repeat) {
    return "F25";
  case GLFW_KEY_KP_0:
      bind_any_mod(this_binding.key, actiontype::REPEAT, func_repeat);
    return "KEYPAD 0";
    }
  case GLFW_KEY_KP_1:
    break;
    return "KEYPAD 1";
  case binding::bindtype::ANY:
  case GLFW_KEY_KP_2:
    if(func_press) {
    return "KEYPAD 2";
      bind_any(func_press);
  case GLFW_KEY_KP_3:
    } else {
    return "KEYPAD 3";
      std::cout << "InputStorm: Key: WARNING - requested to bind to any key with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
  case GLFW_KEY_KP_4:
    return "KEYPAD 4";
    }
  case GLFW_KEY_KP_5:
    break;
    return "KEYPAD 5";
  case binding::bindtype::END:
  case GLFW_KEY_KP_6:
    #ifndef NDEBUG
    return "KEYPAD 6";
      std::cout << "InputStorm: ERROR: bind target has an invalid bindtype END!" << std::endl;
  case GLFW_KEY_KP_7:
    #endif // NDEBUG
    return "KEYPAD 7";
    break;
  case GLFW_KEY_KP_8:
  }
    return "KEYPAD 8";
}
  case GLFW_KEY_KP_9:

    return "KEYPAD 9";
  case GLFW_KEY_KP_DECIMAL:
void key::unbind(keytype this_key, actiontype action, modtype mods) {
    return "KEYPAD DECIMAL";
  if(action == actiontype::RELEASE) {
  case GLFW_KEY_KP_DIVIDE:
    for(auto const &this_mod : modtype()) {                                     // release actions are bound to any modifier, so must be unbound for all
    return "KEYPAD DIVIDE";
      bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(this_mod)][static_cast<unsigned int>(this_key)] = []{}; // noop
  case GLFW_KEY_KP_MULTIPLY:
    }
    return "KEYPAD MULTIPLY";
  } else {
  case GLFW_KEY_KP_SUBTRACT:
    bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = []{}; // noop
    return "KEYPAD SUBTRACT";
  }
  case GLFW_KEY_KP_ADD:
}
    return "KEYPAD ADD";
  case GLFW_KEY_KP_ENTER:
void key::unbind_any_mod(keytype this_key, actiontype action) {
    return "KEYPAD ENTER";
  /// Helper function to unbind callbacks from a key with any modifier
  case GLFW_KEY_KP_EQUAL:
  for(auto const &mods : modtype()) {
    return "KEYPAD EQUAL";
    unbind(this_key, action, mods);
  case GLFW_KEY_LEFT_SHIFT:
  }
    return "LEFT SHIFT";
}
  case GLFW_KEY_LEFT_CONTROL:
void key::unbind_any() {
    return "LEFT CONTROL";
  /// Helper function to unbind callbacks from all keys, all events
  case GLFW_KEY_LEFT_ALT:
  for(keytype this_key = 0; this_key != max; ++this_key) {
    return "LEFT ALT";
    unbind_any_mod(this_key, actiontype::PRESS);
  case GLFW_KEY_LEFT_SUPER:
    return "LEFT SUPER";
    unbind_any_mod(this_key, actiontype::RELEASE);
  case GLFW_KEY_RIGHT_SHIFT:
    unbind_any_mod(this_key, actiontype::REPEAT);
    return "RIGHT SHIFT";
  }
  case GLFW_KEY_RIGHT_CONTROL:
}
    return "RIGHT CONTROL";
void key::unbind(binding const &this_binding) {
  case GLFW_KEY_RIGHT_ALT:
  switch(this_binding.type) {
    return "RIGHT ALT";
  case binding::bindtype::SPECIFIC:
  case GLFW_KEY_RIGHT_SUPER:
    unbind(this_binding.key, actiontype::PRESS,   this_binding.mods);
    return "RIGHT SUPER";
    unbind(this_binding.key, actiontype::RELEASE, this_binding.mods);
  case GLFW_KEY_MENU:
    return "MENU";
    unbind(this_binding.key, actiontype::REPEAT,  this_binding.mods);
  default:
    break;
    return "UNKNOWN";
  case binding::bindtype::ANY_MOD:
  }
    unbind_any_mod(this_binding.key, actiontype::PRESS);
}
    unbind_any_mod(this_binding.key, actiontype::RELEASE);
std::string key::get_actiontype_name(actiontype action) {
    unbind_any_mod(this_binding.key, actiontype::REPEAT);
  /// Return a human-readable name for this key actiontype
    break;
  switch(action) {
  case binding::bindtype::ANY:
  case actiontype::RELEASE:
    unbind_any();
    return "RELEASE";
    break;
  case actiontype::PRESS:
  case binding::bindtype::END:
    return "PRESS";
    #ifndef NDEBUG
  case actiontype::REPEAT:
    return "REPEAT";
      std::cout << "InputStorm: ERROR: unbind target has an invalid bindtype END!" << std::endl;
  default:
    #endif // NDEBUG
    return "";
    break;
  }
  }
}
}
std::string key::get_mod_name(modtype mods) {

  /// Return a human-readable name for this key modifier
void key::execute(keytype this_key, actiontype action, modtype mods) const {
  switch(mods) {
  /// Call the function associated with a given key
  case modtype::NONE:
  #ifndef NDEBUG
    return "NONE";
    if(!binding_at(this_key, action, mods)) {
  case modtype::SHIFT:
    return "SHIFT";
      std::cout << "InputStorm: ERROR: Called key " << get_name(this_key) << " which has a null function, fix this for release!" << std::endl;
  case modtype::CONTROL:
      return;
    return "CONTROL";
    }
  case modtype::SHIFT_CONTROL:
  #endif // NDEBUG
    return "SHIFT CONTROL";
  binding_at(this_key, action, mods)();
  case modtype::ALT:
}
    return "ALT";

  case modtype::SHIFT_ALT:
void key::capture(std::function<void(keytype, modtype)> callback) {
    return "SHIFT ALT";
  case modtype::CONTROL_ALT:
  /// Capture a keystroke and return it to the given callback
    return "CONTROL ALT";
  #ifdef DEBUG_INPUTSTORM
  case modtype::SHIFT_CONTROL_ALT:
    std::cout << "InputStorm: DEBUG: capturing keystroke" << std::endl;
    return "SHIFT CONTROL ALT";
  #endif // DEBUG_INPUTSTORM
  case modtype::SUPER:
  for(keytype this_key = 0; this_key != max; ++this_key) {                      // create a new callback for each key
    return "SUPER";
    for(auto const &mods : modtype()) {
  case modtype::SHIFT_SUPER:
      bind(this_key, actiontype::PRESS,   mods, []{});                          // unbind press actions
    return "SHIFT SUPER";
      bind(this_key, actiontype::REPEAT,  mods, []{});                          // unbind repeat actions
  case modtype::CONTROL_SUPER:
    return "CONTROL SUPER";
      bind(this_key, actiontype::RELEASE, mods, [callback, this_key, mods]{
  case modtype::SHIFT_CONTROL_SUPER:
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
    return "SHIFT CONTROL SUPER";
        callback(this_key, mods);
      });
    }
  case modtype::ALT_SUPER:
  }
    return "ALT SUPER";
}
  case modtype::SHIFT_ALT_SUPER:

    return "SHIFT ALT SUPER";
void key::capture(std::function<void(binding const&)> callback) {
  case modtype::CONTROL_ALT_SUPER:
  /// Capture a keystroke and return it to the given callback as a binding object
    return "CONTROL ALT SUPER";
  #ifdef DEBUG_INPUTSTORM
  case modtype::SHIFT_CONTROL_ALT_SUPER:
    return "SHIFT CONTROL ALT SUPER";
    std::cout << "InputStorm: DEBUG: capturing keystroke to binding" << std::endl;
  default:
  #endif // DEBUG_INPUTSTORM
    return "";
  for(keytype this_key = 0; this_key != max; ++this_key) {                      // create a new callback for each key
  }
    for(auto const &mods : modtype()) {
}
      bind(this_key, actiontype::PRESS,   mods, []{});                          // unbind press actions

      bind(this_key, actiontype::REPEAT,  mods, []{});                          // unbind repeat actions
void key::reset() {
      bind(this_key, actiontype::RELEASE, mods, [callback, this_key, mods]{
  /// Assign a safe default non-functional function to all keys
  for(auto const &mods : modtype()) {
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
    for(auto const &action : actiontype()) {
        callback(binding{binding::bindtype::SPECIFIC, this_key, mods});
      for(keytype this_key = 0; this_key != max; ++this_key) {
      });
        #ifdef DEBUG_INPUTSTORM
    }
          std::stringstream ss;
  }
          ss << "InputStorm: DEBUG: unbound this_key function called on key " << this_key << " (" << get_name(this_key) << ")";
}
          if(mods != modtype::NONE) {

            ss << " mods " << get_mod_name(mods);
}
          }
}
          ss << " action " << get_actiontype_name(action);
          if(action == actiontype::PRESS) {
            bind(this_key, action, mods, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind(this_key, action, mods, []{});
          }
        #else
          bind(this_key, action, mods, []{});                                   // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }
}

void key::bind(keytype this_key, actiontype action, modtype mods, std::function<void()> func) {
  /// Bind a function to a key
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(this_key) << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = func;
}
void key::bind_any_mod(keytype this_key, actiontype action, std::function<void()> func) {
  /// Helper function to bind a callback to a key with any modifier combination
  for(auto const &mods : modtype()) {
    bind(this_key, action, mods, func);
  }
}
void key::bind_any(std::function<void()> func) {
  /// Helper function to bind a callback to all keys, press event only
  for(keytype this_key = 0; this_key != max; ++this_key) {
    bind_any_mod(this_key, actiontype::PRESS, func);
  }
}
void key::bind(key::binding const &this_binding,
               std::function<void()> func_press,
               std::function<void()> func_release,
               std::function<void()> func_repeat) {
  /// Helper function to load binding settings from a binding object
  switch(this_binding.type) {
  case binding::bindtype::SPECIFIC:
    if(func_press) {
      bind(this_binding.key, actiontype::PRESS, this_binding.mods, func_press);
    }
    if(func_release) {
      bind_any_mod(this_binding.key, actiontype::RELEASE, func_release);        // for release actions, always accept any modifier
    }
    if(func_repeat) {
      bind(this_binding.key, actiontype::REPEAT, this_binding.mods, func_repeat);
    }
    break;
  case binding::bindtype::ANY_MOD:
    if(func_press) {
      bind_any_mod(this_binding.key, actiontype::PRESS, func_press);
    }
    if(func_release) {
      bind_any_mod(this_binding.key, actiontype::RELEASE, func_release);
    }
    if(func_repeat) {
      bind_any_mod(this_binding.key, actiontype::REPEAT, func_repeat);
    }
    break;
  case binding::bindtype::ANY:
    if(func_press) {
      bind_any(func_press);
    } else {
      std::cout << "InputStorm: Key: WARNING - requested to bind to any key with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
    }
    break;
  case binding::bindtype::END:
    #ifndef NDEBUG
      std::cout << "InputStorm: ERROR: bind target has an invalid bindtype END!" << std::endl;
    #endif // NDEBUG
    break;
  }
}

void key::unbind(keytype this_key, actiontype action, modtype mods) {
  if(action == actiontype::RELEASE) {
    for(auto const &this_mod : modtype()) {                                     // release actions are bound to any modifier, so must be unbound for all
      bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(this_mod)][static_cast<unsigned int>(this_key)] = []{}; // noop
    }
  } else {
    bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)] = []{}; // noop
  }
}
void key::unbind_any_mod(keytype this_key, actiontype action) {
  /// Helper function to unbind callbacks from a key with any modifier
  for(auto const &mods : modtype()) {
    unbind(this_key, action, mods);
  }
}
void key::unbind_any() {
  /// Helper function to unbind callbacks from all keys, all events
  for(keytype this_key = 0; this_key != max; ++this_key) {
    unbind_any_mod(this_key, actiontype::PRESS);
    unbind_any_mod(this_key, actiontype::RELEASE);
    unbind_any_mod(this_key, actiontype::REPEAT);
  }
}
void key::unbind(binding const &this_binding) {
  switch(this_binding.type) {
  case binding::bindtype::SPECIFIC:
    unbind(this_binding.key, actiontype::PRESS,   this_binding.mods);
    unbind(this_binding.key, actiontype::RELEASE, this_binding.mods);
    unbind(this_binding.key, actiontype::REPEAT,  this_binding.mods);
    break;
  case binding::bindtype::ANY_MOD:
    unbind_any_mod(this_binding.key, actiontype::PRESS);
    unbind_any_mod(this_binding.key, actiontype::RELEASE);
    unbind_any_mod(this_binding.key, actiontype::REPEAT);
    break;
  case binding::bindtype::ANY:
    unbind_any();
    break;
  case binding::bindtype::END:
    #ifndef NDEBUG
      std::cout << "InputStorm: ERROR: unbind target has an invalid bindtype END!" << std::endl;
    #endif // NDEBUG
    break;
  }
}

void key::execute(keytype this_key, actiontype action, modtype mods) const {
  /// Call the function associated with a given key
  #ifndef NDEBUG
    if(!binding_at(this_key, action, mods)) {
      std::cout << "InputStorm: ERROR: Called key " << get_name(this_key) << " which has a null function, fix this for release!" << std::endl;
      return;
    }
  #endif // NDEBUG
  binding_at(this_key, action, mods)();
}

void key::capture(std::function<void(keytype, modtype)> callback) {
  /// Capture a keystroke and return it to the given callback
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing keystroke" << std::endl;
  #endif // DEBUG_INPUTSTORM
  for(keytype this_key = 0; this_key != max; ++this_key) {                      // create a new callback for each key
    for(auto const &mods : modtype()) {
      bind(this_key, actiontype::PRESS,   mods, []{});                          // unbind press actions
      bind(this_key, actiontype::REPEAT,  mods, []{});                          // unbind repeat actions
      bind(this_key, actiontype::RELEASE, mods, [callback, this_key, mods]{
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
        callback(this_key, mods);
      });
    }
  }
}

void key::capture(std::function<void(binding const&)> callback) {
  /// Capture a keystroke and return it to the given callback as a binding object
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing keystroke to binding" << std::endl;
  #endif // DEBUG_INPUTSTORM
  for(keytype this_key = 0; this_key != max; ++this_key) {                      // create a new callback for each key
    for(auto const &mods : modtype()) {
      bind(this_key, actiontype::PRESS,   mods, []{});                          // unbind press actions
      bind(this_key, actiontype::REPEAT,  mods, []{});                          // unbind repeat actions
      bind(this_key, actiontype::RELEASE, mods, [callback, this_key, mods]{
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
        callback(binding{binding::bindtype::SPECIFIC, this_key, mods});
      });
    }
  }
}

}
}
