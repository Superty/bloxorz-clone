#pragma once

#include "globals.hpp"
#include "Graphics.hpp"
#include "IO.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Player.hpp"

namespace Game {
	extern Player p;
	void init(GLfloat curTime);
} // namespace Game
