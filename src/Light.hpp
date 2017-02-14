#pragma once

#include "globals.hpp"
#include "Graphics.hpp"
#include "Camera.hpp"

namespace Light {
	extern rgb3 color;
	extern vec3 pos;

	void init();
	void updateColor(rgb3 o_color);
	void shiftPos(vec3 o_pos);
}
