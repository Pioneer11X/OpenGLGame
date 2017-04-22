#pragma once

#include <string>
#include <GL\glew.h>
#include "Errors.h"

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

	void LinkShaders();

	void AddAttribute(const std::string& attributeName);

	void Use();
	void Unuse();

private:

	int _numAttributes;

	void CompileShader(const std::string& filePath, GLuint& id);

	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

