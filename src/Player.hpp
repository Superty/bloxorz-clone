#pragma once

#include "globals.hpp"
#include "Cuboid.hpp"
#include "Tile.hpp"

enum class Orientation { Vertical, Horizontal };
enum class Status { Entering, Moving, Exiting, Static };

inline void toggleOrientation(Orientation& o) {
	if(o == Orientation::Vertical) {
		o = Orientation::Horizontal;
	}
	else {
		o = Orientation::Vertical;
	}
}

class Player {
  public:
	GLint row, col;
	Orientation orient;
	Direction dir, moveDir;
	Status status;
	GLfloat updateTime;
	Player(GLfloat curTime, GLuint o_row, GLuint o_col);
	Player();
	void update(GLfloat curTime);
	void draw();
	bool isStatic();
	void rollModelTill(GLfloat by, GLfloat till);
	void move(GLfloat curTime, Direction where);

  private:
  	Cuboid model;
	GLfloat fallSpeed;
	static constexpr GLfloat gravity = 2500.0f;
};
