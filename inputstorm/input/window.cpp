#include "window.h"
#ifndef NDEBUG
  #include <iostream>
#endif // NDEBUG


namespace inputstorm {
namespace input {

void window::bind_position(std::function<void(vec2i const&)> func) {
  /// Bind a function to window entering the window
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to window entering the window, this will throw an exception if called!" << std::endl;
    }
  #endif
  position_binding = func;
}

void window::unbind_position() {
  position_binding = [](vec2i const &change __attribute__((__unused__))){};     // noop
}
void window::unbind_resize() {
  resize_binding = [](vec2i const &change __attribute__((__unused__))){};       // noop
}
void window::unbind_close() {
  close_binding = []{};                                                         // noop
}
void window::unbind_refresh() {
  refresh_binding = []{};                                                       // noop
}
void window::unbind_focus_lose() {
  focus_gain_binding = []{};                                                    // noop
}
void window::unbind_focus_gain() {
  focus_lose_binding = []{};                                                    // noop
}
void window::unbind_minimise() {
  minimise_binding = []{};                                                      // noop
}
void window::unbind_restore() {
  restore_binding = []{};                                                       // noop
}
void window::unbind_framebuffer_size() {
  framebuffer_size_binding = [](vec2i const &change __attribute__((__unused__))){}; // noop
}

void window::execute_position(vec2i const &new_position) const {
  /// Call the function associated with window movements
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window position " << new_position << std::endl;
  #endif // DEBUG_INPUTSTORM
  position_binding(new_position);
}
void window::execute_resize(vec2i const &new_size) const {
  /// Call the function associated with window movements
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window size " << new_size << std::endl;
  #endif // DEBUG_INPUTSTORM
  resize_binding(new_size);
}
void window::execute_framebuffer_size(vec2i const &new_size) const {
  /// Call the function associated with window movements
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window framebuffer size " << new_size << std::endl;
  #endif // DEBUG_INPUTSTORM
  framebuffer_size_binding(new_size);
}
void window::execute_close() const {
  /// Call the function associated with window closing
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window close requested" << std::endl;
  #endif // DEBUG_INPUTSTORM
  close_binding();
}
void window::execute_refresh() const {
  /// Call the function associated with window refreshing
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window refresh requested" << std::endl;
  #endif // DEBUG_INPUTSTORM
  refresh_binding();
}
void window::execute_focus_gain() const {
  /// Call the function associated with window gaining focus
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window gained focus" << std::endl;
  #endif // DEBUG_INPUTSTORM
  focus_gain_binding();
}
void window::execute_focus_lose() const {
  /// Call the function associated with window losing focus
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window lost focus" << std::endl;
  #endif // DEBUG_INPUTSTORM
  focus_lose_binding();
}
void window::execute_minimise() const {
  /// Call the function associated with window being minimised
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window minimised" << std::endl;
  #endif // DEBUG_INPUTSTORM
  minimise_binding();
}
void window::execute_restore() const {
  /// Call the function associated with window being restored
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window restored" << std::endl;
  #endif // DEBUG_INPUTSTORM
  restore_binding();
}

}
}
