#ifndef INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
#define INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED

#include "base.h"

namespace inputstorm {
namespace binding_sets {

#define BINDING_SET_TYPE std::unordered_multimap<T, input::joystick::binding_axis>
#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, joystick_axis>

template<typename T>
class joystick_axis : public BASE_TYPE {
  using controltype = T;

public:
  joystick_axis(manager &input_manager, binding_manager<T> &parent_binding_manager);
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

  // update control-based bindings
  virtual void update_all(controltype control) override final;
};

template<typename T>
joystick_axis<T>::joystick_axis(manager &input_manager,
                                binding_manager<controltype> &parent_binding_manager)
  : BASE_TYPE(input_manager, parent_binding_manager) {
  /// Default constructor
}

template<typename T>
joystick_axis<T>::~joystick_axis() {
  /// Default destructor
}

//////////////////// bind and unbind controls to inputs ////////////////////////

template<typename T>
void joystick_axis<T>::unbind(std::string const &binding_name, controltype control) {
  /// Erase a control binding from an input joystick axis relationship
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
  #ifdef DEBUG_INPUTSTORM
    std::cout << "InputStorm: DEBUG: Binding control " << get_name(control) <<  " in set " << binding_selected_name << ", joystick " << joystick_id << " axis " << axis;
    if(flip) {
      std::cout << " (inverted)";
    }
    std::cout << std::endl;
  #endif // DEBUG_INPUTSTORM
  bind(this->binding_selected_name, control, joystick_id, axis, flip, deadzone_min, deadzone_max, saturation_min, saturation_max, centre);
}

///////////////////// update control-based bindings ////////////////////////////

template<typename T>
void joystick_axis<T>::update_all(controltype control) {
  /// Update joystick axis bindings for this control
  auto const &binding_set(this->get_selected_binding_set());
  auto const &binding_range(binding_set.equal_range(control));
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
    auto const &func(this->bindings.action_bindings_analogue[static_cast<unsigned int>(control)]);
    input::joystick::binding_axis const &this_binding = it.second;
    if(func) {
      this->input.joystick.bind_axis(this_binding, func);
    } else {
      this->input.joystick.unbind_axis(this_binding.joystick_id, this_binding.axis);
    }
  }
}

#undef BINDING_SET_TYPE
#undef BASE_TYPE

}
}


#endif // INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
