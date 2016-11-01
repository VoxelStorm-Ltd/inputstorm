#ifndef INPUTSTORM_INPUT_TEXT_H_INCLUDED
#define INPUTSTORM_INPUT_TEXT_H_INCLUDED

#include <functional>

namespace inputstorm {
namespace input {

class text {
  std::function<void(char32_t)> binding = [](char32_t codepoint __attribute__((__unused__))){}; // callback function for UTF32 text input

public:
  void bind(std::function<void(char32_t)> func);

  void unbind();

  void execute(char32_t codepoint) const;
};

}
}

#endif // INPUTSTORM_INPUT_TEXT_H_INCLUDED
