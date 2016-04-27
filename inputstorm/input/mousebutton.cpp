#include "mousebutton.h"
#include <iostream>

namespace inputstorm {
namespace input {

unsigned int constexpr mousebutton::max;
unsigned int constexpr mousebutton::max_action;

void mousebutton::init() {
  name_at(GLFW_MOUSE_BUTTON_1) = "MOUSE LEFT";
  name_at(GLFW_MOUSE_BUTTON_2) = "MOUSE RIGHT";
  name_at(GLFW_MOUSE_BUTTON_3) = "MOUSE MIDDLE";
  name_at(GLFW_MOUSE_BUTTON_4) = "MOUSE 4";
  name_at(GLFW_MOUSE_BUTTON_5) = "MOUSE 5";
  name_at(GLFW_MOUSE_BUTTON_6) = "MOUSE 6";
  name_at(GLFW_MOUSE_BUTTON_7) = "MOUSE 7";
  name_at(GLFW_MOUSE_BUTTON_8) = "MOUSE 8";

  // assign a safe default function to all mouse buttons
  for(key::modtype mods = key::modtype::NONE;
      mods != static_cast<key::modtype>(key::max_mods);
      mods = static_cast<key::modtype>(static_cast<int>(mods) + 1)) {
    for(key::actiontype action = key::actiontype::RELEASE;
        action != static_cast<key::actiontype>(max_action);
        action = static_cast<key::actiontype>(static_cast<int>(action) + 1)) {
      for(buttontype button = 0; button != max; ++button) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound mouse function called on button " << button << " (" << get_name(button) << ")";
          if(mods != key::modtype::NONE) {
            ss << " mods " << get_keymod_name(mods);
          }
          ss << " action " << get_keyaction_name(action);
          if(action == key::actiontype::PRESS) {
            bind(button, action, mods, [s = ss.str()]{
              std::cout << s << std::endl;
            });
          } else {
            bind(button, action, mods, []{});
          }
        #else
          bind(button, action, mods, []{});                                     // default to noop
        #endif // DEBUG_INPUTSTORM
      }
    }
  }

  // report status
  std::cout << "InputStorm: Mouse button bindings:    " << sizeof(bindings) / 1024 << "KB" << std::endl;
}

std::string &mousebutton::name_at(mousebutton::buttontype button) {
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
  return names[button];
}

std::function<void()> &mousebutton::binding_at(mousebutton::buttontype button, key::actiontype action, key::modtype mods) {
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
  return bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)];
}

std::string const &mousebutton::get_name(buttontype button) const {
  /// Return the button name from its GLFW button ID number
  // check for negatives first, as GLFW likes to play that game!
  if(button < 0) {
    button = 0;                                                                 // default this to unknown button
  }
  #ifndef NDEBUG
    if(button > GLFW_MOUSE_BUTTON_LAST) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a mouse button number " << button << " which is past the last button " << GLFW_MOUSE_BUTTON_LAST << ", aborting!" << std::endl;
      abort();
    }
  #endif // NDEBUG
  return names[button];
}

void mousebutton::bind(buttontype button, key::actiontype action, key::modtype mods, std::function<void()> func) {
  /// Bind a function to a mouse button
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(button) << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  binding_at(button, action, mods) = func;
}
void mousebutton::bind_any_mod(buttontype button, key::actiontype action, std::function<void()> func) {
  /// Helper function to bind a callback to a key with any modifier combination
  for(key::modtype mods = key::modtype::NONE;
      mods != static_cast<key::modtype>(key::max_mods);
      mods = static_cast<key::modtype>(static_cast<int>(mods) + 1)) {
    bind(button, action, mods, func);
  }
}
void mousebutton::bind_any(std::function<void()> func) {
  /// Helper function to bind a callback to all mouse buttons, press event only
  for(buttontype button = 0; button != max; ++button) {
    bind_any_mod(button, key::actiontype::PRESS, func);
  }
}

void mousebutton::unbind(buttontype button, key::actiontype action, key::modtype mods) {
  binding_at(button, action, mods) = []{};                                      // noop
}
void mousebutton::unbind_any_mod(buttontype button, key::actiontype action) {
  /// Helper function to unbind key callbacks with any modifier combination
  for(key::modtype mods = key::modtype::NONE;
      mods != static_cast<key::modtype>(key::max_mods);
      mods = static_cast<key::modtype>(static_cast<int>(mods) + 1)) {
    unbind(button, action, mods);
  }
}
void mousebutton::unbind_any() {
  /// Helper function to unbindbind all mouse buttons, all events
  for(buttontype button = 0; button != max; ++button) {
    unbind_any_mod(button, key::actiontype::PRESS);
    unbind_any_mod(button, key::actiontype::RELEASE);
    unbind_any_mod(button, key::actiontype::REPEAT);
  }
}

void mousebutton::execute(buttontype button, key::actiontype action, key::modtype mods) {
  /// Call the function associated with a given key
  #ifndef NDEBUG
    if(!binding_at(button, action, mods)) {
      std::cout << "InputStorm: ERROR: Called mousebutton " << get_name(button) << " which has a null function, fix this for release!" << std::endl;
      return;
    }
  #endif // NDEBUG
  binding_at(button, action, mods)();
}

}
}
