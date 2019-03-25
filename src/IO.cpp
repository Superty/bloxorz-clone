#include "IO.hpp"

namespace IO {
	bool rightPressed;
	vec2 cursor;

	void init() {
		rightPressed = false;
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
		// GLfloat slow = 0.01;
		// // Camera::shiftLookDir(slow*(xpos - cursor.x), slow*(ypos - cursor.y));
		// Camera::shiftLookDir(slow*(xpos - cursor.x), 0);
		// cursor.x = xpos;
		// cursor.y = ypos;
		if(rightPressed) {
			Camera::heliShiftRotate(xpos - cursor.x, ypos - cursor.y);
		}
	}

	void scrollCallback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset) {
		Camera::heliShift(-50*yoffset);
		// game->scrollCallback(window, xoffset, yoffset);
	}

	void mouseButtonCallback(GLFWwindow* window, GLint button, GLint action, GLint mods) {
		// game->mouseButtonCallback(window, button, action, mods);
		if(button == GLFW_MOUSE_BUTTON_RIGHT) {
			if(action == GLFW_PRESS) {
				rightPressed = true;
				double xpos, ypos;
				glfwGetCursorPos(Graphics::window, &xpos, &ypos);
				cursor.x = xpos;
				cursor.y = ypos;
			}
			else if(action == GLFW_RELEASE) {
				rightPressed = false;
				Camera::heliFixRotate();
			}
		}
	}

	void pollKeys() {
		// cerr << Game::movingObjectCount << '\n';
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
		if(glfwGetKey(Graphics::window, GLFW_KEY_3)) {
			Camera::useHelicopterCam();
		}
		if(glfwGetKey(Graphics::window, GLFW_KEY_4)) {
			Camera::useFollowCam(Game::player);
		}
		if(glfwGetKey(Graphics::window, GLFW_KEY_5)) {
			Camera::useBlockCam(Game::player);
		}

	}
}
