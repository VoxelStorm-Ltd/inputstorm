#include "scroll.h"
#ifndef NDEBUG
  #include <iostream>
#endif // NDEBUG

namespace inputstorm::input {

std::string scroll::get_name(scroll::direction this_direction) {
  /// Return the this_key name from its GLFW this_key ID number
  switch(this_direction) {
  case direction::RIGHT:
    return "SCROLL RIGHT";
  case direction::LEFT:
    return "SCROLL LEFT";
  case direction::UP:
    return "SCROLL UP";
  case direction::DOWN:
    return "SCROLL DOWN";
  default:
    return "SCROLL UNKNOWN";
  }
}

void scroll::bind(std::function<void(vec2d const&)> func) {
  /// Bind a function to scrolling
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to scroll, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  binding = func;
}

void scroll::unbind() {
  binding = [](vec2d const &change [[maybe_unused]]){};                         // noop
}

void scroll::execute(vec2d const &offset) const {
  /// Call the function associated with scrolling
  binding(offset);
}

void scroll::capture(std::function<void(direction)> callback) {
  /// Capture a scroll action and return it to the given callback
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: capturing scroll" << std::endl;
  #endif // DEBUG_INPUTSTORM
  bind([callback](vec2d const &amount){
    // prioritise up/down scroll
    if(amount.y > 0.0) {
      #ifdef DEBUG_INPUTSTORM
        std::cout << "InputStorm: DEBUG: captured scroll up" << std::endl;
      #endif // DEBUG_INPUTSTORM
      callback(direction::UP);
    } else if(amount.y < 0.0) {
      #ifdef DEBUG_INPUTSTORM
        std::cout << "InputStorm: DEBUG: captured scroll down" << std::endl;
      #endif // DEBUG_INPUTSTORM
      callback(direction::DOWN);
    } else {
      // only if up/down is zero do we check for left-right
      if(amount.x > 0.0) {
        #ifdef DEBUG_INPUTSTORM
          std::cout << "InputStorm: DEBUG: captured scroll left" << std::endl;
        #endif // DEBUG_INPUTSTORM
        callback(direction::LEFT);
      } if(amount.x < 0.0) {
        #ifdef DEBUG_INPUTSTORM
          std::cout << "InputStorm: DEBUG: captured scroll right" << std::endl;
        #endif // DEBUG_INPUTSTORM
        callback(direction::RIGHT);
      }
    }
    // it's theoretically possible to receive a zero distance scroll event - ignore that if it happens
  });
}

}
