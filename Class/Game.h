#pragma once

//instance od FSM to handle states
#include "GameStateMachine.h"

#include <SDL2/SDL.h>
#include <vector>
#include <random>
using namespace std;

class Game
{
public:
	void Init(const char* title, int gameWidth, int gameHeight);

	void Events();
	void Update();
	void Render();
	void Clean();

	//singleton class
	static Game* Instance();

	//getters
	int getGameWidth() const { return _gameWidth; }
	int getGameHeight() const { return _gameHeight; }
	bool Quit() { return _quit; }
	SDL_Renderer* GetRenderer() const { return _renderer; }
	GameStateMachine* GetStateMachine() { return _gameStateMachine; }
	std::default_random_engine* getRandomGenerator() { return _generator; }

private:

	//singleton code
	Game() {};
	static Game* _instance;

	//SDL rendering
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	
	//Game States
	GameStateMachine* _gameStateMachine;

	//check for quitting event
	bool _quit;
	int _gameWidth, _gameHeight;

	//random generator seeded only once
	std::default_random_engine* _generator;
};


