#ifndef INPUTSTORM_INPUT_SCROLL_H_INCLUDED
#define INPUTSTORM_INPUT_SCROLL_H_INCLUDED

#include <functional>
#include "vectorstorm/vector/vector2.h"

namespace inputstorm {
namespace input {

struct scroll {
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
  std::function<void(vec2d const&)> binding = [](vec2d const &change __attribute__((__unused__))){}; // callback function for scroll

public:
  std::string get_name(direction this_direction) const;

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
inline scroll::direction begin(scroll::direction thistype __attribute__((__unused__))) {
  return scroll::direction::BEGIN;
}
inline scroll::direction end(scroll::direction thistype __attribute__((__unused__))) {
  return scroll::direction::END;
}

}
}

#endif // INPUTSTORM_INPUT_SCROLL_H_INCLUDED
