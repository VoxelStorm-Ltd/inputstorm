#ifndef INPUTSTORM_INPUT_SCROLL_H_INCLUDED
#define INPUTSTORM_INPUT_SCROLL_H_INCLUDED

#include <functional>
#include "vmath.h"

namespace inputstorm {
namespace input {

struct scroll {
  // data
private:
  std::function<void(Vector2d const&)> binding = [](Vector2d const &change __attribute__((__unused__))){};   // callback function for scroll

public:
  void bind(std::function<void(Vector2d const&)> func);

  void execute(Vector2d const &offset);
};

}
}

#endif // INPUTSTORM_INPUT_SCROLL_H_INCLUDED
