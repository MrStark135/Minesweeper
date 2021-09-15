#include "TextureManager.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
using namespace std;

TextureManager* TextureManager::_instance;
bool TextureManager::LoadPNG(const char* filename, string id, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface;
	SDL_Texture* texture;
	tempSurface = IMG_Load(filename);
	if (tempSurface == nullptr)
	{
		cout << "Image '" << filename << "' not loaded\n";
		return false;
	}
	else
	{
		cout << "Image '" << filename << "' loaded successfully\n";
		texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if (texture != nullptr)
		{
			_textureMap[id] = texture;
		}
	}
	return true;
}
void TextureManager::CleanPNG(string id)
{
	_textureMap.erase(id);
}

void TextureManager::Draw(string id, int x, int y, int width, int height, SDL_Renderer* renderer)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;
	
	destRect.x = x;
	destRect.y = y;
	destRect.w = width;
	destRect.h = height;

	SDL_RenderCopy(renderer, _textureMap[id], &srcRect, &destRect);
}
void TextureManager::DrawFrame(string id, int currentRow, int currentFrame, int srcw, int srch, int destx, int desty, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect, destRect;

	srcRect.x = (currentFrame - 1) * srcw;
	srcRect.y = (currentRow - 1) * srch;
	srcRect.w = srcw;
	srcRect.h = srch;

	destRect.x = destx;
	destRect.y = desty;
	destRect.w = srcw;
	destRect.h = srch;

	SDL_RenderCopyEx(renderer, _textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
void TextureManager::DrawTile(string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* renderer)
{
	SDL_Rect srcRect, destRect;
	srcRect.x = margin + (width + spacing)*currentFrame;
	srcRect.y = margin + (height + spacing)*currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopy(renderer, _textureMap[id], &srcRect, &destRect);
}