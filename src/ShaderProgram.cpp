#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const string& vertShaderPath, const string& fragShaderPath) {
	GLuint vertexShader = makeShader(GL_VERTEX_SHADER, vertShaderPath);
	if(!vertexShader) {
		id = 0;
		return;
	}
	GLuint fragmentShader = makeShader(GL_FRAGMENT_SHADER, fragShaderPath);
	if(!fragmentShader) {
		id = 0;
		return;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);

	int linkSuccess;
	glGetProgramiv(id, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess) {
		GLchar infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		cerr << "error: shader program linking failed.\n" << infoLog << "\n";
		id = 0;
		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// for(auto uniformName: uniformList) {
	// 	uniformLocation[uniformName] = getUniformLocation(uniformName);
	// }
	// transformLocation = getUniformLocation("transform");
	// inColorLocation = getUniformLocation("inColor");
}

void ShaderProgram::use() {
	glUseProgram(id);
}

bool ShaderProgram::isValid() {
	return (id != 0);
}

// ShaderProgram::operator int() {
// 	return id;
// }

ShaderProgram::ShaderProgram() {
	id = 0;
}

string ShaderProgram::loadFile(const string& path) {
	std::ifstream fileStream(path);
	string fileContents = "";
	if(fileStream) {
		string line;
		while (getline(fileStream, line)) {
			fileContents += line + "\n";
		}
		fileStream.close();
	}
	else {
		cerr << "error: could not read " << path << ": " << strerror(errno);
	}
	return fileContents;
}

GLuint ShaderProgram::makeShader(GLenum shaderType, const string& path) {
	string shaderCode = loadFile(path);
	GLchar const * shaderCodePointer = shaderCode.c_str();
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCodePointer, NULL);
	glCompileShader(shader);
	GLint shaderCompilationSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompilationSuccess);
	if (!shaderCompilationSuccess) {
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cerr << "error: " << path << ": shader compilation failed.\n" << infoLog << "\n";
		cerr << "code is as follows:\n" << shaderCode << "\n";
		return 0;
	}
	return shader;
}

GLuint ShaderProgram::getUniformLocation(const string& uniformName) {
	GLuint location = glGetUniformLocation(id, uniformName.c_str());
	if(location == GLuint(-1)) {
		cerr << uniformName << " location not found.\n";
		exit(EXIT_FAILURE);
	}
	return location;
}

void ShaderProgram::useUniform(const string& uniformName, const mat4& uniformValue) {
	glUniformMatrix4fv(
		getUniformLocation(uniformName),
		1,
		GL_FALSE,
		&uniformValue[0][0]
	);
}

void ShaderProgram::useUniform(const string& uniformName, const vec4& uniformValue) {
	glUniform4fv(
		getUniformLocation(uniformName),
		1,
		&uniformValue[0]
	);
}

void ShaderProgram::useUniform(const string& uniformName, const vec3& uniformValue) {
	glUniform3fv(
		getUniformLocation(uniformName),
		1,
		&uniformValue[0]
	);
}
