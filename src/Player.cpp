#include "Player.hpp"

Player::Player(GLfloat curTime, GLuint o_row, GLuint o_col):
	row(o_row)
,	col(o_col)
,	orient(Orientation::Vertical)
,	dir(Direction::Up)
,	status(Status::Entering)
,	updateTime(curTime)
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
{  }

void Player::update(GLfloat curTime) {
	GLfloat dt = curTime - updateTime;
	updateTime = curTime;

	if(status == Status::Entering) {
		model.pos.y -= dt * fallSpeed + gravity*dt*dt/2;
		fallSpeed += dt * gravity;
		if(model.pos.y < Tile::NORMAL_HEIGHT) {
			model.pos.y = Tile::NORMAL_HEIGHT;
			status = Status::Static;
		}
	}
	else if(status == Status::Moving) {
		if(orient == Orientation::Horizontal) {
			if(moveDir == Direction::Left) {
				rollModelTill(10*dt, 90);
				// model.roll += 10*dt;
				// if(model.roll >= radians(90.0)) {
				// 	model.roll = radians(90.0);
				// 	status = Status::Static;
				// }
			}
			else if(moveDir == Direction::Right) {
				rollModelTill(-10*dt, -90);
				// model.roll -= 10*dt;
				// if(model.roll <= radians(-90.0)) {
				// 	model.roll = radians(-90.0);
				// 	status = Status::Static;
				// }
			}
		}
		else if(orient == Orientation::Vertical) {
			if(moveDir == Direction::Left) {
				rollModelTill(10*dt, 0);
				// model.roll += 10*dt;
				// if(model.roll >= radians(0.0)) {
				// 	model.roll = radians(0.0);
				// 	status = Status::Static;
				// }
			}
			else if(moveDir == Direction::Right) {
				rollModelTill(-10*dt, 0);
				// model.roll -= 10*dt;
				// if(model.roll <= radians(0.0)) {
				// 	model.roll = radians(0.0);
				// 	status = Status::Static;
				// }
			}
		}
	}
}

void Player::rollModelTill(GLfloat by, GLfloat tillDegrees) {
	GLfloat till = radians(tillDegrees);
	if((model.roll < till) != (model.roll + by <= till)) {
		model.roll = till;
		status = Status::Static;	
	}
	else {
		model.roll += by;
	}
}

bool Player::isStatic() {
	return status == Status::Static;
}

void Player::draw() {
	model.draw();
}

void Player::move(GLfloat curTime, Direction where) {
	if(isStatic()) {
		if(orient == Orientation::Vertical) {
			if(where == Direction::Left) {
				col++;
				model.yaw = radians(90.0);
				model.pitch = radians(0.0);
				model.roll = radians(0.0);
				model.pos = indexToCoord(row, col, Tile::NORMAL_HEIGHT);
			}
			else if(where == Direction::Right) {
				col--;
				model.pitch = radians(0.0);
				model.yaw = radians(0.0);
				model.roll = radians(0.0);
				model.pos = indexToCoord(row, col + 1, Tile::NORMAL_HEIGHT);	
			}
			else if(where == Direction::Up) {
				row--;
			}
			else if(where == Direction::Down) {
				row++;
			}
			dir = where;
			orient = Orientation::Horizontal;
		}
		else if(orient == Orientation::Horizontal) {
			if(where == Direction::Left) {
				col++;
				if(dir == Direction::Left) {
					col++;
				}
				model.pitch = radians(0.0);
				model.yaw = radians(0.0);
				model.roll = radians(-90.0);
				model.pos = indexToCoord(row, col, Tile::NORMAL_HEIGHT);	
			}
			else if(where == Direction::Right) {
				col--;
				if(dir == Direction::Right) {
					col--;
				}
				model.yaw = radians(90.0);
				model.pitch = radians(0.0);
				model.roll = radians(90.0);
				model.pos = indexToCoord(row, col + 1, Tile::NORMAL_HEIGHT);
			}
			else if(where == Direction::Up) {
				row--;
			}
			else if(where == Direction::Down) {
				row++;
			}
			orient = Orientation::Vertical;
		}
		updateTime = curTime;
		moveDir = where;
		status = Status::Moving;
	}
}
