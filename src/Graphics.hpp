#pragma once

#include "globals.hpp"
#include "ShaderProgram.hpp"
#include "Cuboid.hpp"

#include <map>

#include <GLFW/glfw3.h>

namespace Graphics {
	const GLfloat SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

	extern GLFWwindow* window;
	extern ShaderProgram activeShader;
	bool useShader(const string& name);
	void init();

	void drawRectangle(rgb3 color, GLfloat width, GLfloat height, vec3 position, GLfloat yaw, GLfloat pitch, GLfloat roll, vec3 internalPosition = vec3(0, 0, 0));
	void drawCuboid(rgb3 color, GLfloat length, GLfloat width, GLfloat height, vec3 position, GLfloat yaw, GLfloat pitch, GLfloat roll);
	
	void initgl();
	GLuint initVAO(GLfloat vertices[], GLfloat normals[], GLuint vertexCount);
	void initRectangleVAO();
	void initCuboidVAO();

	bool addShader(const string& name, const string& path);
}
