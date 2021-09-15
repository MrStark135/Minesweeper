#include "MineField.h"

#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"

#include <thread>//to be able to put to sleep the current thread
#include <iostream>

MineField::MineField(int width, int height, int numMines, int offsetX, int offsetY)
	:_width(width),_height(height),_numMines(numMines),_offsetX(offsetX), _offsetY(offsetY),
	_holdLEFT(false),_holdRIGHT(false),_mineHit(false),_gameWon(false)
{
	//init mine positions
	std::uniform_int_distribution<int> distributionY(0, height - 1);
	std::uniform_int_distribution<int> distributionX(0, width - 1);
	int x, y;
	for (int i = 0; i < numMines; i++)
	{
again:	x = distributionX(*Game::Instance()->getRandomGenerator());
		y = distributionY(*Game::Instance()->getRandomGenerator());
		for (int j = 0; j < i; j++)
		{
			if (x == _minePos[j][0] && y == _minePos[j][1])
			{
				goto again;
			}
		}
		_minePos[i][0] = x;
		_minePos[i][1] = y;
	}
	//init tile IDs, i.e. all tiles are covered
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			_mineFieldID[i][j][0] = 1;
			_mineFieldID[i][j][1] = 1;
		}
	}
}

void MineField::Update()
{
	if (InputHandler::Instance()->getMouseButtonState(LEFT) == false) _holdLEFT = false;//reset button press, for clicky effect
	if (InputHandler::Instance()->getMouseButtonState(RIGHT) == false) _holdRIGHT = false;//reset button press, for clicky effect

	if (InputHandler::Instance()->getMouseButtonState(LEFT) == true && _holdLEFT == false)//if a cell is LEFT clicked
	{
		Vector2D* mouse_pos = InputHandler::Instance()->getMousePosition();
		int x = mouse_pos->getX() - _offsetX;
		int y = mouse_pos->getY() - _offsetY;
		for (int i = 0; i < _height; i++)
		{
			for (int j = 0; j < _width; j++)
			{
				if ((x - j * 32 <= 32) && (x - j * 32 > 0))
				{
					if ((y - i * 32 <= 32) && (y - i * 32 > 0))
					{
						setTileID(j, i);

						_holdLEFT = true;//if you hold the button, to register just one click
						break;
					}
				}
			}
		}
	}
	if (InputHandler::Instance()->getMouseButtonState(RIGHT) == true && _holdRIGHT == false)//if a cell is RIGHT clicked
	{
		Vector2D* mouse_pos = InputHandler::Instance()->getMousePosition();
		int x = mouse_pos->getX() - _offsetX;
		int y = mouse_pos->getY() - _offsetY;
		for (int i = 0; i < _height; i++)
		{
			for (int j = 0; j < _width; j++)
			{
				if ((x - j * 32 <= 32) && (x - j * 32 > 0))
				{
					if ((y - i * 32 <= 32) && (y - i * 32 > 0))
					{
						if (_mineFieldID[i][j][1] == 1 && _mineFieldID[i][j][0] == 2)//if already flagged, reset to blank field
						{
							_mineFieldID[i][j][1] = 1;
							_mineFieldID[i][j][0] = 1;
						}
						else if(_mineFieldID[i][j][1] == 1 && _mineFieldID[i][j][0] == 1)//flag the cell
						{
							_mineFieldID[i][j][1] = 1;
							_mineFieldID[i][j][0] = 2;
						}

						_holdRIGHT = true;//if you hold the button, to register just one click
						break;
					}
				}
			}
		}
	}

	int c = 0;//check how many unopen fields are left, and if remained == mines -> you won
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			if (_mineFieldID[i][j][0] == 1 && _mineFieldID[i][j][1] == 1) c++;
			else if (_mineFieldID[i][j][0] == 2 && _mineFieldID[i][j][1] == 1) c++;
			if (c > _numMines) return;
		}
	}
	if (c == _numMines) _gameWon = true;
}
void MineField::Draw()
{
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			TextureManager::Instance()->DrawFrame("tiles", _mineFieldID[i][j][1], _mineFieldID[i][j][0], 32, 32, j * 32 + _offsetX, i * 32 + _offsetY, Game::Instance()->GetRenderer(), SDL_FLIP_NONE);
		}
	}
}

