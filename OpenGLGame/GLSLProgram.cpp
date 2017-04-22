#include "GLSLProgram.h"

#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath)
{
	_programID = glCreateProgram();
	if (0 == _programID) {
		FatalError("Failed to Create Program");
	}

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (0 == _vertexShaderID) {
		FatalError("Vertex Shader Failed to be Created");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (0 == _fragmentShaderID) {
		FatalError("Fragment Shader Failed to be Created");
	}
	
	CompileShader(vertexShaderFilePath, _vertexShaderID);
	CompileShader(fragmentShaderFilePath, _fragmentShaderID);


}

void GLSLProgram::LinkShaders()
{

	// Attach Shaders to Program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// Link the Program.
	glLinkProgram(_programID);

	GLuint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (GL_FALSE == isLinked) {

		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shaders failed to link!");

		return;

	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);

}

void GLSLProgram::AddAttribute(const std::string & attributeName)
{
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::Use()
{
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Unuse()
{
	glUseProgram(0);
}

void GLSLProgram::CompileShader(const std::string & filePath, GLuint& id)
{
	std::ifstream fileptr(filePath);
	if (fileptr.fail()) {
		// Not sold on this
		perror(filePath.c_str());
		FatalError("Failed to Open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(fileptr, line))
	{
		fileContents += line + "\n";
	}

	fileptr.close();

	// This is weird
	const char * contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (GL_FALSE == success) {

		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shader " + filePath + " failed to Compile");

	}

}
