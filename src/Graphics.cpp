#include "Graphics.hpp"

namespace Graphics {

GLFWwindow* window;
GLuint rectangleVAO, cuboidVAO;

void error_callback(int error, const char* description) {
	fprintf(stderr, "error %d: %s\n", error, description);
}

void init() {
	initgl();

	if(!addShader("litMonochrome", "src/litMonochrome")) {
		exit(EXIT_FAILURE);
	}
	else if(!useShader("litMonochrome")) {
		exit(EXIT_FAILURE);
	}
	
	Cuboid::init();
	initRectangleVAO();
}

void initgl() {
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL 3.3", nullptr, nullptr);

	if (window == nullptr) {
		cerr << "error: failed to create GLFW window.\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthFunc(GL_LEQUAL);
	glClearColor(0.5, 0.5, 0.5, 1.0f); // sky blue
	// glClearColor(135/255.0, 205/255.0, 235/255.0, 1.0f); // sky blue
	glLineWidth(3.0f);
}

std::map<string,ShaderProgram> shaderList;
ShaderProgram activeShader;

bool addShader(const string& name, const string& path) {
	ShaderProgram shader(path + ".vert", path + ".frag");
	if(shader.isValid()) {
		shaderList[name] = shader;
		return true;
	}
	else {
		return false;
	}
}

bool useShader(const string& name) {
	if(shaderList.count(name)) {
		shaderList[name].use();
		activeShader = shaderList[name];
		return true;
	}
	else {
		return false;
	}
}

void initRectangleVAO() {
	GLfloat vertices[] = {
		0, 0, 0,	// A
		1, 0, 0,	// B
		1, 1, 0,	// C
		1, 1, 0,	// C
		0, 1, 0,	// D
		0, 0, 0,	// A
	};
	GLfloat normals[] = {
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1
	};
	rectangleVAO = initVAO(vertices, normals, 6);
}

GLuint initVAO(GLfloat vertices[], GLfloat normals[], GLuint vertexCount) {
	GLuint vertexVBO, normalVBO, VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, 3*vertexCount*sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, 3*vertexCount*sizeof(GLfloat), normals, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	return VAO;
}

void drawRectangle(rgb3 color, GLfloat width, GLfloat height, vec3 position, GLfloat yaw, GLfloat pitch, GLfloat roll, vec3 internalPosition) {
	if(activeShader.isValid()) {
		activeShader.useUniform("objectColor", color);
		activeShader.useUniform("model",
			translate(position)
			*rotate(roll, vec3(1, 0, 0))
			*rotate(pitch, vec3(0, 0, 1))
			*rotate(yaw, vec3(0, 1, 0))
			*translate(internalPosition)
			*scale(vec3(width, height, 1))
		);

		glPolygonMode(GL_FRONT, GL_FILL);
		glBindVertexArray(rectangleVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	else {
		cerr << "error: no shader activated.\n";
	}
}

void drawCuboid(rgb3 color, GLfloat length, GLfloat width, GLfloat height, vec3 position, GLfloat yaw, GLfloat pitch, GLfloat roll) {
	if(activeShader.isValid()) {
		activeShader.useUniform("objectColor", color);
		activeShader.useUniform("model",
			translate(position)
			*rotate(roll, vec3(1, 0, 0))
			*rotate(pitch, vec3(0, 0, 1))
			*rotate(yaw, vec3(0, 1, 0))
			*scale(vec3(length, height, width))
		);

		glPolygonMode(GL_FRONT, GL_FILL);
		glBindVertexArray(cuboidVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
	else {
		cerr << "error: no shader activated.\n";
	}
}

// void drawCuboid(rgb3 color, GLfloat length, GLfloat breadth, GLfloat height, vec3 position, GLfloat yaw, GLfloat pitch, GLfloat roll) {
// 	// drawRectangle(color, length, height, position, yaw + radians(180.0), pitch, roll, vec3(-length, 0, 0));
// 	// drawRectangle(color, breadth, height, position, yaw + radians(90.0), pitch, roll, vec3(0, 0, 0));
// 	// drawRectangle(color, breadth, height, position, yaw + radians(-90.0), pitch, roll, vec3(length, breadth, 0));
// 	// drawRectangle(color, length, height, position, yaw + radians(180.0), pitch, roll, vec3(-length, 0, 0));
// 	// drawRectangle(rgb3(0, 1, 0), breadth, height, position, yaw + radians(90.0), pitch, roll);
// 	// drawRectangle(color, -length, -height, position, yaw, pitch, roll, vec3(0, 0, breadth));

// 	if(activeShader.isValid()) {
// 		activeShader.useUniform("objectColor", color);
// 		activeShader.useUniform("model",
// 			translate(position)
// 			*rotate(roll, vec3(1, 0, 0))
// 			*rotate(pitch, vec3(0, 0, 1))
// 			*rotate(yaw, vec3(0, 1, 0))
// 			*scale(vec3(length, height, breadth))
// 		);

// 		glPolygonMode(GL_FRONT, GL_FILL);
// 		glBindVertexArray(cuboidVAO);
// 		glDrawArrays(GL_TRIANGLES, 0, 6);
// 		glBindVertexArray(0);
// 	}
// 	else {
// 		cerr << "error: no shader activated.\n";
// 	}
// }

} // namespace Graphics

/*
0, 0
1, 0
1, 1
0, 1


*/