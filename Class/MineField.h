#pragma once

#include <random>
#include <vector>
#include "Vector2D.h"

class MineField
{
public:
	MineField(int width = 10, int height = 10, int numMines = 1, int offsetX = 0, int offsetY = 0);

	void Update();
	void Draw();

	void openAdjacentTiles(int x, int y);
	void setTileID(int x, int y);
	void gameOverAnim();
	void gameWonAnim();
	
	int* getTileRow(int x, int y) { return &_mineFieldID[y][x][1]; }//y coordinate is second
	int* getTileFrame(int x, int y) { return &_mineFieldID[y][x][0]; }//x coordinate is first
	Vector2D getMinePos(int index) { return Vector2D(_minePos[index][0], _minePos[index][1]); }
	int getFieldWidth() { return _width; }
	int getFieldHeight() { return _height; }
	int getNumMines() { return _numMines; }
	bool getMineHit() { return _mineHit; }
	bool getGameWon() { return _gameWon; }
private:
	int _mineFieldID[50][50][2];//x then y
	int _minePos[500][2];//x, then y

	int _width, _height;
	int _offsetX, _offsetY;
	int _numMines;

	bool _holdLEFT,_holdRIGHT;
	bool _mineHit,_gameWon;
};