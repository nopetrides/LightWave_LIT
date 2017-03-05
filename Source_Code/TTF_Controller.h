#pragma once
#ifndef TTF_CONTROLLER_H
#define TTF_CONTROLLER_H
#include "SDL_ttf.h"


class TTF_Controller
{
public:
	void init();
	void setUpFont();
	//void freeFontSurface();
	void Quit();
	//SDL_Surface getSurface();

};

#endif // !TTF_CONTROLLER_H
