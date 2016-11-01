#ifndef INPUTSTORM_BINDING_MANAGER_H_INCLUDED
#define INPUTSTORM_BINDING_MANAGER_H_INCLUDED

#include <unordered_map>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include "manager.h"
#include "binding_sets/key.h"
#include "binding_sets/mousebutton.h"
#include "binding_sets/scroll.h"
#include "binding_sets/joystick_button.h"
#include "binding_sets/joystick_axis.h"
#ifndef DEBUG_INPUTSTORM
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

  binding_sets::key<            controltype> key;
  binding_sets::mousebutton<    controltype> mousebutton;
  binding_sets::scroll<         controltype> scroll;
  binding_sets::joystick_button<controltype> joystick_button;
  binding_sets::joystick_axis<  controltype> joystick_axis;

  // TODO: hoist begin:
  std::string const key_binding_default_name{                 "DEFAULT"};
  std::string const mousebutton_binding_default_name{         "DEFAULT"};
  std::string const scroll_binding_default_name{              "DEFAULT"};
  std::string const joystick_binding_default_name_xbox{       "DEFAULT XBOX"};
  std::string const joystick_binding_default_name_playstation{"DEFAULT PLAYSTATION"};
  std::string joystick_binding_default_name = joystick_binding_default_name_xbox;
  static unsigned int constexpr const num_default_binding_sets_keyboard = 1;    // counters for the above defaults - must be kept up to date
  static unsigned int constexpr const num_default_binding_sets_joystick = 2;

  std::string joystick_binding_selected_name{joystick_binding_default_name_xbox};
  // TODO: hoist end

  binding_manager(manager &input_manager);
  ~binding_manager();

  // bind and unbind functions to controls
  void bind_digital( controltype control, std::function<void()> func_press, std::function<void()> func_release = nullptr);
  void bind_analogue(controltype control, analogue_function_type func);

  void unbind_digital( controltype control);
  void unbind_analogue(controltype control);
  void unbind(         controltype control);

  // update control-based bindings
  void update_all_digital(         controltype control);
  void update_all_analogue(        controltype control);
};

template<typename T>
binding_manager<T>::binding_manager(manager &input_manager)
  : input(input_manager),
    key(            input, *this),
    mousebutton(    input, *this),
    scroll(         input, *this),
    joystick_button(input, *this),
    joystick_axis(input, *this) {
  /// Default constructor
  // TODO: hoist begin:
  key.binding_selected_name             = key_binding_default_name;
  mousebutton.binding_selected_name     = key_binding_default_name;
  scroll.binding_selected_name          = key_binding_default_name;
  joystick_button.binding_selected_name = joystick_binding_default_name;
  joystick_axis.binding_selected_name   = joystick_binding_default_name;

  key.add_binding_set(            key_binding_default_name);
  mousebutton.add_binding_set(    key_binding_default_name);
  scroll.add_binding_set(         key_binding_default_name);
  joystick_button.add_binding_set(joystick_binding_default_name_xbox);
  joystick_button.add_binding_set(joystick_binding_default_name_playstation);
  joystick_axis.add_binding_set(  joystick_binding_default_name_xbox);
  joystick_axis.add_binding_set(  joystick_binding_default_name_playstation);
  // TODO: hoist end
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
  digital_function_type func{func_press, func_release};
  action_bindings_digital[static_cast<unsigned int>(control)] = func;
  update_all_digital(control);
}
template<typename T>
void binding_manager<T>::bind_analogue(controltype control, analogue_function_type func) {
  /// Bind a function to an analogue (sliding scale) control
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
  key.update_all(            control);
  mousebutton.update_all(    control);
  scroll.update_all(         control);
  joystick_button.update_all(control);
}

template<typename T>
void binding_manager<T>::update_all_analogue(controltype control) {
  /// Set up the analogue bindings for a control with a given function
  joystick_axis.update_all(control);
}

}

#endif // INPUTSTORM_BINDING_MANAGER_H_INCLUDED
