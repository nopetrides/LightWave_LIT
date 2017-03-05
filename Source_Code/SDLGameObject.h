﻿

#ifndef SDLGameObject_h
#define SDLGameObject_h

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
	void subCameraOffset(SDL_Rect* cam);
	void addCameraOffset(SDL_Rect *cam);
	

	Vector2D getPos() { return m_position; }
	int getHeight() { return m_height; }
	int getWidth() { return m_width; }

	void collideBottom(SDLGameObject* p);
	void collideTop(SDLGameObject* p);
	void collideLeft(SDLGameObject* p);
	void collideRight(SDLGameObject* p);

	
	bool jumping = true;
	bool double_jumping = true;
	bool alive = true;
	bool dash_available = true;
	bool facingRight;

	//we dont use these anymore
	bool b_collideBottom = false;
	bool b_collideTop = false;
	bool b_collideRight = false;
	bool b_collideLeft = false;

	void PlayerCollisionAgainstHazards(SDLGameObject* hazards);
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

	int originX;
	int originY;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;
};
#endif 