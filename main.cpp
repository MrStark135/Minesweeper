#include <iostream>
#include "Class/Game.h"
using namespace std;

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int main(int argc, char** argv)
{
	int frameStart, frameTime;
	Game::Instance()->Init("Any name for the window", 1000, 650);
	while (!Game::Instance()->Quit())
	{
		frameStart = SDL_GetTicks();
		Game::Instance()->Render();
		Game::Instance()->Events();
		Game::Instance()->Update();
		if (Game::Instance()->GetRenderer() == 0) break;
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}
	}
	return 0;
}