#pragma once
#include "MainGame.h"

#include <string>

void FatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	exit(1);
}

MainGame::MainGame()
{
	_window = nullptr;

	_screenWidth = 1024;
	_screenHeight = 768;

	_gameState = GameState::PLAY;

}


MainGame::~MainGame()
{
	if (nullptr != _window) {
		SDL_DestroyWindow(_window);
	}
}

void MainGame::InitSystems()
{
	// Initialise SDL.
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("Open GL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (nullptr == _window) {
		FatalError("SDL Window could not be created!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (nullptr == glContext) {
		FatalError("SDL_GL context could not be created!");
	}

	glewExperimental = true;
	GLenum error = glewInit();
	if (GLEW_OK != error) {
		FatalError("Could not Init Glew");
	}

	// Use Double Swappable Buffer. Prevents the Flickering when updating.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Set the Background Color.
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

}

void MainGame::ProcessInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
		}
	}
}

void MainGame::GameLoop()
{
	while (GameState::EXIT != _gameState)
	{
		ProcessInput();
	}
}

void MainGame::DrawGame()
{

	// Clear to the depth passed.
	glClearDepth(1.0);

	// Clear the Color Buffer and the Depth Buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	_sprite.Draw();

	SDL_GL_SwapWindow(_window);

}

void MainGame::Run()
{

	InitSystems();

	_sprite.Init(-1.0f, -1.0f, 1.0f, 1.0f);

	GameLoop();

}

