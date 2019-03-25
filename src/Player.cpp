#include "Player.hpp"
#include "Board.hpp"
#include "Game.hpp"

Player::Player(GLint o_row, GLint o_col):
	stepCount(0)
,	row(o_row)
,	col(o_col)
,	orient(Orientation::Vertical)
,	dir(Direction::Up)
,	status(Status::Entering)
,	model(
		rgb3(0, 0, 1)
	,	vec3(50, 100, 50)
	,	indexToCoord(row, col, 700)
	,	radians(0.0)
	,	radians(0.0)
	,	radians(0.0)
	)
,	fallSpeed(500.0f)
{  }

Player::Player():
	model(
		rgb3(0, 0, 1)
	,	vec3(50, 100, 50)
	,	indexToCoord(0, 0, 700)
	,	radians(0.0)
	,	radians(0.0)
	,	radians(0.0)
	)
{}

void Player::fall() {
	status = Status::Exiting;
	Game::movingObjectCount++;
}

void Player::stepOnCoveredTiles(Board& board) {
	if(!isStatic()) {
		return;
	}
	
	board.stepOnTile(*this, row, col);
	if(orient == Orientation::Horizontal) {
		if(dir == Direction::Left) {
			board.stepOnTile(*this, row, col + 1);
		}
		else if(dir == Direction::Right) {
			board.stepOnTile(*this, row, col - 1);
		}
		else if(dir == Direction::Up) {
			board.stepOnTile(*this, row - 1, col);
		}
		else if(dir == Direction::Down) {
			board.stepOnTile(*this, row + 1, col);
		}
	}
}

bool Player::update(GLfloat dt, Board& board) {
	if(status == Status::Entering) {
		model.pos.y -= dt * fallSpeed + gravity*dt*dt/2;
		fallSpeed += dt * gravity;
		if(model.pos.y < Tile::HEIGHT) {
			model.pos.y = Tile::HEIGHT;
			status = Status::Static;
		}
		Camera::handlePlayerMove(*this);
	}
	else if(status == Status::Exiting) {
		model.pos.y -= dt * fallSpeed + gravity*dt*dt/2;
		fallSpeed += dt * gravity;
		if(model.pos.y < -1000) {
			Game::movingObjectCount--;
			return false;
		}
	}
	else if(status == Status::Moving) {
		if(orient == Orientation::Horizontal) {
			if(dirGroup(dir) == dirGroup(moveDir)) {
				if(moveDir == Direction::Left) {
					animateModelTill(board, model.roll, 10*dt, 90);
				}
				else if(moveDir == Direction::Right) {
					animateModelTill(board, model.roll, -10*dt, -90);
				}
				else if(moveDir == Direction::Up) {
					animateModelTill(board, model.pitch, 10*dt, 90);
				}
				else if(moveDir == Direction::Down) {
					animateModelTill(board, model.pitch, -10*dt, -90);
				}
			}
			else {
				if(moveDir == Direction::Left) {
					animateModelTill(board, model.yaw, -10*dt, 0);
				}
				else if(moveDir == Direction::Right) {
					animateModelTill(board, model.yaw, 10*dt, 90);
				}
				else if(moveDir == Direction::Up) {
					animateModelTill(board, model.yaw, -10*dt, -90);
				}
				else if(moveDir == Direction::Down) {
					animateModelTill(board, model.yaw, 10*dt, 0);
				}
			}
		}
		else if(orient == Orientation::Vertical) {
			if(moveDir == Direction::Right) {
				animateModelTill(board, model.roll, -10*dt, 0);
			}
			else if(moveDir == Direction::Left) {
				animateModelTill(board, model.roll, 10*dt, 0);
			}
			else if(moveDir == Direction::Down) {
				animateModelTill(board, model.pitch, -10*dt, 0);
			}
			else if(moveDir == Direction::Up) {
				animateModelTill(board, model.pitch, 10*dt, 0);
			}
		}
	}
	return true;
}

void Player::animateModelTill(Board& board, GLfloat& attr, GLfloat by, GLfloat tillDegrees) {
	GLfloat till = radians(tillDegrees);
	if((attr < till) != (attr + by <= till)) {
		attr = till;
		status = Status::Static;
		stepOnCoveredTiles(board);
		Game::movingObjectCount--;
	}
	else {
		attr += by;
	}
}

// void Player::setModel(GLint drawRow, GLint drawCol, GLfloat yawDeg, GLfloat pitchDeg, GLfloat rollDeg) {
// 	model.pos = indexToCoord(drawRow, drawCol, Tile::HEIGHT);
// 	model.yaw = radians(yawDeg);
// 	model.pitch = radians(pitchDeg);
// 	model.roll = radians(rollDeg);
// }

bool Player::isStatic() {
	return status == Status::Static;
}

void Player::draw() {
	model.draw();
}

GLint Player::dirGroup(Direction d) {
	return (d == Direction::Left || d == Direction::Right);
}

void Player::move(Direction where) {
	if(!isStatic()) {
		return;
	}
	stepCount++;
	cerr << "Step Count: " << stepCount << '\n';
	if(orient == Orientation::Vertical) {
		if(where == Direction::Left) {
			col++;
			model.set(row, col, 90, 0, 0);
		}
		else if(where == Direction::Right) {
			col--;
			model.set(row, col + 1, 0, 0, 0);
		}
		else if(where == Direction::Up) {
			row--;
			model.set(row + 1, col, 0, 0, 0);
		}
		else if(where == Direction::Down) {
			row++;
			model.set(row, col, -90, 0, 0);
		}
		dir = where;
		orient = Orientation::Horizontal;
	}
	else if(orient == Orientation::Horizontal) {
		if(dirGroup(dir) == dirGroup(where)) {
			if(where == Direction::Left) {
				if(dir == where) col += 2;
				else col++;
				model.set(row, col, 0, 0, -90);
			}
			else if(where == Direction::Right) {
				if(dir == where) col -= 2;
				else col--;
				model.set(row, col + 1, 90, 0, 90);
			}
			else if(where == Direction::Up) {
				if(dir == where) row -= 2;
				else row--;
				model.set(row + 1, col, -90, -90, 0);
			}
			else if(where == Direction::Down) {
				if(dir == where) row += 2;
				else row++;
				model.set(row, col, 0, 90, 0);
			}
			orient = Orientation::Vertical;
		}
		else {
			if(where == Direction::Left) {
				col++;
				if(dir == Direction::Up) model.set(row + 1, col, 90, 90, 0);
				if(dir == Direction::Down) model.set(row + 2, col, 90, 90, 0);
			}
			else if(where == Direction::Right) {
				col--;
				if(dir == Direction::Up) model.set(row + 1, col + 1, 0, 90, 0);
				if(dir == Direction::Down) model.set(row + 2, col + 1, 0, 90, 0);
			}
			else if(where == Direction::Up) {
				row--;
				if(dir == Direction::Right) model.set(row + 1, col + 1, 0, 0, -90);
				if(dir == Direction::Left) model.set(row + 1, col + 2, 0, 0, -90);
			}
			else if(where == Direction::Down) {
				row++;
				if(dir == Direction::Right) model.set(row, col + 1, -90, 0, -90);
				if(dir == Direction::Left) model.set(row, col + 2, -90, 0, -90);
			}
		}
	}
	moveDir = where;
	status = Status::Moving;
	Game::movingObjectCount++;
	Camera::handlePlayerMove(*this);
}
