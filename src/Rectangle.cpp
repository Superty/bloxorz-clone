#include "Rectangle.hpp"
#include "Graphics.hpp"

GLuint Rectangle::VAO;

Rectangle::Rectangle(vec3 p, GLfloat w, GLfloat h):
	pos(p)
,	width(w)
,	height(h)
{  }

void Rectangle::init() {
	GLfloat vertices[] = {
		0, 0, 0,	// A
		1, 0, 0,	// B
		1, 1, 0,	// C
		1, 1, 0,	// C
		0, 1, 0,	// D
		0, 0, 0,	// A
	};
	VAO = Graphics::initSimpleVAO(6, vertices);
}

void Rectangle::draw() {
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mat4 model = translate(pos)*scale(vec3(width, height, 1));
	Graphics::useShader("hudShader");
	Graphics::activeShader.useUniform("model", model);
		
	glPolygonMode(GL_FRONT, GL_FILL);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	Graphics::useShader("litMonochrome");
}
