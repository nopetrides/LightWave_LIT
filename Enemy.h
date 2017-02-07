#ifndef __Enemy__
#define __Enemy__
#include <iostream>
//#include "GameObject.h"
#include "SDLGameObject.h"


class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
};
#endif /* defined(__Game__) */