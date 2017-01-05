#ifndef CALLBACKS_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace inputstorm {
namespace callback {

void key(             GLFWwindow *thiswindow, int key, int scancode, int action, int mods);
void cursor(          GLFWwindow *thiswindow, double x, double y);
void cursor_enter(    GLFWwindow *thiswindow, int entered);
void mousebutton(     GLFWwindow *thiswindow, int button, int action, int mods);
void scroll(          GLFWwindow *thiswindow, double xoffset, double yoffset);
void text(            GLFWwindow *thiswindow, unsigned int codepoint);
void window_position( GLFWwindow *thiswindow, int xpos, int ypos);
void window_size(     GLFWwindow *thiswindow, int width, int height);
void window_close(    GLFWwindow *thiswindow);
void window_refresh(  GLFWwindow *thiswindow);
void window_focus(    GLFWwindow *thiswindow, int focused);
void window_iconify(  GLFWwindow *thiswindow, int iconified);
void framebuffer_size(GLFWwindow *thiswindow, int width, int height);

}
}

#endif // CALLBACKS_H_INCLUDED
