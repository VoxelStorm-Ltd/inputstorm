#ifndef INPUTSTORM_INPUT_JOYSTICK_AXIS_BINDINGTYPE_H_INCLUDED
#define INPUTSTORM_INPUT_JOYSTICK_AXIS_BINDINGTYPE_H_INCLUDED

#include <functional>

namespace inputstorm::input {

struct joystick_axis_bindingtype {
  float deadzone_min   =  0.0f;                                                 // values within this range are clamped to zero
  float deadzone_max   =  0.0f;
  float saturation_min = -1.0f;                                                 // values beyond this range are clamped to one
  float saturation_max =  1.0f;
  float centre         =  0.0f;
  float premultiply    =  1.0f;                                                 // premultiply, including an axis flip if appropriate
  float scale_pos = saturation_max - deadzone_max;                              // cached scale values - output values are scaled to fill the above range
  float scale_neg = deadzone_min - saturation_min;
  std::function<void(float)> func = [](float value [[maybe_unused]]){};         // the function to call

  bool enabled = false;                                                         // whether to try this axis' function

  void update_scales();

  float get_transformed(float value) const __attribute__((__pure__));

  void execute(float value) const;

  void draw_graph_console() const;
};

}

#endif // INPUTSTORM_INPUT_JOYSTICK_AXIS_BINDINGTYPE_H_INCLUDED
