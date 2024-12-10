#pragma once

#include <functional>

namespace inputstorm::input {

class text {
  std::function<void(char32_t)> binding = [](char32_t codepoint [[maybe_unused]]){}; // callback function for UTF32 text input

public:
  void bind(std::function<void(char32_t)> func);

  void unbind();

  void execute(char32_t codepoint) const;
};

}
