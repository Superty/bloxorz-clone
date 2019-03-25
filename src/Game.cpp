#include "Game.hpp"
#include "Board.hpp"

namespace Game {
	const vec3 SCORE_POS = vec3(0, 0, 0);
	Player player;
	Board board;
	bool over, won;
	GLuint movingObjectCount;
	void init(string levelFile) {
		player = Player(9, 9);
		over = false;
		won = false;
		board = Board(levelFile);
		movingObjectCount = 0;
	}
	void end(bool& setTrue) {
		setTrue = true;
		player.fall();
		board.reset(player);
	}
	void update(GLfloat dt) {
		if(over) {
			cerr << "YOU DIED!\n";
			over = false;
		}
		else if(won) {
			cerr << "YOU WON!\n";
			won = false;
		}
		else {
			if(!player.update(dt, board)) {
				player = Player(9, 9);
				movingObjectCount = 0;
			}
			board.update(dt);
		}
	}
	void draw() {
		player.draw();
		board.draw();
	}
} // namespace Game
