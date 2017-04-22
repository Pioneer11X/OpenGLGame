#pragma once
#include "MainGame.h"

#include <string>

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

	int glVersionMajor;
	int glVersionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);
	printf("\n=== OpenGL Implementation ===\n");
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("GL Version: %s\n", glGetString(GL_VERSION));
	printf("GL Version (Strict): %d.%d\n", glVersionMajor, glVersionMinor);
	printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	InitShaders();

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

	_colorProgram.Use();

	_sprite.Draw();

	_colorProgram.Unuse();

	SDL_GL_SwapWindow(_window);

}

void MainGame::Run()
{

	InitSystems();

	_sprite.Init(-1.0f, -1.0f, 1.0f, 1.0f);

	GameLoop();

}

void MainGame::InitShaders()
{

	_colorProgram.CompileShaders("Shaders/ColorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.AddAttribute("vertexPosition");
	_colorProgram.LinkShaders();

}

