#ifndef SDL_Game_Programming_Book_Player_h
#define SDL_Game_Programming_Book_Player_h

#include <iostream>
#include "SDLGameObject.h"
#include "InputHandler.h"


class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	void jump();
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void handleInput(); //page 89
	int gravity = 10;
	bool jumping = true;
};

#endif