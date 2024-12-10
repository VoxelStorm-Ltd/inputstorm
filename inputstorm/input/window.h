#pragma once

#include <functional>
#include "vectorstorm/vector/vector2_forward.h"

namespace inputstorm::input {

class window {
private:
  std::function<void(vec2i const&)> position_binding         = [](vec2i const &change [[maybe_unused]]){}; // window position change
  std::function<void(vec2i const&)> resize_binding           = [](vec2i const &change [[maybe_unused]]){}; // window size change
  std::function<void(vec2i const&)> framebuffer_size_binding = [](vec2i const &change [[maybe_unused]]){}; // framebuffer size change
  std::function<void()>             close_binding            = []{};            // window close attempt
  std::function<void()>             refresh_binding          = []{};            // window refresh request
  std::function<void()>             focus_gain_binding       = []{};            // window gains focus
  std::function<void()>             focus_lose_binding       = []{};            // window loses focus
  std::function<void()>             minimise_binding         = []{};            // window is minimised
  std::function<void()>             restore_binding          = []{};            // window is restored from being minimised

public:
  void bind_position(        std::function<void(vec2i const&)> func);
  void bind_resize(          std::function<void(vec2i const&)> func);
  void bind_framebuffer_size(std::function<void(vec2i const&)> func);
  void bind_close(           std::function<void()> func);
  void bind_refresh(         std::function<void()> func);
  void bind_focus_gain(      std::function<void()> func);
  void bind_focus_lose(      std::function<void()> func);
  void bind_minimise(        std::function<void()> func);
  void bind_restore(         std::function<void()> func);

  void unbind_position();
  void unbind_resize();
  void unbind_framebuffer_size();
  void unbind_close();
  void unbind_refresh();
  void unbind_focus_gain();
  void unbind_focus_lose();
  void unbind_minimise();
  void unbind_restore();

  void execute_position(        vec2i const &new_position) const;
  void execute_resize(          vec2i const &new_position) const;
  void execute_framebuffer_size(vec2i const &new_position) const;
  void execute_close()                                     const;
  void execute_refresh()                                   const;
  void execute_focus_gain()                                const;
  void execute_focus_lose()                                const;
  void execute_minimise()                                  const;
  void execute_restore()                                   const;
};

}
