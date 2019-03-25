#include "Board.hpp"
#include "Tile.hpp"
#include "Game.hpp"

TilePointer Board::decodeTile(char c, GLint row, GLint col) {
		 if(c == 'N') 		return TilePointer(new NormalTile(row, col));
	else if(c == 'F')	return TilePointer(new FragileTile(row, col));
	else if(c == 'B') 	return TilePointer(new BridgeTile(row, col));
	else if(c == 'S') 	return TilePointer(new SwitchTile(row, col));
	else if(c == 'G')	return TilePointer(new GoalTile(row, col));
	else 				return TilePointer(new EmptyTile(row, col));
}

Direction Board::decodeDir(char d) {
		 if(d == 'U') return Direction::Up;
	else if(d == 'D') return Direction::Down;
	else if(d == 'L') return Direction::Left;
	else if(d == 'R') return Direction::Right;
	else {
		cerr << "fatal: invalid direction " << d << "\n";
		exit(EXIT_FAILURE);
	}
}

Board::Board(string dataFile) {
	std::ifstream dataStream(dataFile);
	string input;
	for(GLuint i = 0; i < LEVEL_SIDE; i++) {
		dataStream >> input;
		for(GLuint j = 0; j < LEVEL_SIDE; j++) {
			level[i][j] = decodeTile(input[LEVEL_SIDE - j - 1], i, j);
			isPressedSwitch[i][j] = false;
			// cerr << input[j] << ;
		}
		// cerr << '\n';
	}
	GLint row, col;
	while(dataStream >> row >> col) {
		// cerr << row << ' ' << col << ' ';
		col = LEVEL_SIDE - col - 1;
		if(level[row][col]->type == TileType::Bridge) {
			// cerr << "bridge\n";
			char dir, state;
			dataStream >> dir >> state;
			BridgeTile& tile = dynamic_cast<BridgeTile&>(*level[row][col]);
			tile.init(decodeDir(dir), (state == 'E' ? BridgeState::Expanded : BridgeState::Folded));
		}
		else if(level[row][col]->type == TileType::Switch) {
			// cerr << "switch\n";
			GLuint bridgeCount;
			dataStream >> bridgeCount;
			vector<pair<int,int>> bridgeList;
			while(bridgeCount--) {
				GLuint bridgeRow, bridgeCol;
				dataStream >> bridgeRow >> bridgeCol;
				bridgeList.emplace_back(bridgeRow, LEVEL_SIDE - 1 - bridgeCol);
			}
			SwitchTile& tile = dynamic_cast<SwitchTile&>(*level[row][col]);
			tile.init(std::move(bridgeList));
		}
	}
}

void Board::draw() {
	for(GLuint i = 0; i < LEVEL_SIDE; i++) {
		for(GLuint j = 0; j < LEVEL_SIDE; j++) {
			level[i][j]->draw();
		}
	}
}

void Board::update(GLfloat dt) {
	for(GLuint i = 0; i < LEVEL_SIDE; i++) {
		for(GLuint j = 0; j < LEVEL_SIDE; j++) {
			level[i][j]->update(dt);
		}
	}
}

void Board::activateTile(GLint row, GLint col) {
	level[row][col]->activate();
}

void Board::stepOnTile(Player& player, GLint row, GLint col) {
	if(row < 0 || col < 0 || row >= LEVEL_SIDE || col >= LEVEL_SIDE) {
		Game::end(Game::over);
	}
	else {
		level[row][col]->stepOn(player, *this);
	}
}

void Board::reset(Player& player) {
	for(GLuint i = 0; i < LEVEL_SIDE; i++) {
		for(GLuint j = 0; j < LEVEL_SIDE; j++) {
			if(isPressedSwitch[i][j]) {
				stepOnTile(player, i, j);
			}
		}
	}
}