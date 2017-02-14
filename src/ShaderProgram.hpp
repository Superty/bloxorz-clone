#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

#include "globals.hpp"

class ShaderProgram {
public:
	ShaderProgram(const std::string& vertShaderPath, const std::string& fragShaderPath);
	ShaderProgram();
	void use();
	// operator int();
	bool isValid();
	void useUniform(const std::string& uniformName, const mat4& uniformValue);
	void useUniform(const std::string& uniformName, const vec4& uniformValue);
	void useUniform(const std::string& uniformName, const vec3& uniformValue);

private:
	GLuint id;
	static std::string loadFile(const std::string& path);
	static GLuint makeShader(GLenum shaderType, const std::string& path);
	GLuint getUniformLocation(const std::string& uniformName);
};
