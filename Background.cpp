#include "Background.h"

Background::Background(const LoaderParams* pParams) :SDLGameObject(pParams)
{
	setType("Background");
}

void Background::draw()
{
	SDLGameObject::draw();
}

void Background::update()
{
	m_currentFrame = 0;
	SDLGameObject::update();
}

void Background::clean()
{
	SDLGameObject::clean();
}

