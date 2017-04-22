#pragma once
#include <GL\glew.h>

class Sprite
{

public:
	Sprite();
	~Sprite();


	void Init(int x, int y, int width, int height);
	void Draw();


private:
	int _x;
	int _y;
	int _width;
	int _height;

	GLuint _vboID;

};

