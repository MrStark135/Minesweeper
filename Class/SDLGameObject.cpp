#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject()
	: GameObject() {}

void SDLGameObject::Draw()
{
	TextureManager::Instance()->DrawFrame(_textureID, _currentRow, _currentFrame, _width, _height, _position.getX(), _position.getY(), Game::Instance()->GetRenderer(), SDL_FLIP_NONE);
}
void SDLGameObject::Update()
{
	_velocity += _acceleration;
	_position += _velocity;
}

void SDLGameObject::Load(const LoaderParams* params)
{
	_position = Vector2D(params->getX(), params->getY()); 
	_velocity = Vector2D(0, 0);
	_acceleration = Vector2D(0, 0);

	_numFrames = params->getFrames();
	_width = params->getWidth();
	_height = params->getHeight();
	_textureID = params->GetTextureID();
	
	_currentFrame = 1;
	_currentRow = 1;
}