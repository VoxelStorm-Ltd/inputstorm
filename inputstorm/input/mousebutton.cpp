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
#include "mousebutton.h"
  #endif // NDEBUG
#include <iostream>
  return bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)];
#ifdef DEBUG_INPUTSTORM
}
  #include <sstream>

#endif // DEBUG_INPUTSTORM
std::string mousebutton::get_name(buttontype button) {

  /// Return the button name from its GLFW button ID number
namespace inputstorm {
  switch(button) {
namespace input {
  case GLFW_MOUSE_BUTTON_1:

    return "LEFT MOUSE";
void mousebutton::init() {
  case GLFW_MOUSE_BUTTON_2:
  // assign a safe default function to all mouse buttons
    return "RIGHT MOUSE";
  for(auto const &mods : key::modtype()) {
  case GLFW_MOUSE_BUTTON_3:
    for(actiontype action : actiontype()) {
    return "MIDDLE MOUSE";
      for(buttontype button = 0; button != max; ++button) {
  case GLFW_MOUSE_BUTTON_4:
        #ifdef DEBUG_INPUTSTORM
    return "MOUSE 4";
          std::stringstream ss;
  case GLFW_MOUSE_BUTTON_5:
          ss << "InputStorm: DEBUG: unbound mouse function called on button " << button << " (" << get_name(button) << ")";
    return "MOUSE 5";
          if(mods != key::modtype::NONE) {
  case GLFW_MOUSE_BUTTON_6:
            ss << " mods " << key::get_mod_name(mods);
    return "MOUSE 6";
          }
  case GLFW_MOUSE_BUTTON_7:
          ss << " action " << get_actiontype_name(action);
    return "MOUSE 7";
          if(action == actiontype::PRESS) {
  case GLFW_MOUSE_BUTTON_8:
            bind(button, action, mods, [s = ss.str()]{
    return "MOUSE 8";
              std::cout << s << std::endl;
  default:
            });
    return "UNKNOWN";
          } else {
  }
            bind(button, action, mods, []{});
}
          }
std::string mousebutton::get_actiontype_name(actiontype action) {
        #else
  /// Return a human-readable name for this mousebutton actiontype
          bind(button, action, mods, []{});                                     // default to noop
  switch(action) {
        #endif // DEBUG_INPUTSTORM
  case actiontype::RELEASE:
      }
    return "RELEASE";
    }
  case actiontype::PRESS:
  }
    return "PRESS";

  default:
  // report status
    return "";
  std::cout << "InputStorm: Mouse button bindings:    " << sizeof(bindings) / 1024 << "KB" << std::endl;
  }
}
}


std::function<void()> const &mousebutton::binding_at(mousebutton::buttontype button, actiontype action, key::modtype mods) const {
void mousebutton::bind(buttontype button, actiontype action, key::modtype mods, std::function<void()> func) {
  /// Accessor for the mousebutton function sparse arrays
  /// Bind a function to a mouse button
  #ifndef NDEBUG
  #ifndef NDEBUG
    if(button < 0) {
    if(!func) {
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a button number " << button << " which is below zero - aborting!" << std::endl;
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(button) << ", this will throw an exception if called!" << std::endl;
      abort();
    }
    }
  #endif // NDEBUG
    if(button > GLFW_MOUSE_BUTTON_LAST) {
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)] = func;
      std::cout << "InputStorm: ERROR! " << __PRETTY_FUNCTION__ << " called with a button number " << button << " which is past the last key " << GLFW_MOUSE_BUTTON_LAST << ", aborting!" << std::endl;
}
      abort();
void mousebutton::bind_any_mod(buttontype button, actiontype action, std::function<void()> func) {
    }
  /// Helper function to bind a callback to a key with any modifier combination
  #endif // NDEBUG
  for(auto const &mods : key::modtype()) {
  return bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)];
    bind(button, action, mods, func);
}
  }

}
std::string mousebutton::get_name(buttontype button) {
void mousebutton::bind_any(std::function<void()> func) {
  /// Return the button name from its GLFW button ID number
  switch(button) {
  /// Helper function to bind a callback to all mouse buttons, press event only
  case GLFW_MOUSE_BUTTON_1:
  for(buttontype button = 0; button != max; ++button) {
    return "LEFT MOUSE";
    bind_any_mod(button, actiontype::PRESS, func);
  case GLFW_MOUSE_BUTTON_2:
  }
    return "RIGHT MOUSE";
}
  case GLFW_MOUSE_BUTTON_3:
void mousebutton::bind(mousebutton::binding const &this_binding,
    return "MIDDLE MOUSE";
                       std::function<void()> func_press,
  case GLFW_MOUSE_BUTTON_4:
                       std::function<void()> func_release) {
    return "MOUSE 4";
  /// Helper function to load binding settings from a binding object
  case GLFW_MOUSE_BUTTON_5:
  switch(this_binding.type) {
    return "MOUSE 5";
  case binding::bindtype::SPECIFIC:
  case GLFW_MOUSE_BUTTON_6:
    if(func_press) {
    return "MOUSE 6";
  case GLFW_MOUSE_BUTTON_7:
      bind(this_binding.button, actiontype::PRESS, this_binding.mods, func_press);
    return "MOUSE 7";
    }
  case GLFW_MOUSE_BUTTON_8:
    if(func_release) {
    return "MOUSE 8";
      bind(this_binding.button, actiontype::RELEASE, this_binding.mods, func_release);
  default:
    }
    return "UNKNOWN";
    break;
  }
  case binding::bindtype::ANY_MOD:
}
    if(func_press) {
std::string mousebutton::get_actiontype_name(actiontype action) {
      bind_any_mod(this_binding.button, actiontype::PRESS, func_press);
  /// Return a human-readable name for this mousebutton actiontype
    }
  switch(action) {
    if(func_release) {
  case actiontype::RELEASE:
      bind_any_mod(this_binding.button, actiontype::RELEASE, func_release);
    return "RELEASE";
    }
  case actiontype::PRESS:
    break;
    return "PRESS";
  case binding::bindtype::ANY:
  default:
    if(func_press) {
    return "";
      bind_any(func_press);
  }
}
    } else {

      std::cout << "InputStorm: Key: WARNING - requested to bind to any mouse button with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
void mousebutton::bind(buttontype button, actiontype action, key::modtype mods, std::function<void()> func) {
    }
  /// Bind a function to a mouse button
    break;
  #ifndef NDEBUG
  case binding::bindtype::END:
    if(!func) {
    #ifndef NDEBUG
      std::cout << "InputStorm: WARNING: Binding a null function to key " << get_name(button) << ", this will throw an exception if called!" << std::endl;
      std::cout << "InputStorm: ERROR: bind target has an invalid bindtype END!" << std::endl;
    }
    #endif // NDEBUG
  #endif // NDEBUG
    break;
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)] = func;
  }
}
}
void mousebutton::bind_any_mod(buttontype button, actiontype action, std::function<void()> func) {

  /// Helper function to bind a callback to a key with any modifier combination
void mousebutton::unbind(buttontype button, actiontype action, key::modtype mods) {
  for(auto const &mods : key::modtype()) {
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)] = []{}; // noop
    bind(button, action, mods, func);
}
  }
}
void mousebutton::unbind_any_mod(buttontype button, actiontype action) {
void mousebutton::bind_any(std::function<void()> func) {
  /// Helper function to unbind key callbacks with any modifier combination
  /// Helper function to bind a callback to all mouse buttons, press event only
  for(auto const &mods : key::modtype()) {
  for(buttontype button = 0; button != max; ++button) {
    unbind(button, action, mods);
    bind_any_mod(button, actiontype::PRESS, func);
  }
  }
}
}
void mousebutton::unbind_any() {
  /// Helper function to unbindbind all mouse buttons, all events
void mousebutton::bind(mousebutton::binding const &this_binding,
  for(buttontype button = 0; button != max; ++button) {
                       std::function<void()> func_press,
    unbind_any_mod(button, actiontype::PRESS);
                       std::function<void()> func_release) {
    unbind_any_mod(button, actiontype::RELEASE);
  /// Helper function to load binding settings from a binding object
  }
  switch(this_binding.type) {
}
  case binding::bindtype::SPECIFIC:
void mousebutton::unbind(binding const &this_binding) {
    if(func_press) {
  switch(this_binding.type) {
      bind(this_binding.button, actiontype::PRESS, this_binding.mods, func_press);
  case binding::bindtype::SPECIFIC:
    }
    unbind(this_binding.button, actiontype::PRESS,   this_binding.mods);
    if(func_release) {
    unbind(this_binding.button, actiontype::RELEASE, this_binding.mods);
      bind(this_binding.button, actiontype::RELEASE, this_binding.mods, func_release);
    break;
    }
  case binding::bindtype::ANY_MOD:
    break;
    unbind_any_mod(this_binding.button, actiontype::PRESS);
  case binding::bindtype::ANY_MOD:
    unbind_any_mod(this_binding.button, actiontype::RELEASE);
    if(func_press) {
    break;
      bind_any_mod(this_binding.button, actiontype::PRESS, func_press);
  case binding::bindtype::ANY:
    }
    unbind_any();
    if(func_release) {
    break;
      bind_any_mod(this_binding.button, actiontype::RELEASE, func_release);
  case binding::bindtype::END:
    }
    #ifndef NDEBUG
    break;
  case binding::bindtype::ANY:
      std::cout << "InputStorm: ERROR: unbind target has an invalid bindtype END!" << std::endl;
    if(func_press) {
    #endif // NDEBUG
      bind_any(func_press);
    break;
    } else {
  }
      std::cout << "InputStorm: Key: WARNING - requested to bind to any mouse button with a function other than PRESS, this is not currently supported - create a set of specific bindings instead." << std::endl;
}
    }

    break;
void mousebutton::execute(buttontype button, actiontype action, key::modtype mods) const {
  case binding::bindtype::END:
  /// Call the function associated with a given key
    #ifndef NDEBUG
  #ifndef NDEBUG
      std::cout << "InputStorm: ERROR: bind target has an invalid bindtype END!" << std::endl;
    if(!binding_at(button, action, mods)) {
    #endif // NDEBUG
      std::cout << "InputStorm: ERROR: Called mousebutton " << get_name(button) << " which has a null function, fix this for release!" << std::endl;
    break;
      return;
  }
    }
}
  #endif // NDEBUG

  binding_at(button, action, mods)();
void mousebutton::unbind(buttontype button, actiontype action, key::modtype mods) {
}
  bindings[static_cast<unsigned int>(action)][static_cast<unsigned int>(mods)][static_cast<unsigned int>(button)] = []{}; // noop

}
void mousebutton::capture(std::function<void(buttontype, key::modtype)> callback) {
void mousebutton::unbind_any_mod(buttontype button, actiontype action) {
  /// Capture a button press and return it to the given callback
  /// Helper function to unbind key callbacks with any modifier combination
  #ifdef DEBUG_INPUTSTORM
  for(auto const &mods : key::modtype()) {
    unbind(button, action, mods);
    std::cout << "InputStorm: DEBUG: capturing mousebutton" << std::endl;
  }
  #endif // DEBUG_INPUTSTORM
}
  for(buttontype this_button = 0; this_button != max; ++this_button) {          // create a new callback for each key
void mousebutton::unbind_any() {
    for(auto const &mods : key::modtype()) {
  /// Helper function to unbindbind all mouse buttons, all events
      bind(this_button, actiontype::PRESS,   mods, []{});                       // unbind press actions
  for(buttontype button = 0; button != max; ++button) {
      bind(this_button, actiontype::RELEASE, mods, [callback, this_button, mods]{
    unbind_any_mod(button, actiontype::PRESS);
    unbind_any_mod(button, actiontype::RELEASE);
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
  }
        callback(this_button, mods);
}
      });
void mousebutton::unbind(binding const &this_binding) {
    }
  switch(this_binding.type) {
  }
  case binding::bindtype::SPECIFIC:
}
    unbind(this_binding.button, actiontype::PRESS,   this_binding.mods);
void mousebutton::capture(std::function<void(binding const&)> callback) {
    unbind(this_binding.button, actiontype::RELEASE, this_binding.mods);
  /// Capture a button press and return it to the given callback as a binding object
    break;
  #ifdef DEBUG_INPUTSTORM
  case binding::bindtype::ANY_MOD:
    std::cout << "InputStorm: DEBUG: capturing mousebutton to binding" << std::endl;
    unbind_any_mod(this_binding.button, actiontype::PRESS);
  #endif // DEBUG_INPUTSTORM
    unbind_any_mod(this_binding.button, actiontype::RELEASE);
  for(buttontype this_button = 0; this_button != max; ++this_button) {          // create a new callback for each key
    break;
    for(auto const &mods : key::modtype()) {
  case binding::bindtype::ANY:
    unbind_any();
      bind(this_button, actiontype::PRESS,   mods, []{});                       // unbind press actions
    break;
      bind(this_button, actiontype::RELEASE, mods, [callback, this_button, mods]{
  case binding::bindtype::END:
        // bind on the release action - this allows us to attach to modified keys without shift, alt etc triggering the bind first
    #ifndef NDEBUG
        callback(binding{binding::bindtype::SPECIFIC, this_button, mods});
      std::cout << "InputStorm: ERROR: unbind target has an invalid bindtype END!" << std::endl;
      });
    #endif // NDEBUG
    }
    break;
  }
  }
}
}


}
void mousebutton::execute(buttontype button, actiontype action, key::modtype mods) const {
}
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
}
