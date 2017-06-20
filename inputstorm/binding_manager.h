#ifndef INPUTSTORM_BINDING_MANAGER_H_INCLUDED
#define INPUTSTORM_BINDING_MANAGER_H_INCLUDED

#include <functional>
#include <vector>
#include <memory>
#include "binding_sets/base.h"
#ifdef DEBUG_INPUTSTORM
  #include <iostream>
#endif // DEBUG_INPUTSTORM

namespace inputstorm {

class manager;

template<typename T>
class binding_manager {
  using controltype = T;

  manager &input;

public:
  using analogue_function_type = std::function<void(float)>;
  struct digital_function_type {
    std::function<void()> press;
    std::function<void()> release;
  };
  std::array<analogue_function_type, static_cast<unsigned int>(controltype::END)> action_bindings_analogue;
  std::array< digital_function_type, static_cast<unsigned int>(controltype::END)> action_bindings_digital;

  std::vector<std::shared_ptr<binding_sets::base<controltype>>> binding_sets_digital;
  std::vector<std::shared_ptr<binding_sets::base<controltype>>> binding_sets_analogue;

  binding_manager(manager &input_manager);
  ~binding_manager();

  // bind and unbind functions to controls
  void bind_digital( controltype control, std::function<void()> func_press, std::function<void()> func_release = nullptr);
  void bind_analogue(controltype control, analogue_function_type func);

  void unbind_digital( controltype control);
  void unbind_analogue(controltype control);
  void unbind(         controltype control);

  // update control-based bindings
  void update_all_digital( controltype control);
  void update_all_analogue(controltype control);
};

template<typename T>
binding_manager<T>::binding_manager(manager &input_manager)
  : input(input_manager) {
  /// Default constructor
}

template<typename T>
binding_manager<T>::~binding_manager() {
  /// Default destructor
}

/////////////////// bind and unbind functions to controls //////////////////////

template<typename T>
void binding_manager<T>::bind_digital(controltype control,
                                      std::function<void()> func_press,
                                      std::function<void()> func_release) {
  /// Bind a function to a digital (instant action) control
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Binding digital function for control " << static_cast<unsigned int>(control) << std::endl;
  #endif // DEBUG_INPUTSTORM
  digital_function_type func{func_press, func_release};
  action_bindings_digital[static_cast<unsigned int>(control)] = func;
  update_all_digital(control);
}
template<typename T>
void binding_manager<T>::bind_analogue(controltype control, analogue_function_type func) {
  /// Bind a function to an analogue (sliding scale) control
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Binding analogue function for control " << static_cast<unsigned int>(control) << std::endl;
  #endif // DEBUG_INPUTSTORM
  action_bindings_analogue[static_cast<unsigned int>(control)] = func;
  update_all_analogue(control);
}

template<typename T>
void binding_manager<T>::unbind_digital(controltype control) {
  /// Unbind a digital (instant action) control
  bind_digital(control, nullptr);
  update_all_digital(control);
}
template<typename T>
void binding_manager<T>::unbind_analogue(controltype control) {
  /// Unbind an analogue (sliding scale) control
  bind_analogue(control, nullptr);
  update_all_analogue(control);
}
template<typename T>
void binding_manager<T>::unbind(controltype control) {
  /// Unbind all parts of a control
  unbind_digital( control);
  unbind_analogue(control);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void binding_manager<T>::update_all_digital(controltype control) {
  /// Set up the digital bindings for a control with a given function
  for(auto &it : binding_sets_digital) {
    it->update_all(control);
  }
}

template<typename T>
void binding_manager<T>::update_all_analogue(controltype control) {
  /// Set up the analogue bindings for a control with a given function
  for(auto &it : binding_sets_analogue) {
    it->update_all(control);
  }
}

}

#endif // INPUTSTORM_BINDING_MANAGER_H_INCLUDED
