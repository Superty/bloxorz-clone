#pragma once

#include <fstream>
#include <memory>

#include "globals.hpp"

class Tile;
using TilePointer = std::unique_ptr<Tile>;
class Player;

class Board {
  public:
	static const GLint LEVEL_SIDE = 10;
	Board() = default;
	Board(string dataFile);
	void draw();
	void update(GLfloat dt);
	void activateTile(GLint row, GLint col);
	void stepOnTile(Player& player, GLint row, GLint col);
  	bool isPressedSwitch[LEVEL_SIDE][LEVEL_SIDE];
  	void reset(Player& player);
  private:
	TilePointer decodeTile(char c, GLint row, GLint col);
	Direction decodeDir(char d);
	TilePointer level[LEVEL_SIDE][LEVEL_SIDE];
};
