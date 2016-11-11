#include "key.h"
#include <iostream>
#ifdef DEBUG_INPUTSTORM
  #include <sstream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {
namespace input {

void key::init() {
  /// create default key bindings and initialise key names
  //std::cout << "InputStorm: Initialising keymap..." << std::endl;
  // assign a safe default function to all keys
  for(auto const &mods : modtype()) {
    for(auto const &action : actiontype()) {
      for(keytype this_key = 0; this_key != max; ++this_key) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound this_key function called on key " << this_key << " (" << get_name(this_key) << ")";
          if(mods != modtype::NONE) {
            ss << " mods " << get_mod_name(mods);
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

  // report status
  std::cout << "InputStorm: Key bindings:             " << sizeof(bindings) / 1024 << "KB" << std::endl;
}

std::function<void()> const &key::binding_at(keytype this_key, actiontype action, modtype mods) const {
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
  return bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(this_key)];
}

std::string key::get_name(keytype this_key) {
  /// Return the this_key name from its GLFW this_key ID number
  switch(this_key) {
  case GLFW_KEY_SPACE:
    return "SPACE";
  case GLFW_KEY_APOSTROPHE:
    return "APOSTROPHE";
  case GLFW_KEY_COMMA:
    return "COMMA";
  case GLFW_KEY_MINUS:
    return "MINUS";
  case GLFW_KEY_PERIOD:
    return "PERIOD";
  case GLFW_KEY_SLASH:
    return "SLASH";
  case GLFW_KEY_0:
    return "0";
  case GLFW_KEY_1:
    return "1";
  case GLFW_KEY_2:
    return "2";
  case GLFW_KEY_3:
    return "3";
  case GLFW_KEY_4:
    return "4";
  case GLFW_KEY_5:
    return "5";
  case GLFW_KEY_6:
    return "6";
  case GLFW_KEY_7:
    return "7";
  case GLFW_KEY_8:
    return "8";
  case GLFW_KEY_9:
    return "9";
  case GLFW_KEY_SEMICOLON:
    return "SEMICOLON";
  case GLFW_KEY_EQUAL:
    return "EQUALS";
  case GLFW_KEY_A:
    return "A";
  case GLFW_KEY_B:
    return "B";
  case GLFW_KEY_C:
    return "C";
  case GLFW_KEY_D:
    return "D";
  case GLFW_KEY_E:
    return "E";
  case GLFW_KEY_F:
    return "F";
  case GLFW_KEY_G:
    return "G";
  case GLFW_KEY_H:
    return "H";
  case GLFW_KEY_I:
    return "I";
  case GLFW_KEY_J:
    return "J";
  case GLFW_KEY_K:
    return "K";
  case GLFW_KEY_L:
    return "L";
  case GLFW_KEY_M:
    return "M";
  case GLFW_KEY_N:
    return "N";
  case GLFW_KEY_O:
    return "O";
  case GLFW_KEY_P:
    return "P";
  case GLFW_KEY_Q:
    return "Q";
  case GLFW_KEY_R:
    return "R";
  case GLFW_KEY_S:
    return "S";
  case GLFW_KEY_T:
    return "T";
  case GLFW_KEY_U:
    return "U";
  case GLFW_KEY_V:
    return "V";
  case GLFW_KEY_W:
    return "W";
  case GLFW_KEY_X:
    return "X";
  case GLFW_KEY_Y:
    return "Y";
  case GLFW_KEY_Z:
    return "Z";
  case GLFW_KEY_LEFT_BRACKET:
    return "LEFT BRACKET";
  case GLFW_KEY_BACKSLASH:
    return "BACKSLASH";
  case GLFW_KEY_RIGHT_BRACKET:
    return "RIGHT BRACKET";
  case GLFW_KEY_GRAVE_ACCENT:
    return "GRAVE ACCENT";
  case GLFW_KEY_WORLD_1:
    return "WORLD 1";
  case GLFW_KEY_WORLD_2:
    return "WORLD 2";
  case GLFW_KEY_ESCAPE:
    return "ESCAPE";
  case GLFW_KEY_ENTER:
    return "ENTER";
  case GLFW_KEY_TAB:
    return "TAB";
  case GLFW_KEY_BACKSPACE:
    return "BACKSPACE";
  case GLFW_KEY_INSERT:
    return "INSERT";
  case GLFW_KEY_DELETE:
    return "DELETE";
  case GLFW_KEY_RIGHT:
    return "RIGHT";
  case GLFW_KEY_LEFT:
    return "LEFT";
  case GLFW_KEY_DOWN:
    return "DOWN";
  case GLFW_KEY_UP:
    return "UP";
  case GLFW_KEY_PAGE_UP:
    return "PAGE UP";
  case GLFW_KEY_PAGE_DOWN:
    return "PAGE DOWN";
  case GLFW_KEY_HOME:
    return "HOME";
  case GLFW_KEY_END:
    return "END";
  case GLFW_KEY_CAPS_LOCK:
    return "CAPS LOCK";
  case GLFW_KEY_SCROLL_LOCK:
    return "SCROLL LOCK";
  case GLFW_KEY_NUM_LOCK:
    return "NUM LOCK";
  case GLFW_KEY_PRINT_SCREEN:
    return "PRINT_SCREEN";
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
    return "F13";
  case GLFW_KEY_F14:
    return "F14";
  case GLFW_KEY_F15:
    return "F15";
  case GLFW_KEY_F16:
    return "F16";
  case GLFW_KEY_F17:
    return "F17";
  case GLFW_KEY_F18:
    return "F18";
  case GLFW_KEY_F19:
    return "F19";
  case GLFW_KEY_F20:
    return "F20";
  case GLFW_KEY_F21:
    return "F21";
  case GLFW_KEY_F22:
    return "F22";
  case GLFW_KEY_F23:
    return "F23";
  case GLFW_KEY_F24:
    return "F24";
  case GLFW_KEY_F25:
    return "F25";
  case GLFW_KEY_KP_0:
    return "KEYPAD 0";
  case GLFW_KEY_KP_1:
    return "KEYPAD 1";
  case GLFW_KEY_KP_2:
    return "KEYPAD 2";
  case GLFW_KEY_KP_3:
    return "KEYPAD 3";
  case GLFW_KEY_KP_4:
    return "KEYPAD 4";
  case GLFW_KEY_KP_5:
    return "KEYPAD 5";
  case GLFW_KEY_KP_6:
    return "KEYPAD 6";
  case GLFW_KEY_KP_7:
    return "KEYPAD 7";
  case GLFW_KEY_KP_8:
    return "KEYPAD 8";
  case GLFW_KEY_KP_9:
    return "KEYPAD 9";
  case GLFW_KEY_KP_DECIMAL:
    return "KEYPAD DECIMAL";
  case GLFW_KEY_KP_DIVIDE:
    return "KEYPAD DIVIDE";
  case GLFW_KEY_KP_MULTIPLY:
    return "KEYPAD MULTIPLY";
  case GLFW_KEY_KP_SUBTRACT:
    return "KEYPAD SUBTRACT";
  case GLFW_KEY_KP_ADD:
    return "KEYPAD ADD";
  case GLFW_KEY_KP_ENTER:
    return "KEYPAD ENTER";
  case GLFW_KEY_KP_EQUAL:
    return "KEYPAD EQUAL";
  case GLFW_KEY_LEFT_SHIFT:
    return "LEFT SHIFT";
  case GLFW_KEY_LEFT_CONTROL:
    return "LEFT CONTROL";
  case GLFW_KEY_LEFT_ALT:
    return "LEFT ALT";
  case GLFW_KEY_LEFT_SUPER:
    return "LEFT SUPER";
  case GLFW_KEY_RIGHT_SHIFT:
    return "RIGHT SHIFT";
  case GLFW_KEY_RIGHT_CONTROL:
    return "RIGHT CONTROL";
  case GLFW_KEY_RIGHT_ALT:
    return "RIGHT ALT";
  case GLFW_KEY_RIGHT_SUPER:
    return "RIGHT SUPER";
  case GLFW_KEY_MENU:
    return "MENU";
  default:
    return "UNKNOWN";
  }
}
std::string key::get_actiontype_name(actiontype action) {
  /// Return a human-readable name for this key actiontype
  switch(action) {
  case actiontype::RELEASE:
    return "RELEASE";
  case actiontype::PRESS:
    return "PRESS";
  case actiontype::REPEAT:
    return "REPEAT";
  default:
    return "";
  }
}
std::string key::get_mod_name(modtype mods) {
  /// Return a human-readable name for this key modifier
  switch(mods) {
  case modtype::NONE:
    return "NONE";
  case modtype::SHIFT:
    return "SHIFT";
  case modtype::CONTROL:
    return "CONTROL";
  case modtype::SHIFT_CONTROL:
    return "SHIFT CONTROL";
  case modtype::ALT:
    return "ALT";
  case modtype::SHIFT_ALT:
    return "SHIFT ALT";
  case modtype::CONTROL_ALT:
    return "CONTROL ALT";
  case modtype::SHIFT_CONTROL_ALT:
    return "SHIFT CONTROL ALT";
  case modtype::SUPER:
    return "SUPER";
  case modtype::SHIFT_SUPER:
    return "SHIFT SUPER";
  case modtype::CONTROL_SUPER:
    return "CONTROL SUPER";
  case modtype::SHIFT_CONTROL_SUPER:
    return "SHIFT CONTROL SUPER";
  case modtype::ALT_SUPER:
    return "ALT SUPER";
  case modtype::SHIFT_ALT_SUPER:
    return "SHIFT ALT SUPER";
  case modtype::CONTROL_ALT_SUPER:
    return "CONTROL ALT SUPER";
  case modtype::SHIFT_CONTROL_ALT_SUPER:
    return "SHIFT CONTROL ALT SUPER";
  default:
    return "";
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
