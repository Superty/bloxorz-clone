#pragma once

#include "globals.hpp"

class Rectangle {
  public:
  	Rectangle(vec3 p, GLfloat w, GLfloat h);
  	static void init();
  	void draw();

  	vec3 pos;
  	GLfloat width, height;
  private:
  	static GLuint VAO;
};
