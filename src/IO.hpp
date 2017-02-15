#pragma once

#include "globals.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include <GLFW/glfw3.h>

namespace IO {
	extern bool inputEnabled;
	void init();
	void keyCallback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mode);
	void cursorPositionCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos);
	void scrollCallback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset);
	void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods);
	void pollKeys();
}
