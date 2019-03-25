#pragma once

#include "globals.hpp"
#include "Graphics.hpp"

class Player;

enum class CameraMode { Top, Tower, Helicopter, Follow, Block };

namespace Camera {
	extern CameraMode mode;
	extern vec3 pos;
	extern GLfloat radius, theta, phi;
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
	void heliShift(GLfloat offset);
	void heliShiftRotate(GLfloat delTheta, GLfloat delPhi);
	void heliFixRotate();

	void useFollowCam(Player& player);
	void useBlockCam(Player& player);
	void handlePlayerMove(Player &player);

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
