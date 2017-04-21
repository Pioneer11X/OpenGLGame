#pragma once
#include "MainGame.h"

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
			break;
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

void MainGame::Run()
{

	InitSystems();

	GameLoop();

}
