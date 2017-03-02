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
	bool getHooked() { return hooked; }

	int getCamX() { return camX; }
	int getCamY() { return camY; }
	void setCamX(int x) { camX = x; }
	void setCamY(int y) { camY = y; }


	float timeHookUsed = NULL;
	float hookCoolDown = 5000; // 5 seconds.
	void applyForce(int x, int y);

	float hookExtendSpeed = 30;
	float pullPlayerSpeed = 25;
	int hookAngle = 0;

private:
	void handleInput(); //page 89
	int gravity = 10;
	//bool jumping = true;
	int start_posX;
	int start_posY;
	float hookLength;
	int midpointX;
	int midpointY;
	bool extending = false;
	bool hooked = false;


	int camX;
	int camY;

	//Vars for actually moving the player when they grapple something. 
	//Desired directions
	int desiredX;
	int desiredY;

protected:

};

#endif