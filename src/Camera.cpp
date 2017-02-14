#include "Camera.hpp"

namespace Camera {

const GLfloat ZOOM_SPEED = 0.1, PAN_SPEED = 8, MAX_ZOOM = 4;

vec3 pos = vec3(0, 0, 300);
GLfloat zoom = 1;

GLfloat yaw = radians(-90.0), pitch = radians(0.0);
vec3 dir;

void init() {
	if(Graphics::activeShader.isValid()) {
		dir = vec3(
			rotate(pitch, vec3(0, 0, 1))
			*rotate(yaw, vec3(0, 1, 0))
			*vec4(0, 0, -1, 1)
		);
		updateProjection();
		updateView();
	}
	else {
		cerr << "error: Camera: no shader specified\n";
	}
}

void updateProjection() {
	GLfloat width = Graphics::SCREEN_WIDTH/zoom, height = Graphics::SCREEN_HEIGHT/zoom;
	Graphics::activeShader.useUniform(
		"projection",
		ortho(
			-width/2,
			width/2,
			-height/2,
			height/2,
			-1000.0f,
			+1000.0f
		)
	);
}

		// perspective(
		// 	200.0f
		// ,	GLfloat(Graphics::SCREEN_WIDTH)/Graphics::SCREEN_HEIGHT
		// ,	-10000.0f
		// ,	+10000.0f
		// )

void shiftLookDir(GLfloat dyaw, GLfloat dpitch) {
	// yaw += dyaw;
	// pitch += dpitch;
	// dir = vec3(
	// 	rotate(pitch, vec3(0, 0, 1))
	// 	*rotate(yaw, vec3(0, 1, 0))
	// 	*vec4(0, 0, -1, 1)
	// );
	// cerr << dir.x << ' ' << dir.y << ' ' << dir.z << '\n';
	// updateView();
}

// void shiftLookFront() {
// 	pos += dir;
// 	updateView();
// }

// void shiftLookBack() {
// 	pos -= dir;
// 	updateView();
// }

// void shiftLookLeft() {
// 	pos += 1.0f*vec3(
// 		rotate(yaw + radians(90.0f), vec3(0, 1, 0))
// 		*vec4(0, 0, -1, 1)
// 	);
// 	// cerr << pos.x << ' ' << pos.y << ' ' << pos.z << '\n';
// 	updateView();
// }

// void shiftLookRight() {
// 	pos += 1.0f*vec3(
// 		rotate(yaw - radians(90.0f), vec3(0, 1, 0))
// 		*vec4(0, 0, -1, 1)
// 	);
// 	updateView();
// }

GLfloat moveSpeed = 10;

void shiftLookFront() {
	pos.z += moveSpeed;
	updateView();
}

void shiftLookBack() {
	pos.z -= moveSpeed;
	updateView();
}

void shiftLookLeft() {
	pos.x -= moveSpeed;
	updateView();
}

void shiftLookRight() {
	pos.x += moveSpeed;
	updateView();
}

void shiftLookUp() {
	pos.y += moveSpeed;
	updateView();
}

void shiftLookDown() {
	pos.y -= moveSpeed;
	updateView();
}

/*
ortho(
	pos.x - width/2,
	pos.x + width/2,
	pos.y - height/2,
	pos.y + height/2,
	-1000.0f,
	+1000.0f
) */


void updateView() {
	Graphics::activeShader.useUniform(
		"view",
		// mat4(1.0)
		// lookAt(
		// 	pos
		// ,	pos + dir
		// ,	vec3(0, 1, 0)
		// )
		lookAt(
			pos
		,	pos + vec3(-1, -1, -0.5)
		,	vec3(0, 1, 0)
		)
	);
}

// translate(pos)
// *rotate(pitch, vec3(0, 0, 1))
// *rotate(yaw, vec3(0, 1, 0))
// *vec4(0, 0, -1, 1)

// void clipPos() {
// 	GLfloat width = Graphics::SCREEN_WIDTH/zoom, height = Graphics::SCREEN_HEIGHT/zoom;

// 	if(pos.x - width/2 < 0) pos.x = width/2;
// 	else if(pos.x + width/2 > Graphics::SCREEN_WIDTH) pos.x = Graphics::SCREEN_WIDTH - width/2;

// 	if(pos.y - height/2 < 0) pos.y = height/2;
// 	else if(pos.y + height/2 > Graphics::SCREEN_HEIGHT) pos.y = Graphics::SCREEN_HEIGHT - height/2;
// }
// void setShift(vec3 shift) {
// 	pos = base + (shift/zoom);
// 	clipPos();
// }
// void resetShift() {
// 	base = pos;
// }
// void zoomIn() {
// 	zoom += ZOOM_SPEED;
// 	if(zoom > MAX_ZOOM) {
// 		zoom = MAX_ZOOM;
// 	}
// 	clipPos();
// }
// void zoomOut() {
// 	zoom -= ZOOM_SPEED;
// 	if(zoom < 1) {
// 		zoom = 1;
// 	}
// 	clipPos();
// }
// void panLeft() {
// 	pos.x -= PAN_SPEED/zoom;
// 	clipPos();
// }
// void panRight() {
// 	pos.x += PAN_SPEED/zoom;
// 	clipPos();
// }
// void panDown() {
// 	pos.y -= PAN_SPEED/zoom;
// 	clipPos();
// }
// void panUp() {
// 	pos.y += PAN_SPEED/zoom;
// 	clipPos();
// }
// vec3 gameCords(GLfloat windowPosX, GLfloat windowPosY) {
// 	vec3 res;
// 	res.x = windowPosX;
// 	res.y = Graphics::SCREEN_HEIGHT - windowPosY;

// 	res.x -= Graphics::SCREEN_WIDTH/2;
// 	res.y -= Graphics::SCREEN_HEIGHT/2;

// 	res.x = res.x/zoom + pos.x;
// 	res.y = res.y/zoom + pos.y;

// 	return vec3(res.x, res.y, 0);
// }

// mat4 getVP() {
// 	GLfloat width = Graphics::SCREEN_WIDTH/zoom, height = Graphics::SCREEN_HEIGHT/zoom;

// 	return ortho(
// 		pos.x - width/2,
// 		pos.x + width/2,
// 		pos.y - height/2,
// 		pos.y + height/2,
// 		0.0f,
// 		500.0f
// 	);
// }

} // namespace Camera