#ifndef INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
#define INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED

#include <unordered_map>
#include "base.h"

namespace inputstorm::binding_sets {

#define BINDING_SET_TYPE std::unordered_multimap<T, input::joystick::binding_axis>
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, joystick_axis>

template<typename T>
class joystick_axis : public BASE_TYPE {
  using controltype = T;

  input::joystick &parent_joystick;

public:
  joystick_axis(binding_manager<controltype> &parent_binding_manager,
                input::joystick &this_parent_joystick);
  virtual ~joystick_axis();

  // bind and unbind controls to inputs
  virtual void unbind(std::string const &binding_name, controltype control) override final;
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type

  void bind(std::string const &binding_name,
            controltype control,
            unsigned int joystick_id,
            unsigned int axis,
            bool flip = false,
            float deadzone_min = 0.0f,
            float deadzone_max = 0.0f,
            float saturation_min = -1.0f,
            float saturation_max = 1.0f,
            float centre = 0.0f);
  void bind(controltype control,
            unsigned int joystick_id,
            unsigned int axis,
            bool flip = false,
            float deadzone_min = 0.0f,
            float deadzone_max = 0.0f,
            float saturation_min = -1.0f,
            float saturation_max = 1.0f,
            float centre = 0.0f);
  void bind(std::string const &binding_name,
            controltype control,
            input::joystick::binding_axis const &binding);
  void bind(controltype control,
            input::joystick::binding_axis const &binding);

  // update control-based bindings
  virtual void update_all(controltype control) override final;
};

template<typename T>
joystick_axis<T>::joystick_axis(binding_manager<controltype> &parent_binding_manager,
                                input::joystick &this_parent_joystick)
  : BASE_TYPE(parent_binding_manager),
    parent_joystick(this_parent_joystick) {
  /// Default constructor
}

template<typename T>
joystick_axis<T>::~joystick_axis() {
  /// Default destructor
}

//////////////////// bind and unbind controls to inputs ////////////////////////

template<typename T>
void joystick_axis<T>::unbind(std::string const &binding_name,
                              controltype control) {
  /// Erase a control binding from an input joystick axis relationship
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Unbinding joystick axis for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto &binding_set(this->binding_sets[binding_name]);
  binding_set.erase(control);                                                   // clear the current associations with that control
  update_all(control);                                                          // update all joystick axes, because they're not separable into components
}

template<typename T>
void joystick_axis<T>::bind(std::string const &binding_name,
                            controltype control,
                            unsigned int joystick_id,
                            unsigned int axis,
                            bool flip,
                            float deadzone_min,
                            float deadzone_max,
                            float saturation_min,
                            float saturation_max,
                            float centre) {
  /// Apply a new control binding to an input key relationship
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
              << " in set " << binding_name
              << ", joystick " << joystick_id
              << " axis " << axis;
    if(flip) {
      std::cout << " (inverted)";
    }
    std::cout << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto &binding_set(this->binding_sets[binding_name]);
  binding_set.emplace(control, input::joystick::binding_axis{
    joystick_id,
    axis,
    flip,
    deadzone_min,
    deadzone_max,
    saturation_min,
    saturation_max,
    centre
  });
  update_all(control);                                                          // update all joystick axes, because they're not separable into components
}
template<typename T>
void joystick_axis<T>::bind(controltype control,
                            unsigned int joystick_id,
                            unsigned int axis,
                            bool flip,
                            float deadzone_min,
                            float deadzone_max,
                            float saturation_min,
                            float saturation_max,
                            float centre) {
  /// Wrapper to work on the selected control set
  bind(this->binding_selected_name,
       control,
       joystick_id,
       axis,
       flip,
       deadzone_min,
       deadzone_max,
       saturation_min,
       saturation_max,
       centre);
}
template<typename T>
void joystick_axis<T>::bind(std::string const &binding_name,
                            controltype control,
                            input::joystick::binding_axis const &binding) {
  /// Wrapper to work on a binding
  bind(binding_name,
       control,
       binding.joystick_id,
       binding.axis,
       binding.flip,
       binding.deadzone_min,
       binding.deadzone_max,
       binding.saturation_min,
       binding.saturation_max,
       binding.centre);
}
template<typename T>
void joystick_axis<T>::bind(controltype control,
                            input::joystick::binding_axis const &binding) {
  /// Wrapper to work on a binding in the selected control set
  bind(control,
       binding.joystick_id,
       binding.axis,
       binding.flip,
       binding.deadzone_min,
       binding.deadzone_max,
       binding.saturation_min,
       binding.saturation_max,
       binding.centre);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void joystick_axis<T>::update_all(controltype control) {
  /// Update joystick axis bindings for this control
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Updating all joystick axis bindings for control " << static_cast<unsigned int>(control) << std::endl;
  #endif // DEBUG_INPUTSTORM
  auto const &binding_set(this->get_selected_binding_set());
  auto const &binding_range(binding_set.equal_range(control));
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
    auto const &func(this->bindings.action_bindings_analogue[static_cast<unsigned int>(control)]);
    input::joystick::binding_axis const &this_binding = it.second;
    if(func) {
      #ifdef DEBUG_INPUTSTORM
        std::cout << "InputStorm: DEBUG: Updating binding in set " << this->binding_selected_name
                                                                   << " for joystick " << this_binding.joystick_id
                                                                   << " axis " << this_binding.axis << std::endl;
      #endif // DEBUG_INPUTSTORM
      parent_joystick.bind_axis(this_binding, func);
    } else {
      parent_joystick.unbind_axis(this_binding.joystick_id, this_binding.axis);
    }
  }
}

#undef BINDING_SET_TYPE
#undef BASE_TYPE

}

#endif // INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
