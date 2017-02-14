#include "Tile.hpp"

Tile::Tile(TileType o_type):
	type(o_type)
{  }

void Tile::draw(int row, int col) {
	// if(type != TileType.Empty) {
	// 	Graphics::drawCuboid(
	// 		(type == TileType.Fragile) ? COLOR_FRAGILE : COLOR_NORMAL
	// 	,	TILE_SIDE
	// 	,	TILE_HEIGHT
	// 	,	TILE_SIDE
	// 	,	indexToPosition(row, col)
	// 	,	radians(0.0)
	// 	,	radians(0.0)
	// 	,	radians(90.0)
	// 	);
	// }
}
