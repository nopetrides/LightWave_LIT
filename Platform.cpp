#include "Platform.h"

Platform::Platform(const LoaderParams* pParams) :SDLGameObject(pParams)
{

}

void Platform::setSpeed(int speedChange)
{
	m_ChangeSpeed = speedChange;
}
int Platform::getSpeedMult()
{
	return m_ChangeSpeed;
}

void Platform::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Platform::update()
{
	m_currentFrame = 0;
	SDLGameObject::update();
}

void Platform::clean()
{

}