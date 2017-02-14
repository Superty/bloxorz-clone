#pragma once

#include "globals.hpp"
#include "Graphics.hpp"

class Cuboid {
  public:
  	Cuboid(rgb3 o_color, vec3 o_length, vec3 o_pos, GLfloat o_yaw, GLfloat o_pitch, GLfloat o_roll);
	vec3 pos, length;
	rgb3 color;
	GLfloat yaw, pitch, roll;
	void draw();
	static void init();

  private:
	static GLuint VAO;
};
