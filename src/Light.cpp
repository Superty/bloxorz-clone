#include "Light.hpp"

namespace Light {
	rgb3 color;
	vec3 pos(250, 200, 500);

	void init() {
		updateColor(rgb3(1, 1, 1));
		shiftPos(vec3(0, 0, 0));
	}
	
	void updateColor(rgb3 o_color) {
		color = o_color;
		Graphics::activeShader.useUniform("lightColor", color);
	}
	
	void shiftPos(vec3 dpos) {
		pos += dpos;
		Graphics::activeShader.useUniform("lightPos", pos);
	}
}