void MineField::openAdjacentTiles(int x, int y)
{
	if (_mineFieldID[y + 1][x + 1][0] == 1 && _mineFieldID[y + 1][x + 1][1] == 1) setTileID(x + 1, y + 1);
	if (_mineFieldID[y - 1][x - 1][0] == 1 && _mineFieldID[y - 1][x - 1][1] == 1) setTileID(x - 1, y - 1);
	if (_mineFieldID[y - 1][x + 1][0] == 1 && _mineFieldID[y - 1][x + 1][1] == 1) setTileID(x + 1, y - 1);
	if (_mineFieldID[y + 1][x - 1][0] == 1 && _mineFieldID[y + 1][x - 1][1] == 1) setTileID(x - 1, y + 1);
	if (_mineFieldID[y + 1][x][0] == 1 && _mineFieldID[y + 1][x][1] == 1) setTileID(x, y + 1);
	if (_mineFieldID[y - 1][x][0] == 1 && _mineFieldID[y - 1][x][1] == 1) setTileID(x, y - 1);
	if (_mineFieldID[y][x + 1][0] == 1 && _mineFieldID[y][x + 1][1] == 1) setTileID(x + 1, y);
	if (_mineFieldID[y][x - 1][0] == 1 && _mineFieldID[y][x - 1][1] == 1) setTileID(x - 1, y);
}
void MineField::setTileID(int x, int y)
{
	int c = 0;
	for (int i = 0; i < _numMines; i++)
	{
		if (x == _minePos[i][0] && y == _minePos[i][1])//if there is a mine on the tile pressed
		{
			_mineFieldID[y][x][1] = 1;
			_mineFieldID[y][x][0] = 3;

			//TextureManager::Instance()->DrawFrame("tiles", _mineFieldID[y][x][1], _mineFieldID[y][x][0], 32, 32, x * 32 + 10, y * 32 + 100, Game::Instance()->GetRenderer(), SDL_FLIP_NONE);
			//SDL_RenderPresent(Game::Instance()->GetRenderer());

			_mineHit = true;

			return;
		}

		//check all surrounding tiles
		if (x + 1 == _minePos[i][0] && y + 1 == _minePos[i][1]) c++;
		else if (x - 1 == _minePos[i][0] && y - 1 == _minePos[i][1]) c++;
		else if (x + 1 == _minePos[i][0] && y - 1 == _minePos[i][1]) c++;
		else if (x - 1 == _minePos[i][0] && y + 1 == _minePos[i][1]) c++;
		else if (x == _minePos[i][0] && y + 1 == _minePos[i][1]) c++;
		else if (x == _minePos[i][0] && y - 1 == _minePos[i][1]) c++;
		else if (x + 1 == _minePos[i][0] && y == _minePos[i][1]) c++;
		else if (x - 1 == _minePos[i][0] && y == _minePos[i][1]) c++;
	}
	switch (c)//just maps the corresponding number, for c counted mines
	{	
	case 0:
	{
		_mineFieldID[y][x][1] = 2;
		_mineFieldID[y][x][0] = 1;

		openAdjacentTiles(x, y);
		
		break;
	}
	case 1:
	{
		_mineFieldID[y][x][1] = 2;
		_mineFieldID[y][x][0] = 2;
		break;
	}
	case 2:
	{
		_mineFieldID[y][x][1] = 2;
		_mineFieldID[y][x][0] = 3;
		break;
	}
	case 3:
	{
		_mineFieldID[y][x][1] = 3;
		_mineFieldID[y][x][0] = 1;
		break;
	}
	case 4:
	{
		_mineFieldID[y][x][1] = 3;
		_mineFieldID[y][x][0] = 2;
		break;
	}
	case 5:
	{
		_mineFieldID[y][x][1] = 3;
		_mineFieldID[y][x][0] = 3;
		break;
	}
	case 6:
	{
		_mineFieldID[y][x][1] = 4;
		_mineFieldID[y][x][0] = 1;
		break;
	}
	case 7:
	{
		_mineFieldID[y][x][1] = 4;
		_mineFieldID[y][x][0] = 2;
		break;
	}
	case 8:
	{
		_mineFieldID[y][x][1] = 4;
		_mineFieldID[y][x][0] = 3;
		break;
	}
	default:
	{
		_mineFieldID[y][x][1] = 2;
		_mineFieldID[y][x][0] = 1;
		break;
	}
	}
}

void MineField::gameOverAnim()
{
	int i, j;
	for (int s = 0; s < _numMines; s++)
	{
		i = _minePos[s][1];
		j = _minePos[s][0];

		_mineFieldID[i][j][1] = 1;
		_mineFieldID[i][j][0] = 3;

		TextureManager::Instance()->DrawFrame("tiles", _mineFieldID[i][j][1], _mineFieldID[i][j][0], 32, 32, j * 32 + _offsetX, i * 32 + _offsetY, Game::Instance()->GetRenderer(), SDL_FLIP_NONE);
		SDL_RenderPresent(Game::Instance()->GetRenderer());
		SDL_Delay(170);

		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(20));
		//puts to sleep the current thread, so that the others can catch up. time required is innoticable by the user
	}
	SDL_Delay(2500);
}
void MineField::gameWonAnim()
{
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			_mineFieldID[i][j][1] = 1;
			_mineFieldID[i][j][0] = 2;

			TextureManager::Instance()->DrawFrame("tiles", _mineFieldID[i][j][1], _mineFieldID[i][j][0], 32, 32, j * 32 + _offsetX, i * 32 + _offsetY, Game::Instance()->GetRenderer(), SDL_FLIP_NONE);
			SDL_RenderPresent(Game::Instance()->GetRenderer());
			SDL_Delay(40);

			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(20));
			//puts to sleep the current thread, so that the others can catch up. time required is innoticable by the user
		}
	}
	SDL_Delay(2500);
}