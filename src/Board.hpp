#pragma once

#include <fstream>
#include <memory>

#include "globals.hpp"

class Tile;
using TilePointer = std::unique_ptr<Tile>;
class Player;

class Board {
  public:
	static const GLuint LEVEL_SIDE = 10;
	Board() = default;
	Board(string dataFile);
	void draw();
	void update(GLfloat dt);
	void activateTile(GLint row, GLint col);
	void stepOnTile(Player& player, GLint row, GLint col);
  protected:
	TilePointer decodeTile(char c, GLint row, GLint col);
	Direction decodeDir(char d);
	TilePointer level[LEVEL_SIDE][LEVEL_SIDE];
};
