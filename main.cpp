#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

#include "src/globals.hpp"
#include "src/Graphics.hpp"
#include "src/Camera.hpp"
#include "src/Light.hpp"
#include "src/IO.hpp"
#include "src/Cuboid.hpp"
#include "src/Game.hpp"

// void error_callback(int error, const char* description) {
// 	fprintf(stderr, "error %d: %s\n", error, description);
// }

void quit(GLFWwindow *window) {
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void init() {
	Graphics::init();
	IO::init();
	Camera::init();
	Light::init();
	srand(glfwGetTime());
}

int main() {
	init();

	// vec4 v = vec4(1, 0, 0, 1);
	// mat4 m = rotate(radians(90.0f), vec3(0, 1, 0));
	// cerr << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << '\n';
	// vec4 r = m*v;
	// cerr << r.x << ' ' << r.y << ' ' << r.z << ' ' << r.w << '\n';
	// v = *v;
	// cerr << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << '\n';
	
	// Graphics::drawCuboid(rgb3(0, 0, 1), 50, -100, 50, vec3(0, 0, 0), radians(0.0), radians(0.0), radians(30*curTime));	
	// Cuboid ground(rgb3(1, 0, 0), vec3(500, 10, 500), vec3(-300, 0, 50), radians(0.0), radians(0.0), radians(0.0));
	Cuboid test(rgb3(1, 0, 0), vec3(50, 10, 50), vec3(0, 0, 50), radians(0.0), radians(0.0), radians(0.0));
	GLfloat curTime = glfwGetTime();
	// Player p(curTime, 9, 9);
	// NormalTile tile(2, 2);

	// tile.model = test;
	Game::init("level.txt");
	GLint seconds = 0;
	while (!glfwWindowShouldClose(Graphics::window)) {
		glfwPollEvents();
		IO::pollKeys();
		GLfloat delTime = glfwGetTime() - curTime;
		curTime += delTime;
		GLint curSecs = GLint(curTime);
		if(curSecs != seconds) {
			seconds = curSecs;
			GLint minutes = seconds / 60;
			cerr << "Time: ";
			if (minutes < 10) cerr << '0';
			cerr << minutes << ':';
			if (seconds < 10) cerr << '0';
			cerr << seconds << '\n';
		}

		// game->pollKeys(Graphics::window, curTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		Game::update(delTime);
		Game::draw();
		// test.draw();
		// tile.draw();
		// Game::player.draw();
		// Game::board.draw();
		// Graphics::drawCuboid(, 500, 10, 500, , );
		// Graphics::drawCuboid(rgb3(1, 0, 0), 50, 10, 50, vec3(-50, 0, 0), radians(0.0), radians(0.0), radians(90.0));
		// Graphics::drawCuboid(rgb3(1, 0, 0), 50, 10, 50, vec3(0, 0, -50), radians(0.0), radians(0.0), radians(90.0));
		// Graphics::drawCuboid(rgb3(0, 1, 0), 50, 10, 50, vec3(-50, 0, -50), radians(0.0), radians(0.0), radians(90.0));
		// Graphics::drawCuboid(rgb3(0, 1, 0), 50, 10, 50, vec3(50, 0, 0), radians(0.0), radians(0.0), radians(90.0));
		// Graphics::drawCuboid(rgb3(0, 1, 0), 50, 10, 50, vec3(50, 0, 50), radians(0.0), radians(0.0), radians(90.0));
		// Graphics::drawCuboid(rgb3(0, 0, 1), 50, -100, 50, vec3(0, 0, 0), radians(0.0), radians(0.0), radians(30*curTime));
		
		// Camera::setLook(curTime, 0);

		// Graphics::drawRectangle(rgb3(1, 0, 0), 100, 200, vec3(400, 400, 100), radians(30*curTime), radians(0.0), radians(45.0));
		// Graphics::drawCuboid(rgb3(1, 0, 0), 100, 200, 100, vec3(500, 500, 100), radians(90.0), radians(0.0), radians(0.0));
		// Graphics::drawRectangle(rgb3(0, 0, 0), 10, 10, vec3(400, 300, 100), 0, radians(0.0), radians(0.0));
		// game->update(curTime);
		// game->draw();

		// GLfloat dist = 50*delTime;
		// Light::shiftPos(vec3(dist, 0, -dist));

		glfwSwapBuffers(Graphics::window);
	}

	quit(Graphics::window);
}
