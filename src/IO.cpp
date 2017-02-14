#include "IO.hpp"

namespace IO {
	vec2 cursor;

	void init() {
		glfwSetInputMode(Graphics::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetKeyCallback(Graphics::window, keyCallback);
		glfwSetCursorPosCallback(Graphics::window, cursorPositionCallback);
		glfwSetMouseButtonCallback(Graphics::window, mouseButtonCallback);
		glfwSetScrollCallback(Graphics::window, scrollCallback);
		GLdouble xpos, ypos;
		glfwGetCursorPos(Graphics::window, &xpos, &ypos);
		cursor.x = xpos;
		cursor.y = ypos;
	}

	void keyCallback(GLFWwindow *window, GLint key, GLint scancode, GLint action, GLint mode) {
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		// else {
		// 	game->keyCallback(key, action, mode);
		// }
	}

	void cursorPositionCallback(GLFWwindow* window, GLdouble xpos, GLdouble ypos) {
		// game->cursorPositionCallback(window, xpos, ypos);
		GLfloat slow = 0.01;
		// Camera::shiftLookDir(slow*(xpos - cursor.x), slow*(ypos - cursor.y));
		Camera::shiftLookDir(slow*(xpos - cursor.x), 0);
		cursor.x = xpos;
		cursor.y = ypos;
	}

	void scrollCallback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset) {
		// game->scrollCallback(window, xoffset, yoffset);
	}

	void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods) {
		// game->mouseButtonCallback(window, button, action, mods);
	}

	void pollKeys() {
		GLfloat curTime = glfwGetTime();
		if(glfwGetKey(Graphics::window, GLFW_KEY_W)) {
			Game::p.move(curTime, Direction::Up);
		}
		if(glfwGetKey(Graphics::window, GLFW_KEY_A)) {
			Game::p.move(curTime, Direction::Left);
		}
		if(glfwGetKey(Graphics::window, GLFW_KEY_S)) {
			Game::p.move(curTime, Direction::Down);
		}
		if(glfwGetKey(Graphics::window, GLFW_KEY_D)) {
			Game::p.move(curTime, Direction::Right);
		}
	}
}
