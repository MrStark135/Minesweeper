#include "AnimatedGraphic.h"
#include "TextureManager.h"
#include "Game.h"
#include <SDL2/SDL.h>

AnimatedGraphic::AnimatedGraphic()
	: SDLGameObject() {}

void AnimatedGraphic::Update()
{
	_currentFrame = int(SDL_GetTicks() / (1000 / _animSpeed) % _numFrames) + 1;
	_currentRow = int(SDL_GetTicks() / (1000 / _animSpeed * _numFrames) % 3) + 1;
}
void AnimatedGraphic::Draw()
{
	SDLGameObject::Draw();
}
void AnimatedGraphic::Clean()
{
	SDLGameObject::Clean();
}

void AnimatedGraphic::Load(const LoaderParams* params)
{
	SDLGameObject::Load(params);
	_animSpeed = params->getAnimSpeed();
}