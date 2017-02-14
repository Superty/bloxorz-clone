#pragma once

#include "globals.hpp"
#include "Graphics.hpp"

namespace Camera {
	extern vec3 pos;
	void init();
	void updateProjection();
	void shiftLookDir(GLfloat o_yaw, GLfloat o_pitch);
	void shiftLookFront();
	void shiftLookBack();
	void shiftLookLeft();
	void shiftLookRight();
	void shiftLookUp();
	void shiftLookDown();

	void updateView();
	// mat4 getVP();
	// void clipPos();
	// void setShift(vec3 newPos);
	// void resetShift();
	// void zoomIn();
	// void zoomOut();
	// void panLeft();
	// void panRight();
	// void panDown();
	// void panUp();
	// vec3 gameCords(GLfloat xpos, GLfloat ypos);
}
