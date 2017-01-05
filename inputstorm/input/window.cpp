
void window::bind_position(std::function<void(vec2i const&)> func) {
  /// Bind a function to window being moved
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to window position, this will throw an exception if called!" << std::endl;
    }
  #endif
  position_binding = func;
}
#include "window.h"
void window::bind_resize(std::function<void(vec2i const&)> func) {
#ifndef NDEBUG
  /// Bind a function to window being resized
  #include <iostream>
  #ifndef NDEBUG
#endif // NDEBUG
    if(!func) {
#ifdef DEBUG_INPUTSTORM
      std::cout << "InputStorm: WARNING: Binding a null function to window resize, this will throw an exception if called!" << std::endl;
  #include "vectorstorm/vector/vector2.h"
    }
#endif // DEBUG_INPUTSTORM
  #endif

  resize_binding = func;
namespace inputstorm {
}
namespace input {
void window::bind_framebuffer_size(std::function<void(vec2i const&)> func) {

  /// Bind a function to framebuffer being resized
void window::bind_position(std::function<void(vec2i const&)> func) {
  #ifndef NDEBUG
  /// Bind a function to window being moved
    if(!func) {
  #ifndef NDEBUG
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to framebuffer resize, this will throw an exception if called!" << std::endl;
      std::cout << "InputStorm: WARNING: Binding a null function to window position, this will throw an exception if called!" << std::endl;
    }
    }
  #endif
  #endif
  framebuffer_size_binding = func;
  position_binding = func;
}
}
void window::bind_close(std::function<void()> func) {
void window::bind_resize(std::function<void(vec2i const&)> func) {
  /// Bind a function to window being closed
  /// Bind a function to window being resized
  #ifndef NDEBUG
  #ifndef NDEBUG
    if(!func) {
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to window close, this will throw an exception if called!" << std::endl;
      std::cout << "InputStorm: WARNING: Binding a null function to window resize, this will throw an exception if called!" << std::endl;
    }
    }
  #endif
  #endif
  close_binding = func;
  resize_binding = func;
}
}
void window::bind_framebuffer_size(std::function<void(vec2i const&)> func) {
void window::bind_refresh(std::function<void()> func) {
  /// Bind a function to framebuffer being resized
  /// Bind a function to window being refreshed
  #ifndef NDEBUG
  #ifndef NDEBUG
    if(!func) {
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to framebuffer resize, this will throw an exception if called!" << std::endl;
      std::cout << "InputStorm: WARNING: Binding a null function to window refresh, this will throw an exception if called!" << std::endl;
    }
    }
  #endif
  #endif
  framebuffer_size_binding = func;
  refresh_binding = func;
}
}
void window::bind_close(std::function<void()> func) {
void window::bind_focus_gain(std::function<void()> func) {
  /// Bind a function to window being closed
  /// Bind a function to window gaining focus
  #ifndef NDEBUG
  #ifndef NDEBUG
    if(!func) {
    if(!func) {
      std::cout << "InputStorm: WARNING: Binding a null function to window close, this will throw an exception if called!" << std::endl;
    }
      std::cout << "InputStorm: WARNING: Binding a null function to window gaining focus, this will throw an exception if called!" << std::endl;
  #endif
    }
  close_binding = func;
  #endif
}
  focus_gain_binding = func;
void window::bind_refresh(std::function<void()> func) {
}
  /// Bind a function to window being refreshed
void window::bind_focus_lose(std::function<void()> func) {
  #ifndef NDEBUG
  /// Bind a function to window losing focus
    if(!func) {
  #ifndef NDEBUG
      std::cout << "InputStorm: WARNING: Binding a null function to window refresh, this will throw an exception if called!" << std::endl;
    if(!func) {
    }
      std::cout << "InputStorm: WARNING: Binding a null function to window losing focus, this will throw an exception if called!" << std::endl;
  #endif
    }
  refresh_binding = func;
  #endif
}
  focus_lose_binding = func;
void window::bind_focus_gain(std::function<void()> func) {
}
  /// Bind a function to window gaining focus
void window::bind_minimise(std::function<void()> func) {
  #ifndef NDEBUG
  /// Bind a function to window minimise
    if(!func) {
  #ifndef NDEBUG
      std::cout << "InputStorm: WARNING: Binding a null function to window gaining focus, this will throw an exception if called!" << std::endl;
    if(!func) {
    }
  #endif
      std::cout << "InputStorm: WARNING: Binding a null function to window minimise, this will throw an exception if called!" << std::endl;
  focus_gain_binding = func;
    }
}
  #endif
void window::bind_focus_lose(std::function<void()> func) {
  minimise_binding = func;
  /// Bind a function to window losing focus
}
  #ifndef NDEBUG
void window::bind_restore(std::function<void()> func) {
    if(!func) {
  /// Bind a function to window restore
      std::cout << "InputStorm: WARNING: Binding a null function to window losing focus, this will throw an exception if called!" << std::endl;
  #ifndef NDEBUG
    }
    if(!func) {
  #endif
      std::cout << "InputStorm: WARNING: Binding a null function to window restore, this will throw an exception if called!" << std::endl;
  focus_lose_binding = func;
    }
}
  #endif
void window::bind_minimise(std::function<void()> func) {
  restore_binding = func;
  /// Bind a function to window minimise
}
  #ifndef NDEBUG

    if(!func) {
void window::unbind_position() {
      std::cout << "InputStorm: WARNING: Binding a null function to window minimise, this will throw an exception if called!" << std::endl;
    }
  position_binding = [](vec2i const &change __attribute__((__unused__))){};     // noop
  #endif
}
  minimise_binding = func;
void window::unbind_resize() {
}
  resize_binding = [](vec2i const &change __attribute__((__unused__))){};       // noop
void window::bind_restore(std::function<void()> func) {
}
  /// Bind a function to window restore
void window::unbind_close() {
  #ifndef NDEBUG
  close_binding = []{};                                                         // noop
    if(!func) {
}
      std::cout << "InputStorm: WARNING: Binding a null function to window restore, this will throw an exception if called!" << std::endl;
void window::unbind_refresh() {
    }
  #endif
  refresh_binding = []{};                                                       // noop
  restore_binding = func;
}
}
void window::unbind_focus_lose() {

  focus_gain_binding = []{};                                                    // noop
void window::unbind_position() {
}
  position_binding = [](vec2i const &change __attribute__((__unused__))){};     // noop
void window::unbind_focus_gain() {
}
  focus_lose_binding = []{};                                                    // noop
void window::unbind_resize() {
}
  resize_binding = [](vec2i const &change __attribute__((__unused__))){};       // noop
void window::unbind_minimise() {
}
  minimise_binding = []{};                                                      // noop
void window::unbind_close() {
}
  close_binding = []{};                                                         // noop
void window::unbind_restore() {
}
void window::unbind_refresh() {
  restore_binding = []{};                                                       // noop
  refresh_binding = []{};                                                       // noop
}
}
void window::unbind_framebuffer_size() {
void window::unbind_focus_lose() {
  framebuffer_size_binding = [](vec2i const &change __attribute__((__unused__))){}; // noop
  focus_gain_binding = []{};                                                    // noop
}
}

