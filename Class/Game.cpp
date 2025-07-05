#include "Game.h"

//GameObjectFactory is used to register types
#include "GameObjectFactory.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "Background.h"

//InputHandler is called for updating the keyboard and mouse
#include "InputHandler.h"

//mainmenu state is init when the game starts
#include "MainMenuState.h"

//iostream and SDL
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

Game* Game::_instance;//static instance, must be declared
Game* Game::Instance()
{
	if (_instance == 0)
	{
		_instance = new Game();
	}
	return _instance;
}

void Game::Init(const char* title, int gameWidth, int gameHeight)
{
	//Inits SDL, creates a window and a renderer
	_quit = true;
	//initializes SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		cout << "SDL initialized successfully...\n";
		_gameWidth = gameWidth;
		_gameHeight = gameHeight;
		//creates a window
		_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _gameWidth, _gameHeight, SDL_WINDOW_SHOWN);
		if (_window != nullptr)
		{
			cout << "Window created successfully...\n";
			//creates a renderer
			_renderer = SDL_CreateRenderer(_window, -1, 0);
			if (_renderer != nullptr)
			{
				cout << "Renderer create successfully...\n";
				cout << "SDL initialized!\n\n";
				//everything is Init, so now change quit to false, i.e. start the game
				_quit = false;
				//SDL loaded successfully, now load the game
				
				//register all gameObject types
				//**required for the state parser
				GameObjectFactory::Instance()->RegisterType("MenuButton", new MenuButtonCreator());
				GameObjectFactory::Instance()->RegisterType("AnimatedGraphic", new AnimatedGraphicCreator());
				GameObjectFactory::Instance()->RegisterType("Background", new BackgroundCreator());
				//push_back() first GameState, i.e. 'mainmenu'
				_gameStateMachine = new GameStateMachine();
				_gameStateMachine->changeState(new MainMenuState());
				//seed the random engine
				_generator = new std::default_random_engine(time_t(SDL_GetTicks()));
				//start the game, everything initialized
			}
			else
			{
				_quit = true;
			}
		}
		else
		{
			_quit = true;
			cout << "Window wasn't created!\n";
		}
	}
	else
	{
		_quit = true;
		cout << "SDL couldn't initialize!\n";
	}
}

void Game::Events()
{
	//call Update() of the InputHandler, it handles events
	InputHandler::Instance()->Update();
}
void Game::Update()
{
	//calls Update() of the FSM, and that calls the Update() of the current state
	_gameStateMachine->Update();
}
void Game::Render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);//set renderer's color to black
	SDL_RenderClear(_renderer);//clear the renderer to black

	_gameStateMachine->Render();
	//calls the FSM Render() which calls the current state's Render()

	SDL_RenderPresent(_renderer);
	//show the renderer to the screen
	//Update the screen with the renderer
}
void Game::Clean()
{
	cout << "Cleaning up after SDL...\n";
	SDL_Quit();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	_renderer = 0;
}