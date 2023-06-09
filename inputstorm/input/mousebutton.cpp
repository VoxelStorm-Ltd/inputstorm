#include "mousebutton.h"
#include <iostream>
#ifdef DEBUG_INPUTSTORM
  #include <sstream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm::input {

void mousebutton::init() {
  // assign a safe default function to all mouse buttons
  for(auto const &mods : key::modtype()) {
    for(actiontype action : actiontype()) {
      for(buttontype button = 0; button != max; ++button) {
        #ifdef DEBUG_INPUTSTORM
          std::stringstream ss;
          ss << "InputStorm: DEBUG: unbound mouse function called on button " << button << " (" << get_name(button) << ")";
          if(mods != key::modtype::NONE) {
            ss << " mods " << key::get_mod_name(mods);
          }
          ss << " action " << get_actiontype_name(action);
          if(action == actiontype::PRESS) {
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

std::function<void()> const &mousebutton::binding_at(mousebutton::buttontype button, actiontype action, key::modtype mods) const {
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

std::string mousebutton::get_name(buttontype button) {
  /// Return the button name from its GLFW button ID number
  switch(button) {
  case GLFW_MOUSE_BUTTON_1:
    return "LEFT MOUSE";
  case GLFW_MOUSE_BUTTON_2:
    return "RIGHT MOUSE";
  case GLFW_MOUSE_BUTTON_3:
    return "MIDDLE MOUSE";
  case GLFW_MOUSE_BUTTON_4:
    return "MOUSE 4";
  case GLFW_MOUSE_BUTTON_5:
    return "MOUSE 5";
  case GLFW_MOUSE_BUTTON_6:
    return "MOUSE 6";
  case GLFW_MOUSE_BUTTON_7:
    return "MOUSE 7";
  case GLFW_MOUSE_BUTTON_8:
    return "MOUSE 8";
  default:
    return "UNKNOWN";
  }
}
std::string mousebutton::get_actiontype_name(actiontype action) {
  /// Return a human-readable name for this mousebutton actiontype
  switch(action) {
  case actiontype::RELEASE:
    return "RELEASE";
  case actiontype::PRESS:
    return "PRESS";
  default:
    return "";
  }
}

void mousebutton::bind(buttontype button, actiontype action, key::modtype mods, std::function<void()> func) {
  /// Bind a function to a mouse button
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(button) << ", this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)] = func;
}
void mousebutton::bind_any_mod(buttontype button, actiontype action, std::function<void()> func) {
  /// Helper function to bind a callback to a key with any modifier combination
  for(auto const &mods : key::modtype()) {
    bind(button, action, mods, func);
  }
}
void mousebutton::bind_any(std::function<void()> func) {
  /// Helper function to bind a callback to all mouse buttons, press event only
  for(buttontype button = 0; button != max; ++button) {
    bind_any_mod(button, actiontype::PRESS, func);
  }
}
void mousebutton::bind(mousebutton::binding const &this_binding,
                       std::function<void()> func_press,
                       std::function<void()> func_release) {
  /// Helper function to load binding settings from a binding object
  switch(this_binding.type) {
  case binding::bindtype::SPECIFIC:
    if(func_press) {
      bind(this_binding.button, actiontype::PRESS, this_binding.mods, func_press);
    }
    if(func_release) {
      bind(this_binding.button, actiontype::RELEASE, this_binding.mods, func_release);
    }
    break;
  case binding::bindtype::ANY_MOD:
    if(func_press) {
      bind_any_mod(this_binding.button, actiontype::PRESS, func_press);
    }
    if(func_release) {
      bind_any_mod(this_binding.button, actiontype::RELEASE, func_release);
    }
    break;
  case binding::bindtype::ANY:
    if(func_press) {
      bind_any(func_press);
    } else {
      std::cout << "InputStorm: Key: WARNING - requested to bind to any mouse button with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
    }
    break;
  case binding::bindtype::END:
    #ifndef NDEBUG
      std::cout << "InputStorm: ERROR: bind target has an invalid bindtype END!" << std::endl;
    #endif // NDEBUG
    break;
  }
}

void mousebutton::unbind(buttontype button, actiontype action, key::modtype mods) {
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)] = []{}; // noop
}
void mousebutton::unbind_any_mod(buttontype button, actiontype action) {
  /// Helper function to unbind key callbacks with any modifier combination
  for(auto const &mods : key::modtype()) {
    unbind(button, action, mods);
  }
}
void mousebutton::unbind_any() {
  /// Helper function to unbindbind all mouse buttons, all events
  for(buttontype button = 0; button != max; ++button) {
    unbind_any_mod(button, actiontype::PRESS);
    unbind_any_mod(button, actiontype::RELEASE);
  }
}
void mousebutton::unbind(binding const &this_binding) {
  switch(this_binding.type) {
  case binding::bindtype::SPECIFIC:
    unbind(this_binding.button, actiontype::PRESS,   this_binding.mods);
    unbind(this_binding.button, actiontype::RELEASE, this_binding.mods);
    break;
  case binding::bindtype::ANY_MOD:
    unbind_any_mod(this_binding.button, actiontype::PRESS);
    unbind_any_mod(this_binding.button, actiontype::RELEASE);
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

void mousebutton::execute(buttontype button, actiontype action, key::modtype mods) const {
  /// Call the function associated with a given key
  #ifndef NDEBUG
    if(!binding_at(button, action, mods)) {
      std::cout << "InputStorm: ERROR: Called mousebutton " << get_name(button) << " which has a null function, fix this for release!" << std::endl;
      return;
    }
  #endif // NDEBUG
  binding_at(button, action, mods)();
}

void mousebutton::capture(std::function<void(buttontype, key::modtype)> callback) {
  /// Capture a button press and return it to the given callback
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing mousebutton" << std::endl;
  #endif // DEBUG_INPUTSTORM
  for(buttontype this_button = 0; this_button != max; ++this_button) {          // create a new callback for each key
    for(auto const &mods : key::modtype()) {
      bind(this_button, actiontype::PRESS,   mods, []{});                       // unbind press actions
      bind(this_button, actiontype::RELEASE, mods, [callback, this_button, mods]{
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
        callback(this_button, mods);
      });
    }
  }
}
void mousebutton::capture(std::function<void(binding const&)> callback) {
  /// Capture a button press and return it to the given callback as a binding object
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing mousebutton to binding" << std::endl;
  #endif // DEBUG_INPUTSTORM
  for(buttontype this_button = 0; this_button != max; ++this_button) {          // create a new callback for each key
    for(auto const &mods : key::modtype()) {
      bind(this_button, actiontype::PRESS,   mods, []{});                       // unbind press actions
      bind(this_button, actiontype::RELEASE, mods, [callback, this_button, mods]{
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
        callback(binding{binding::bindtype::SPECIFIC, this_button, mods});
      });
    }
  }
}

}
