#include "Sprite.h"



Sprite::Sprite()
{
	// Setting this to invalid(null) vbo
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (0 != _vboID) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::Init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_width = width;
	_height = height;

	if (0 == _vboID) {
		// 0 indicates no buffer.
		glGenBuffers(1, &_vboID);
	}

	float vertexData[12] = {
		// First triangle
		x + width,
		y + height,

		x,
		y + height,

		x,
		y,

		// Second Triangle
		x,
		y,

		x + width,
		y,

		x + width,
		y + height

	};

	// Bind this buffer.
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	// Pass the Data on to the buffer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Unbind the buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::Draw()
{

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
