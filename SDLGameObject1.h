//
//  GameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 31/12/2012.
//  Copyright (c) 2012 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_SDLGameObject_h
#define SDL_Game_Programming_Book_SDLGameObject_h

#include <iostream>
#include "SDL.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

#include "TextureManager.h"
//#include "Game.h"

class SDLGameObject : public GameObject
{
public:

	SDLGameObject(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	Vector2D getPos() { return m_position; }
	int getHeight() { return m_height; }
	int getWidth() { return m_width; }

	void collideBottom(SDLGameObject* p);
	void collideTop(SDLGameObject* p);
	void collideLeft(SDLGameObject* p);
	void collideRight(SDLGameObject* p);

	bool jumping = true;
	bool double_jumping = true;

	bool b_collideBottom = false;
	bool b_collideTop = false;
	bool b_collideRight = false;
	bool b_collideLeft = false;


	void PlayerCollisionAgainstPlatforms(SDLGameObject* platform);
	SDLGameObject* current_collide = NULL;

protected:

	//	int m_x;
	//	int m_y;

	float collideDistance = 3.0f; // Collision distance from platform

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration; //page 77

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;
};
#endif /* defined(__SDL_Game_Programming_Book__Chapter_3_SDLGameObject__) */