void window::unbind_focus_gain() {
void window::execute_position(vec2i const &new_position) const {
  focus_lose_binding = []{};                                                    // noop
  /// Call the function associated with window movements
}
  #ifdef DEBUG_INPUTSTORM
void window::unbind_minimise() {
    std::cout << "InputStorm: DEBUG: window position " << new_position << std::endl;
  minimise_binding = []{};                                                      // noop
  #endif // DEBUG_INPUTSTORM
}
  position_binding(new_position);
void window::unbind_restore() {
}
  restore_binding = []{};                                                       // noop
void window::execute_resize(vec2i const &new_size) const {
}
void window::unbind_framebuffer_size() {
  /// Call the function associated with window movements
  framebuffer_size_binding = [](vec2i const &change __attribute__((__unused__))){}; // noop
  #ifdef DEBUG_INPUTSTORM
}
    std::cout << "InputStorm: DEBUG: window size " << new_size << std::endl;

  #endif // DEBUG_INPUTSTORM
void window::execute_position(vec2i const &new_position) const {
  resize_binding(new_size);
  /// Call the function associated with window movements
}
  #ifdef DEBUG_INPUTSTORM
void window::execute_framebuffer_size(vec2i const &new_size) const {
    std::cout << "InputStorm: DEBUG: window position " << new_position << std::endl;
  /// Call the function associated with window movements
  #endif // DEBUG_INPUTSTORM
  #ifdef DEBUG_INPUTSTORM
  position_binding(new_position);
    std::cout << "InputStorm: DEBUG: window framebuffer size " << new_size << std::endl;
}
  #endif // DEBUG_INPUTSTORM
void window::execute_resize(vec2i const &new_size) const {
  framebuffer_size_binding(new_size);
  /// Call the function associated with window movements
}
  #ifdef DEBUG_INPUTSTORM
void window::execute_close() const {
    std::cout << "InputStorm: DEBUG: window size " << new_size << std::endl;
  /// Call the function associated with window closing
  #endif // DEBUG_INPUTSTORM
  #ifdef DEBUG_INPUTSTORM
  resize_binding(new_size);
}
    std::cout << "InputStorm: DEBUG: window close requested" << std::endl;
void window::execute_framebuffer_size(vec2i const &new_size) const {
  #endif // DEBUG_INPUTSTORM
  /// Call the function associated with window movements
  close_binding();
  #ifdef DEBUG_INPUTSTORM
}
    std::cout << "InputStorm: DEBUG: window framebuffer size " << new_size << std::endl;
void window::execute_refresh() const {
  #endif // DEBUG_INPUTSTORM
  /// Call the function associated with window refreshing
  framebuffer_size_binding(new_size);
  #ifdef DEBUG_INPUTSTORM
}
    std::cout << "InputStorm: DEBUG: window refresh requested" << std::endl;
void window::execute_close() const {
  #endif // DEBUG_INPUTSTORM
  /// Call the function associated with window closing
  refresh_binding();
  #ifdef DEBUG_INPUTSTORM
}
    std::cout << "InputStorm: DEBUG: window close requested" << std::endl;
void window::execute_focus_gain() const {
  #endif // DEBUG_INPUTSTORM
  /// Call the function associated with window gaining focus
  close_binding();
  #ifdef DEBUG_INPUTSTORM
}
void window::execute_refresh() const {
    std::cout << "InputStorm: DEBUG: window gained focus" << std::endl;
  /// Call the function associated with window refreshing
  #endif // DEBUG_INPUTSTORM
  #ifdef DEBUG_INPUTSTORM
  focus_gain_binding();
    std::cout << "InputStorm: DEBUG: window refresh requested" << std::endl;
}
  #endif // DEBUG_INPUTSTORM
void window::execute_focus_lose() const {
  refresh_binding();
  /// Call the function associated with window losing focus
}
  #ifdef DEBUG_INPUTSTORM
void window::execute_focus_gain() const {
    std::cout << "InputStorm: DEBUG: window lost focus" << std::endl;
  /// Call the function associated with window gaining focus
  #endif // DEBUG_INPUTSTORM
  #ifdef DEBUG_INPUTSTORM
  focus_lose_binding();
    std::cout << "InputStorm: DEBUG: window gained focus" << std::endl;
}
  #endif // DEBUG_INPUTSTORM
void window::execute_minimise() const {
  focus_gain_binding();
}
  /// Call the function associated with window being minimised
void window::execute_focus_lose() const {
  #ifdef DEBUG_INPUTSTORM
  /// Call the function associated with window losing focus
    std::cout << "InputStorm: DEBUG: window minimised" << std::endl;
  #ifdef DEBUG_INPUTSTORM
  #endif // DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window lost focus" << std::endl;
  minimise_binding();
  #endif // DEBUG_INPUTSTORM
}
  focus_lose_binding();
void window::execute_restore() const {
}
  /// Call the function associated with window being restored
void window::execute_minimise() const {
  #ifdef DEBUG_INPUTSTORM
  /// Call the function associated with window being minimised
    std::cout << "InputStorm: DEBUG: window restored" << std::endl;
  #ifdef DEBUG_INPUTSTORM
  #endif // DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window minimised" << std::endl;
  restore_binding();
  #endif // DEBUG_INPUTSTORM
}
  minimise_binding();

}
}
void window::execute_restore() const {
}
  /// Call the function associated with window being restored
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: window restored" << std::endl;
  #endif // DEBUG_INPUTSTORM
  restore_binding();
}

}
}
