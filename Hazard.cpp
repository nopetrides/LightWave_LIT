#include "Hazard.h"

Hazard::Hazard(const LoaderParams* pParams) :SDLGameObject(pParams)
{

}


void Hazard::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Hazard::update()
{
	m_currentFrame = 0;
	SDLGameObject::update();
}

void Hazard::clean()
{

}