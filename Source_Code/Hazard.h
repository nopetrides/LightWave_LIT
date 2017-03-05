#ifndef HAZARD_H 
#define HAZARD_H
#include "SDLGameObject.h"

class Hazard : public SDLGameObject
{

public:
	Hazard(const LoaderParams* pParams);
//	void setSpeed(int speedChange);
	//int getSpeedMult();
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_ChangeSpeed;




};

#endif // !PLATFORM_H 