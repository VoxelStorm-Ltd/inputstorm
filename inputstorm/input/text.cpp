#include "text.h"
#include <iostream>

namespace inputstorm::input {

void text::bind(std::function<void(char32_t)> func) {
  /// Bind a function to text input
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to text input, this will throw an exception if called!" << std::endl;
    }
  #endif // NDEBUG
  binding = func;
}

void text::unbind() {
  /// Unbind the text input function
  binding = [](char32_t codepoint __attribute__((__unused__))){};               // noop
}

void text::execute(char32_t codepoint) const {
  /// Call the function associated with text input
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: text input " << codepoint << std::endl;
  #endif // DEBUG_INPUTSTORM
  binding(codepoint);
}

}
