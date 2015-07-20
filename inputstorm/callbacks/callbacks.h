#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace inputstorm {

void key(         GLFWwindow *thiswindow, int key, int scancode, int action, int mods);
void cursor(      GLFWwindow *thiswindow, double x, double y);
void cursor_enter(GLFWwindow *thiswindow, int entered);
void mousebutton( GLFWwindow *thiswindow, int button, int action, int mods);
void scroll(      GLFWwindow *thiswindow, double xoffset, double yoffset);

}

#endif // CALLBACKS_H_INCLUDED
