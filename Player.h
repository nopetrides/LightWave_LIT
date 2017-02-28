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

	SDL_Point* grapplePoint = new SDL_Point();
	bool didHookHitPlatform(SDLGameObject *r);
	int maxHookDistance = 500;

	int getDesiredX() { return desiredX; }
	int getDesiredY() { return desiredY; }

	void applyForce(int x, int y);

	float hookExtendSpeed = 30;
	float pullPlayerSpeed = 25;

private:
	void handleInput(); //page 89
	int gravity = 10;
	//bool jumping = true;
	int start_posX;
	int start_posY;
	bool alive = true;
	bool dash_available = true;

	int midpointX;
	int midpointY;
	bool extending = false;


	//Vars for actually moving the player when they grapple something. 
	//Desired directions
	int desiredX;
	int desiredY;

protected:

};

#endif