#pragma once

#include "globals.hpp"
#include "Graphics.hpp"

enum class CameraMode { Top, Tower };

namespace Camera {
	extern vec3 pos;
	void init();
	void updateProjection(mat4 projection);
	void useOrthoProjection();

	// void shiftLookDir(GLfloat o_yaw, GLfloat o_pitch);
	// void shiftLookFront();
	// void shiftLookBack();
	// void shiftLookLeft();
	// void shiftLookRight();
	// void shiftLookUp();
	// void shiftLookDown();

	void updateView(mat4 view);
	void useTopCam();
	void useTowerCam();
	void useHelicopterCam();



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
