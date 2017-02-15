#include "Cuboid.hpp"
#include "Tile.hpp"

GLuint Cuboid::VAO;

Cuboid::Cuboid(rgb3 o_color, vec3 o_length, vec3 o_pos, GLfloat o_yaw, GLfloat o_pitch, GLfloat o_roll):
	pos(o_pos)
,	length(o_length)
,	color(o_color)
,	yaw(o_yaw)
,	pitch(o_pitch)
,	roll(o_roll)
{  }

void Cuboid::set(GLint drawRow, GLint drawCol, GLfloat yawDeg, GLfloat pitchDeg, GLfloat rollDeg) {
	pos = indexToCoord(drawRow, drawCol, Tile::HEIGHT);
	yaw = radians(yawDeg);
	pitch = radians(pitchDeg);
	roll = radians(rollDeg);
}

void Cuboid::draw() {
	if(Graphics::activeShader.isValid()) {
		Graphics::activeShader.useUniform("objectColor", color);
		Graphics::activeShader.useUniform("model",
			translate(pos)
			*rotate(roll, vec3(1, 0, 0))
			*rotate(pitch, vec3(0, 0, 1))
			*rotate(yaw, vec3(0, 1, 0))
			*scale(length)
		);
		
		glPolygonMode(GL_FRONT, GL_FILL);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
	else {
		cerr << "error: no shader activated.\n";
	}
}

void Cuboid::init() {
	GLfloat vertices[] = {
		// back
		0, 0, 0,
		1, 0, 0,
		1, 1, 0,
		1, 1, 0,
		0, 1, 0,
		0, 0, 0,
		// front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		1, 1, 1,
		0, 1, 1,
		0, 0, 1,
		// left
		0, 0, 0,
		0, 1, 0,
		0, 1, 1,
		0, 1, 1,
		0, 0, 1,
		0, 0, 0,
		// right
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
		1, 1, 1,
		1, 0, 1,
		1, 0, 0,
		// bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		1, 0, 1,
		0, 0, 1,
		0, 0, 0,
		// top
		0, 1, 0,
		1, 1, 0,
		1, 1, 1,
		1, 1, 1,
		0, 1, 1,
		0, 1, 0,
	};
	GLfloat normals[] = {
		// back
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		// front
		0, 0, +1,
		0, 0, +1,
		0, 0, +1,
		0, 0, +1,
		0, 0, +1,
		0, 0, +1,
		// left
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		// right
		+1, 0, 0,
		+1, 0, 0,
		+1, 0, 0,
		+1, 0, 0,
		+1, 0, 0,
		+1, 0, 0,
		// bottom
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		// top
		0, +1, 0,
		0, +1, 0,
		0, +1, 0,
		0, +1, 0,
		0, +1, 0,
		0, +1, 0,
	};
	VAO = Graphics::initVAO(vertices, normals, 36);
}