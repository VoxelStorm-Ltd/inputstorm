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
#ifndef INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
            float deadzone_max = 0.0f,
#define INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
            float saturation_min = -1.0f,

            float saturation_max = 1.0f,
#include <unordered_map>
            float centre = 0.0f);
#include "base.h"
  void bind(std::string const &binding_name,

            controltype control,
namespace inputstorm {
            input::joystick::binding_axis const &binding);
namespace binding_sets {
  void bind(controltype control,

            input::joystick::binding_axis const &binding);
#define BINDING_SET_TYPE std::unordered_multimap<T, input::joystick::binding_axis>

#define BASE_TYPE base_crtp_adapter<T, BINDING_SET_TYPE, joystick_axis>
  // update control-based bindings

template<typename T>
  virtual void update_all(controltype control) override final;
class joystick_axis : public BASE_TYPE {
};
  using controltype = T;


template<typename T>
  input::joystick &parent_joystick;
joystick_axis<T>::joystick_axis(binding_manager<controltype> &parent_binding_manager,

                                input::joystick &this_parent_joystick)
public:
  : BASE_TYPE(parent_binding_manager),
  joystick_axis(binding_manager<controltype> &parent_binding_manager,
    parent_joystick(this_parent_joystick) {
                input::joystick &this_parent_joystick);
  /// Default constructor
  virtual ~joystick_axis();
}


  // bind and unbind controls to inputs
template<typename T>
  virtual void unbind(std::string const &binding_name, controltype control) override final;
joystick_axis<T>::~joystick_axis() {
  using BASE_TYPE::unbind;                                                      // required to allow visibility of hidden overridden base type
  /// Default destructor

}
  void bind(std::string const &binding_name,

            controltype control,
//////////////////// bind and unbind controls to inputs ////////////////////////
            unsigned int joystick_id,

            unsigned int axis,
template<typename T>
            bool flip = false,
            float deadzone_min = 0.0f,
void joystick_axis<T>::unbind(std::string const &binding_name,
            float deadzone_max = 0.0f,
                              controltype control) {
            float saturation_min = -1.0f,
  /// Erase a control binding from an input joystick axis relationship
            float saturation_max = 1.0f,
  #ifdef DEBUG_INPUTSTORM
            float centre = 0.0f);
    std::cout << "InputStorm: DEBUG: Unbinding joystick axis for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
  void bind(controltype control,
  #endif // DEBUG_INPUTSTORM
            unsigned int joystick_id,
  auto &binding_set(this->binding_sets[binding_name]);
            unsigned int axis,
  binding_set.erase(control);                                                   // clear the current associations with that control
            bool flip = false,
            float deadzone_min = 0.0f,
  update_all(control);                                                          // update all joystick axes, because they're not separable into components
            float deadzone_max = 0.0f,
}
            float saturation_min = -1.0f,

            float saturation_max = 1.0f,
template<typename T>
            float centre = 0.0f);
void joystick_axis<T>::bind(std::string const &binding_name,
  void bind(std::string const &binding_name,
                            controltype control,
            controltype control,
                            unsigned int joystick_id,
            input::joystick::binding_axis const &binding);
                            unsigned int axis,
  void bind(controltype control,
                            bool flip,
            input::joystick::binding_axis const &binding);

                            float deadzone_min,
  // update control-based bindings
                            float deadzone_max,
  virtual void update_all(controltype control) override final;
                            float saturation_min,
};
                            float saturation_max,

                            float centre) {
template<typename T>
  /// Apply a new control binding to an input key relationship
joystick_axis<T>::joystick_axis(binding_manager<controltype> &parent_binding_manager,
  #ifdef DEBUG_INPUTSTORM
                                input::joystick &this_parent_joystick)
    std::cout << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
  : BASE_TYPE(parent_binding_manager),
              << " in set " << binding_name
    parent_joystick(this_parent_joystick) {
              << ", joystick " << joystick_id
  /// Default constructor
              << " axis " << axis;
}

    if(flip) {
template<typename T>
      std::cout << " (inverted)";
joystick_axis<T>::~joystick_axis() {
    }
  /// Default destructor
    std::cout << std::endl;
}
  #endif // DEBUG_INPUTSTORM

  auto &binding_set(this->binding_sets[binding_name]);
//////////////////// bind and unbind controls to inputs ////////////////////////
  binding_set.emplace(control, input::joystick::binding_axis{

    joystick_id,
template<typename T>
    axis,
void joystick_axis<T>::unbind(std::string const &binding_name,
    flip,
                              controltype control) {
    deadzone_min,
  /// Erase a control binding from an input joystick axis relationship
    deadzone_max,
  #ifdef DEBUG_INPUTSTORM
    saturation_min,
    std::cout << "InputStorm: DEBUG: Unbinding joystick axis for control " << static_cast<unsigned int>(control) << " on set " << binding_name << std::endl;
    saturation_max,
  #endif // DEBUG_INPUTSTORM
    centre
  auto &binding_set(this->binding_sets[binding_name]);
  });
  binding_set.erase(control);                                                   // clear the current associations with that control
  update_all(control);                                                          // update all joystick axes, because they're not separable into components
  update_all(control);                                                          // update all joystick axes, because they're not separable into components
}
}
template<typename T>

template<typename T>
void joystick_axis<T>::bind(controltype control,
void joystick_axis<T>::bind(std::string const &binding_name,
                            unsigned int joystick_id,
                            controltype control,
                            unsigned int axis,
                            unsigned int joystick_id,
                            bool flip,
                            unsigned int axis,
                            float deadzone_min,
                            bool flip,
                            float deadzone_max,
                            float deadzone_min,
                            float saturation_min,
                            float deadzone_max,
                            float saturation_max,
                            float saturation_min,
                            float centre) {
                            float saturation_max,
  /// Wrapper to work on the selected control set
                            float centre) {
  bind(this->binding_selected_name,
  /// Apply a new control binding to an input key relationship
       control,
  #ifdef DEBUG_INPUTSTORM
       joystick_id,
    std::cout << "InputStorm: DEBUG: Binding control " << static_cast<unsigned int>(control)
       axis,
              << " in set " << binding_name
       flip,
              << ", joystick " << joystick_id
       deadzone_min,
              << " axis " << axis;
       deadzone_max,
    if(flip) {
       saturation_min,
      std::cout << " (inverted)";
       saturation_max,
    }
       centre);
    std::cout << std::endl;
  #endif // DEBUG_INPUTSTORM
}
  auto &binding_set(this->binding_sets[binding_name]);
template<typename T>
  binding_set.emplace(control, input::joystick::binding_axis{
void joystick_axis<T>::bind(std::string const &binding_name,
    joystick_id,
                            controltype control,
    axis,
                            input::joystick::binding_axis const &binding) {
    flip,
  /// Wrapper to work on a binding
    deadzone_min,
  bind(binding_name,
    deadzone_max,
       control,
    saturation_min,
       binding.joystick_id,
    saturation_max,
       binding.axis,
    centre
       binding.flip,
  });
       binding.deadzone_min,
  update_all(control);                                                          // update all joystick axes, because they're not separable into components
       binding.deadzone_max,
}
       binding.saturation_min,
template<typename T>
       binding.saturation_max,
void joystick_axis<T>::bind(controltype control,
       binding.centre);
                            unsigned int joystick_id,
}
                            unsigned int axis,
template<typename T>
                            bool flip,
void joystick_axis<T>::bind(controltype control,
                            float deadzone_min,
                            float deadzone_max,
                            input::joystick::binding_axis const &binding) {
                            float saturation_min,
  /// Wrapper to work on a binding in the selected control set
                            float saturation_max,
  bind(control,
                            float centre) {
       binding.joystick_id,
  /// Wrapper to work on the selected control set
       binding.axis,
  bind(this->binding_selected_name,
       binding.flip,
       control,
       binding.deadzone_min,
       joystick_id,
       binding.deadzone_max,
       axis,
       binding.saturation_min,
       flip,
       binding.saturation_max,
       deadzone_min,
       binding.centre);
       deadzone_max,
}
       saturation_min,

       saturation_max,
///////////////////// update control-based bindings ////////////////////////////
       centre);

}
template<typename T>
template<typename T>
void joystick_axis<T>::update_all(controltype control) {
void joystick_axis<T>::bind(std::string const &binding_name,
  /// Update joystick axis bindings for this control
                            controltype control,
  #ifdef DEBUG_INPUTSTORM
                            input::joystick::binding_axis const &binding) {
  /// Wrapper to work on a binding
    std::cout << "InputStorm: DEBUG: Updating all joystick axis bindings for control " << static_cast<unsigned int>(control) << std::endl;
  bind(binding_name,
  #endif // DEBUG_INPUTSTORM
       control,
  auto const &binding_set(this->get_selected_binding_set());
       binding.joystick_id,
  auto const &binding_range(binding_set.equal_range(control));
       binding.axis,
  for(auto const &it : boost::make_iterator_range(binding_range.first, binding_range.second)) {
       binding.flip,
    auto const &func(this->bindings.action_bindings_analogue[static_cast<unsigned int>(control)]);
       binding.deadzone_min,
    input::joystick::binding_axis const &this_binding = it.second;
       binding.deadzone_max,
    if(func) {
       binding.saturation_min,
      #ifdef DEBUG_INPUTSTORM
       binding.saturation_max,
       binding.centre);
        std::cout << "InputStorm: DEBUG: Updating binding in set " << this->binding_selected_name
}
                                                                   << " for joystick " << this_binding.joystick_id
template<typename T>
                                                                   << " axis " << this_binding.axis << std::endl;
void joystick_axis<T>::bind(controltype control,
      #endif // DEBUG_INPUTSTORM
                            input::joystick::binding_axis const &binding) {
      parent_joystick.bind_axis(this_binding, func);
  /// Wrapper to work on a binding in the selected control set
    } else {
  bind(control,
      parent_joystick.unbind_axis(this_binding.joystick_id, this_binding.axis);
       binding.joystick_id,
    }
       binding.axis,
  }
       binding.flip,
}
       binding.deadzone_min,

       binding.deadzone_max,
#undef BINDING_SET_TYPE
       binding.saturation_min,
#undef BASE_TYPE
       binding.saturation_max,

       binding.centre);
}
}
}


///////////////////// update control-based bindings ////////////////////////////

#endif // INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
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
}

#endif // INPUTSTORM_BINDING_SETS_JOYSTICK_AXIS_H_INCLUDED
