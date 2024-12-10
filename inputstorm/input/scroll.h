#pragma once

#include <functional>
#include "vectorstorm/vector/vector2.h"

namespace inputstorm::input {

class scroll {
public:
  // types
  enum class direction : char {
    RIGHT,
    BEGIN = RIGHT,
    LEFT,
    UP,
    DOWN,
    END,
    LAST = END - 1
  };

  // data
private:
  std::function<void(vec2d const&)> binding = [](vec2d const &change [[maybe_unused]]){}; // callback function for scroll

public:
  static std::string get_name(direction this_direction);

  void bind(std::function<void(vec2d const&)> func);

  void unbind();

  void execute(vec2d const &offset) const;

  void capture(std::function<void(direction)> callback);
};

/// Helper functions to allow scroll::direction to be iterated
inline scroll::direction operator++(scroll::direction &i) {
  return i = static_cast<scroll::direction>(std::underlying_type<scroll::direction>::type(i) + 1);
}
inline scroll::direction operator*(scroll::direction c) {
  return c;
}
inline scroll::direction begin(scroll::direction thistype [[maybe_unused]]) {
  return scroll::direction::BEGIN;
}
inline scroll::direction end(scroll::direction thistype [[maybe_unused]]) {
  return scroll::direction::END;
}

}
