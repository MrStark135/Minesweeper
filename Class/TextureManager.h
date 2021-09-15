#pragma once
#include <SDL.h>

#include <string>
#include <map>
using namespace std;

class TextureManager
{
public:
	//To add a texture in the map, or to remove from it. The map holds ALL loaded textures by their corresponding IDs
	bool LoadPNG(const char* filename, string id, SDL_Renderer* renderer);
	void CleanPNG(string id);

	//different functions to handle drawing to the screen
	void Draw(string id, int x, int y, int width, int height, SDL_Renderer* renderer);
	void DrawFrame(string id, int currentRow, int currentFrame, int srcw, int srch, int destx, int desty, SDL_Renderer* renderer, SDL_RendererFlip flip);
	void DrawTile(string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer);

	static TextureManager* Instance()
	{
		if (_instance == 0)
		{
			_instance = new TextureManager();
		}
		return _instance;
	}
private:
	TextureManager() {};
	static TextureManager* _instance;

	//to hold ALL loaded, can be accessed by the corresponding ID, for each texture specified when loaded
	map<string, SDL_Texture*> _textureMap;
};

