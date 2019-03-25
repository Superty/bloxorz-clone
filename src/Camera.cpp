#include "Camera.hpp"
#include "Player.hpp"

namespace Camera {

CameraMode mode;
vec3 dir;

// helicopter
GLfloat radius, theta, phi;
GLfloat baseTheta, basePhi;

void init() {
	if(Graphics::activeShader.isValid()) {
		radius = 400;
		baseTheta = theta = 0;
		basePhi = phi = 89.9;
		useOrthoProjection();
		useTowerCam();
	}
	else {
		cerr << "error: Camera: no shader specified\n";
	}
}

void useOrthoProjection() {
	updateProjection(
		ortho(
			-Graphics::SCREEN_WIDTH/2,
			Graphics::SCREEN_WIDTH/2,
			-Graphics::SCREEN_HEIGHT/2,
			Graphics::SCREEN_HEIGHT/2,
			-1000.0f,
			+1000.0f
		)
	);
}

void usePerspectiveProjection(GLfloat fov = 90.0f) {
	updateProjection(
		perspective(
			radians(90.0f)
		,	Graphics::SCREEN_WIDTH/Graphics::SCREEN_HEIGHT
		,	0.2f
		,	1000.0f
		)
	);
}

void updateProjection(mat4 projection) {
	Graphics::activeShader.useUniform(
		"projection",
		projection
	);
}

void useTowerCam() {
	mode = CameraMode::Tower;
	useOrthoProjection();
	vec3 _pos(0, 0, 300);
	updateView(
		lookAt(
			_pos
		,	_pos + vec3(-1, -1, -0.5)
		,	vec3(0, 1, 0)
		)
	);
}

void useTopCam() {
	mode = CameraMode::Top;
	useOrthoProjection();
	vec3 _pos(-50, 0, 300);
	updateView(
		lookAt(
			_pos
		,	_pos + vec3(0, -1, 0)
		,	vec3(-1, 0, 0)
		)
	);
}

void useHelicopterCam() {
	mode = CameraMode::Helicopter;
	usePerspectiveProjection();
	vec3 _pos = radius*vec3(
		cos(radians(phi))*cos(radians(theta))
	,	sin(radians(phi))
	,	cos(radians(phi))*sin(radians(theta))
	);
	// pos = indexToCoord(0, 0, 0);
	vec3 centre = vec3(-50, 0, 300);
	updateView(
		// mat4(1.0f)
		lookAt(
			centre + _pos
		,	centre
		// ,	pos + vec3(0, -1, 0)
		,	vec3(0, 1, 0)
		)
	);
}

void heliShift(GLfloat offset) {
	if(mode == CameraMode::Helicopter) {
		radius += offset;
		if(radius < 100) {
			radius = 100;
		}
		if(radius > 1000) {
			radius = 1000;
		}
		Camera::useHelicopterCam();
	}
}

void heliShiftRotate(GLfloat delTheta, GLfloat delPhi) {
	if(mode == CameraMode::Helicopter) {
		// cerr << delTheta << ' ' << delPhi << '\n';
		theta = baseTheta + delTheta;
		phi = basePhi + delPhi;
		if(phi >= 89.9) {
			phi = 89.9;
		}
		else if(phi <= 10.0) {
			phi = 10.0;
		}
		Camera::useHelicopterCam();
	}
}

void heliFixRotate() {
	baseTheta = theta;
	basePhi = phi;
}

// follow
Status status = Status::Static;
vec3 speed;
GLint row, col;
vec3 speedTheta;
GLfloat followTheta, maxTheta;


void useFollowCam(Player& player) {
	mode = CameraMode::Follow;
	usePerspectiveProjection();
	vec3 _dir, _pos;
	if(player.moveDir == Direction::Up) {
		_dir = vec3(-1, -1, 0);
		_pos = indexToMid(player.row + 2, player.col, 200);
	}
	else if(player.moveDir == Direction::Down) {
		_dir = vec3(1, -1, 0);
		_pos = indexToMid(player.row - 2, player.col, 200);
	}
	else if(player.moveDir == Direction::Left) {
		_dir = vec3(0, -1, 1);
		_pos = indexToMid(player.row, player.col - 2, 200);
	}
	else {
		_dir = vec3(0, -1, -1);
		_pos = indexToMid(player.row, player.col + 2, 200);
	}
	updateView(
		lookAt(
			_pos
		,	_pos + _dir
		,	vec3(0, 1, 0)
		)
	);
}

void update(GLfloat dt) {
	if(status == Status::Moving) {
		
	}
}

void updateView(mat4 view) {
	Graphics::activeShader.useUniform(
		"view",
		// mat4(1.0)
		// lookAt(
		// 	pos
		// ,	pos + dir
		// ,	vec3(0, 1, 0)
		// )
		view
	);
}

void handlePlayerMove(Player &player) {
	if(mode == CameraMode::Follow) {
		useFollowCam(player);
	}
	else if(mode == CameraMode::Block) {
		useBlockCam(player);
	}
}

void useBlockCam(Player& player) {
	mode = CameraMode::Block;
	usePerspectiveProjection(120.0);
	vec3 _dir, _pos;
	if(player.moveDir == Direction::Up) {
		_dir = vec3(-1, -1, 0);
	}
	else if(player.moveDir == Direction::Down) {
		_dir = vec3(1, -1, 0);
	}
	else if(player.moveDir == Direction::Left) {
		_dir = vec3(0, -1, 1);
	}
	else {
		_dir = vec3(0, -1, -1);
	}
	_pos = indexToMid(player.row, player.col, 100);
	if(player.orient == Orientation::Vertical) {
		_pos += 25.0f*_dir;
	}
	else {
		_pos += 75.0f*_dir;
	}
	updateView(
		lookAt(
			_pos
		,	_pos + _dir
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