#include "joystick_axis_bindingtype.h"
#include <iostream>

namespace inputstorm::input {

void joystick_axis_bindingtype::update_scales() {
  /// Re-cache scale values after changing deadzones or saturation values
  const float range_pos = (saturation_max - deadzone_max);
  const float range_neg = (deadzone_min - saturation_min);
  if(range_pos == 0.0f) {
    std::cout << "InputStorm: WARNING: Joystick axis binding positive saturation is the same as deadzone (" << deadzone_max << ") which would lead to infinite scale, not applying!" << std::endl;
  } else {
    scale_pos = 1.0f / range_pos;
  }
  if(range_neg == 0.0f) {
    std::cout << "InputStorm: WARNING: Joystick axis binding negative saturation is the same as deadzone (" << deadzone_min << ") which would lead to infinite scale, not applying!" << std::endl;
  } else {
    scale_neg = 1.0f / range_neg;
  }
}

float joystick_axis_bindingtype::get_transformed(float value) const {
  /// Run this value through the binding's transformation function
  float value_transformed = (value * premultiply) - centre;
  if(value_transformed >= 0.0f) {
    //std::cout << "InputStorm: DEBUG1p: value_transformed " << value_transformed << std::endl;
    value_transformed = std::max(value_transformed - deadzone_max, 0.0f);
    //std::cout << "InputStorm: DEBUG2p: value_transformed " << value_transformed << " by deadzone " << deadzone_max << std::endl;
    value_transformed *= scale_pos;
    //std::cout << "DEBUG: saturation_max = " << saturation_max << std::endl;
    //std::cout << "InputStorm: DEBUG3p: value_transformed " << value_transformed << " by scale_neg " << scale_pos << std::endl;
    //std::cout << "InputStorm: DEBUG: binding before " << value << " after " << value_transformed << " pos " << std::endl;
  } else {
    //std::cout << "InputStorm: DEBUG1n: value_transformed " << value_transformed << std::endl;
    value_transformed = std::min(value_transformed - deadzone_min, 0.0f);
    //std::cout << "InputStorm: DEBUG2n: value_transformed " << value_transformed << " by deadzone " << deadzone_min << std::endl;
    value_transformed *= scale_neg;
    //std::cout << "DEBUG: saturation_min = " << saturation_min << std::endl;
    //std::cout << "InputStorm: DEBUG3n: value_transformed " << value_transformed << " by scale_neg " << scale_neg << std::endl;
    //std::cout << "InputStorm: DEBUG: binding before " << value << " after " << value_transformed << " neg " << std::endl;
  }
  // TODO: optimise this - perhaps use integer flags and multiplication instead of the branch
  return value_transformed;
}

void joystick_axis_bindingtype::execute(float value) const {
  func(get_transformed(value));
}

void joystick_axis_bindingtype::draw_graph_console() const {
  /// produce a text representation of this binding's function's graph
  float constexpr const range_min = -1.0f;
  float constexpr const range_max =  1.0f;
  float constexpr const range = range_max - range_min;
  unsigned int constexpr const columns = 80;
  unsigned int constexpr const rows    = 20;
  float constexpr const range_scale_h  = range / static_cast<float>(columns - 1);
  float constexpr const range_offset_h = -static_cast<float>(columns / 2) * range_scale_h;
  float constexpr const range_scale_v  = range / static_cast<float>(rows - 1);
  float constexpr const range_offset_v = -static_cast<float>(rows    / 2) * range_scale_v;
  char constexpr const char_empty  = ' ';
  char constexpr const char_fill   = '#';
  char constexpr const char_axis_h = '-';
  char constexpr const char_axis_v = '|';

  // fill the bitmap background
  std::array<std::array<char, columns>, rows> bitmap;
  for(unsigned int row = 0; row != rows; ++row) {
    for(unsigned int column = 0; column != columns; ++column) {
      if(column == columns / 2) {
        bitmap[row][column] = char_axis_v;
      } else {
        if(row == 0 || row == rows / 2 || row == rows - 1) {
          bitmap[row][column] = char_axis_h;
        } else {
          bitmap[row][column] = char_empty;
        }
      }
    }
  }
  // draw a line on the bitmap from the function
  for(unsigned int column = 0; column != columns; ++column) {
    float const value = (static_cast<float>(column) * range_scale_h) + range_offset_h;
    unsigned int const row = static_cast<unsigned int>((get_transformed(value) - range_offset_v) / range_scale_v);
    bitmap[row][column] = char_fill;
  }

  // draw the thing
  //for(unsigned int column = 0; column != columns; ++column) {
  //  std::cout << '-';
  //}
  //std::cout << std::endl;
  for(int row = rows - 1; row != -1; --row) {                                   // don't make this an unsigned int for the love of god
    for(unsigned int column = 0; column != columns; ++column) {
      std::cout << bitmap[row][column];
    }
    //std::cout << std::endl;
  }
  //for(unsigned int column = 0; column != columns; ++column) {
  //  std::cout << '-';
  //}
  //std::cout << std::endl;
}

}
