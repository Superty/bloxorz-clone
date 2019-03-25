#pragma once

#include "globals.hpp"
#include "Cuboid.hpp"
#include "Tile.hpp"

enum class Orientation { Vertical, Horizontal };

inline void toggleOrientation(Orientation& o) {
	if(o == Orientation::Vertical) {
		o = Orientation::Horizontal;
	}
	else {
		o = Orientation::Vertical;
	}
}

class Board;

class Player {
  public:
	GLuint stepCount;
	GLint row, col;
	Orientation orient;
	Direction dir, moveDir;
	Status status;
	Player(GLint o_row, GLint o_col);
	Player();
	bool update(GLfloat dt, Board& board);
	void draw();
	bool isStatic();
	void animateModelTill(Board& board, GLfloat& attr, GLfloat by, GLfloat till);
	void move(Direction where);
	GLint dirGroup(Direction d);
	void stepOnCoveredTiles(Board& board);
	void fall();

  private:
  	Cuboid model;
	GLfloat fallSpeed;
	static constexpr GLfloat gravity = 2500.0f;
};
