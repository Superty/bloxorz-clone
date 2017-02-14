#pragma once

#include "globals.hpp"
#include "Graphics.hpp"

enum class TileType { Normal, Fragile, Bridge, Switch, Empty };

class Tile {
  public:
	Tile(TileType o_type);
	void draw(int row, int col);
	TileType type;
	static constexpr GLfloat
		SIDE_LENGTH = 50
	,	NORMAL_HEIGHT = 10
	,	BRIDGE_HEIGHT = 7
	;

 //  private:
	// static const rgb3
	// 	COLOR_NORMAL	= COLOR(193, 210, 223)
	// ,	COLOR_FRAGILE	= COLOR(255, 142, 000)
	// ,	COLOR_SPECIAL	= COLOR(214, 194, 165)
	// ;
};
