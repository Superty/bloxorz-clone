#include "Game.hpp"

namespace Game {
	Player p;
	void init(GLfloat curTime) {
		p = Player(curTime, 9, 9);
	}
} // namespace Game