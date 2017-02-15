#include "IO.hpp"

namespace IO {
	bool inputEnabled;
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
		inputEnabled = true;
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
		// GLfloat slow = 0.01;
		// // Camera::shiftLookDir(slow*(xpos - cursor.x), slow*(ypos - cursor.y));
		// Camera::shiftLookDir(slow*(xpos - cursor.x), 0);
		// cursor.x = xpos;
		// cursor.y = ypos;
	}

	void scrollCallback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset) {
		// game->scrollCallback(window, xoffset, yoffset);
	}

	void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods) {
		// game->mouseButtonCallback(window, button, action, mods);
	}

	void pollKeys() {
		if(Game::movingObjectCount == 0) {
			// GLfloat curTime = glfwGetTime();
			if(glfwGetKey(Graphics::window, GLFW_KEY_W)) {
				Game::player.move(Direction::Up);
			}
			if(glfwGetKey(Graphics::window, GLFW_KEY_A)) {
				Game::player.move(Direction::Left);
			}
			if(glfwGetKey(Graphics::window, GLFW_KEY_S)) {
				Game::player.move(Direction::Down);
			}
			if(glfwGetKey(Graphics::window, GLFW_KEY_D)) {
				Game::player.move(Direction::Right);
			}
		}
		if(glfwGetKey(Graphics::window, GLFW_KEY_1)) {
			Camera::useTowerCam();
		}
		if(glfwGetKey(Graphics::window, GLFW_KEY_2)) {
			Camera::useTopCam();
		}
	}
}
