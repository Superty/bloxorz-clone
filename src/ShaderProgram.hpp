#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

#include "globals.hpp"

class ShaderProgram {
public:
	ShaderProgram(const string& vertShaderPath, const string& fragShaderPath);
	ShaderProgram();
	void use();
	// operator int();
	bool isValid();
	void useUniform(const string& uniformName, const mat4& uniformValue);
	void useUniform(const string& uniformName, const vec4& uniformValue);
	void useUniform(const string& uniformName, const vec3& uniformValue);

private:
	GLuint id;
	static string loadFile(const string& path);
	static GLuint makeShader(GLenum shaderType, const string& path);
	GLuint getUniformLocation(const string& uniformName);
};
