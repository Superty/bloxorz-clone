#include "Game.hpp"

namespace Game {
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
	void update(GLfloat dt) {
		if(over) {
			cerr << "GAME OVER!\n";
			exit(EXIT_SUCCESS);
		}
		else if(won) {
			cerr << "YOU WON!\n";
			exit(EXIT_SUCCESS);
		}
		else {
			player.update(dt, board);
			board.update(dt);
		}
	}
	void draw() {
		player.draw();
		board.draw();
	}
} // namespace Game
