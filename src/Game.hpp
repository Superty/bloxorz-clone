#pragma once

#include "globals.hpp"
#include "Graphics.hpp"
#include "IO.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace Game {
	extern Player player;
	extern Board board;
	extern bool over, won;
	extern GLuint movingObjectCount;
	void init(string levelFile);
	void update(GLfloat dt);
	void draw();
} // namespace Game
