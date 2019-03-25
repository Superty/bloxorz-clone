#pragma once

#include "globals.hpp"
#include "Graphics.hpp"
#include "IO.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Player.hpp"

class Player;

namespace Game {
	extern Player player;
	extern Board board;
	extern bool over, won;
	extern GLuint movingObjectCount;
	void init(string levelFile);
	void update(GLfloat dt);
	void draw();
	void end(bool& setTrue);
} // namespace Game
