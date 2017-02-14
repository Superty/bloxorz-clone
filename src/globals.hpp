#pragma once

#include <iostream>
#include <cmath>
#include <glad/glad.h>

using std::string;
using std::cerr;

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

const GLfloat EPS = 1e-5;

inline bool isZero(GLfloat x) {
	return (-EPS < x && x < +EPS);
}

inline bool areEqual(GLfloat x, GLfloat y) {
	return isZero(x - y);
}

inline GLfloat distance(vec2 p, vec2 q) {
	return sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
}

inline GLfloat principalAngle(GLfloat angle) {
	if(angle < 0) return angle + 2*M_PI;
	else if(angle > 2*M_PI) return angle - 2*M_PI;
	else return angle;
}

using rgb4 = vec4;
using rgb3 = vec3;

enum class Direction { Up, Down, Left, Right };

inline vec3 indexToCoord(GLint r, GLint c, GLfloat y = 0) {
	return vec3(-300 + 50*r, y, 50 + 50*c);
}

inline rgb3 COLOR(GLfloat r, GLfloat g, GLfloat b) {
	return rgb3(r/255.0, g/255.0, b/255.0);
}
