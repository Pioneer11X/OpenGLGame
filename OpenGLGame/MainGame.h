#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <iostream>
#include "Sprite.h"
#include "Errors.h"
#include "GLSLProgram.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	
	void Run();

private:

	void InitShaders();

	SDL_Window* _window;

	int _screenWidth;
	int _screenHeight;

	GameState _gameState;

	Sprite _sprite;

	void InitSystems();
	void ProcessInput();
	void GameLoop();
	void DrawGame();

	GLSLProgram _colorProgram;

};

