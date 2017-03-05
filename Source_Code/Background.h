#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "SDLGameObject.h"
#include "Game.h"
class Background : public SDLGameObject
{
public: 
	Background(const LoaderParams* pParams);
	void draw();
	void update();
	void clean();


private: 

};

#endif	