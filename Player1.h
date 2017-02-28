#ifndef SDL_Game_Programming_Book_Player_h
#define SDL_Game_Programming_Book_Player_h

#include <iostream>
#include "SDLGameObject.h"
#include "InputHandler.h"
#include "Game.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	//void collideBottom(SDLGameObject* p);
	//void collideTop(SDLGameObject *p);
	//void collideRight(SDLGameObject* p);
	//void collideLeft(SDLGameObject* p);
	void respawn();

private:
	void handleInput(); //page 89
	int gravity = 10;
	//bool jumping = true;
	int start_posX;
	int start_posY;
	bool alive = true;
	bool dash_available = true;
protected:

};

#endif