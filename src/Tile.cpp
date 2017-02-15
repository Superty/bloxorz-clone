#include "Tile.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Game.hpp"

const rgb3
	COLOR_NORMAL	= RGB(193, 210, 223)
,	COLOR_FRAGILE	= RGB(255, 142, 000)
,	COLOR_SPECIAL	= RGB(214, 194, 165)
;

Tile::Tile(TileType o_type, rgb3 o_color, GLint o_row, GLint o_col):
	type(o_type)
,	row(o_row)
,	col(o_col)
,	model(
		o_color
	,	vec3(LENGTH, HEIGHT, LENGTH)
	,	indexToCoord(row, col, 0)
	,	radians(0.0)
	,	radians(0.0)
	,	radians(0.0)
	)
{  }

void Tile::draw() { }
void Tile::stepOn(Player& player, Board& board) { }
void Tile::activate() { }
void Tile::update(GLfloat curTime) { }

VisibleTile::VisibleTile(TileType o_type, rgb3 o_color, GLint o_row, GLint o_col):
	Tile(o_type, o_color, o_row, o_col)
{  }

void VisibleTile::draw() {
	model.draw();
}

NormalTile::NormalTile(GLint o_row, GLint o_col):
	VisibleTile(TileType::Normal, COLOR_NORMAL, o_row, o_col)
{  }

FragileTile::FragileTile(GLint o_row, GLint o_col):
	VisibleTile(TileType::Fragile, COLOR_FRAGILE, o_row, o_col)
{  }

void FragileTile::stepOn(Player& player, Board& board) {
	if(player.orient == Orientation::Vertical) {
		Game::over = true;
	}
}

EmptyTile::EmptyTile(GLint o_row, GLint o_col):
	Tile(TileType::Empty, COLOR_NORMAL, o_row, o_col)
{  }

void EmptyTile::stepOn(Player& player, Board& board) {
	Game::over = true;
}

GoalTile::GoalTile(GLint o_row, GLint o_col):
	Tile(TileType::Goal, COLOR_NORMAL, o_row, o_col)
{  }

void GoalTile::stepOn(Player& player, Board& board) {
	if(player.orient == Orientation::Vertical) {
		Game::won = true;
	}
}


BridgeTile::BridgeTile(GLint o_row, GLint o_col):
	VisibleTile(TileType::Bridge, COLOR_SPECIAL, o_row, o_col)
{  }

void BridgeTile::init(Direction o_dir, BridgeState o_state) {
	dir = o_dir;
	state = o_state;
	if(dir == Direction::Left) {
		model.set(row, col + 1, 90, 0, state == BridgeState::Expanded ? 360 : 180);
		model.pos.y = 0;
	}
	else if(dir == Direction::Right) {
		model.set(row, col, 0, 0, state == BridgeState::Expanded ? -360 : -180);
		model.pos.y = 0;
	}
	else if(dir == Direction::Up) {
		model.set(row, col, 0, state == BridgeState::Expanded ? 360 : 180, 0);
		model.pos.y = 0;
	}
	else if(dir == Direction::Down) {
		model.set(row + 1, col, -90, state == BridgeState::Expanded ? -360 : -180, 0);
		model.pos.y = 0;
	}
}

void BridgeTile::activate() {
	status = Status::Moving;
	Game::movingObjectCount++;
	state = (state == BridgeState::Expanded ?
		BridgeState::Folded : BridgeState::Expanded);
}

void BridgeTile::update(GLfloat dt) {
	if(status == Status::Moving) {
		if(dir == Direction::Left) {
			if(state == BridgeState::Expanded) {
				animateModelTill(model.roll, +30*dt, 360);
			}
			else {
				animateModelTill(model.roll, -30*dt, 180);
			}
		}
		else if(dir == Direction::Right) {
			if(state == BridgeState::Expanded) {
				animateModelTill(model.roll, -30*dt, -360);
			}
			else {
				animateModelTill(model.roll, +30*dt, -180);
			}
		}
		else if(dir == Direction::Up) {
			if(state == BridgeState::Expanded) {
				animateModelTill(model.pitch, +30*dt, 360);
			}
			else {
				animateModelTill(model.pitch, -30*dt, 180);
			}
		}
		else if(dir == Direction::Down) {
			if(state == BridgeState::Expanded) {
				animateModelTill(model.pitch, -30*dt, -360);
			}
			else {
				animateModelTill(model.pitch, +30*dt, -180);
			}
		}
	}
}

void BridgeTile::animateModelTill(GLfloat& attr, GLfloat by, GLfloat tillDegrees) {
	GLfloat till = radians(tillDegrees);
	if((attr < till) != (attr + by <= till)) {
		attr = till;
		status = Status::Static;
		Game::movingObjectCount--;
	}
	else {
		attr += by;
	}
}

void BridgeTile::stepOn(Player& player, Board& board) {
	if(state == BridgeState::Folded) {
		Game::over = true;
	}
}

SwitchTile::SwitchTile(GLint o_row, GLint o_col):
	VisibleTile(TileType::Switch, COLOR_NORMAL, o_row, o_col)
,	switchModel(
		COLOR_SPECIAL
	,	vec3(LENGTH - 2*BORDER_PADDING, SWITCH_HEIGHT, LENGTH - 2*BORDER_PADDING)
	,	indexToCoord(row, col, 0) + vec3(BORDER_PADDING, HEIGHT, BORDER_PADDING)
	,	radians(0.0)
	,	radians(0.0)
	,	radians(0.0)
	)
{  }

void SwitchTile::draw() {
	model.draw();
	switchModel.draw();
}

void SwitchTile::init(vector<pair<int,int>>&& o_bridgeList) {
	bridgeList = o_bridgeList;
}

void SwitchTile::stepOn(Player& player, Board& board) {
	for(auto bridgePos : bridgeList) {
		board.activateTile(bridgePos.first, bridgePos.second);
	}
}
