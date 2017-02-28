#ifndef PLATFORM_H 
#define PLATFORM_H
#include "SDLGameObject.h"

class Platform : public SDLGameObject
{

public:
	Platform(const LoaderParams* pParams);
	void setSpeed(int speedChange);
	int getSpeedMult();
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_ChangeSpeed;




};

#endif // !PLATFORM_H 
