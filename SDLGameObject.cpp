#include <iostream>
#include "SDLGameObject.h"
#include "Game.h"


SDLGameObject::SDLGameObject(const LoaderParams* pParams) :
	GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0)
{
	//	m_x = pParams->getX();
	//	m_y = pParams->getY();

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw()
{
	//	TheTextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(),SDL_FLIP_NONE);
	//	TheTextureManager::Instance()->drawFrame(m_textureID,(int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(),SDL_FLIP_NONE);
	if (m_velocity.getX() > 0)
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}
}

void SDLGameObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;

}

void SDLGameObject::clean()
{
}


void SDLGameObject::PlayerCollisionAgainstPlatforms(SDLGameObject * platform)
{
	current_collide = platform;

	//Chris
	int playerTop = getPos().m_y; // Top of the player Rect
	int playerBottom = getPos().m_y + getHeight(); // Bottom of the player Rect
	int playerLeft = getPos().m_x; // Left of the player Rect 
	int playerRight = getPos().m_x + getWidth(); // Right of the player Rect
	int playerMidPointX = getPos().m_x + (getWidth() / 2); // Mid point of player X. 
	int playerMidPointY = getPos().m_y + (getHeight() / 2); // Mid point of player Y. 
	int playerHeight = getHeight();
	int playerWidth = getWidth();

	//Calculate top, bottom, left and right of platform
	int platformTop = platform->getPos().m_y; // Top of the platform Rect
	int platformBottom = platform->getPos().m_y + platform->getHeight(); // Bottom of the platform Rect
	int platformLeft = platform->getPos().m_x; // Left of the platform Rect 
	int platformRight = platform->getPos().m_x + platform->getWidth(); // Right of the platform Rect

																	   //Player on top of platform check - 
	if (playerBottom >= platformTop &&
		playerBottom < platformBottom &&
		playerTop >= (platformTop - playerHeight - collideDistance) &&
		playerMidPointX >= platformLeft &&
		playerMidPointX <= platformRight)
	{
		collideBottom(platform);
		//b_collideBottom = true;
		std::cout << "Bottom player, on top of platform.\n";
	}
	//	else b_collideBottom = false;

	//player bumps head to bottom of platform -
	if (playerTop <= platformBottom &&
		playerTop > platformTop &&
		playerBottom <= (platformBottom + playerHeight + collideDistance) &&
		playerMidPointX >= platformLeft &&
		playerMidPointX <= platformRight)
	{
		collideTop(platform);
		//b_collideTop = true;
		std::cout << "Top player, hitting bottom of platform.\n";
	}
	//else b_collideTop = false;


	//TODO: fix side collisions
	//Player bumps into left side of platform checking if bottom is > top of plat
	if (playerMidPointY > platformTop &&
		playerMidPointY < platformBottom &&
		playerLeft >= (platformLeft - playerWidth - collideDistance) &&
		playerRight >= platformLeft &&
		playerRight <= platformRight)


	{

		collideRight(platform);
		//b_collideRight = true;
		std::cout << "Right side of player hit left side platform,with bottom being below top of platform.\n ";
	}
	//	else b_collideRight = false;

	//Player bumps into right side of platform check
	if (playerMidPointY > platformTop &&
		playerMidPointY < platformBottom &&
		playerRight <= (platformRight + playerWidth + collideDistance) &&
		playerLeft <= platformRight &&
		playerLeft >= platformLeft)
	{
		collideLeft(platform);
		//	b_collideLeft = true;
		std::cout << "left side Player hit right side of plat, with top being above top of platform.\n";
	}
	//else b_collideLeft = false;
}
void SDLGameObject::collideBottom(SDLGameObject* p)
{
	m_velocity.setY(0);
	jumping = false;
	m_position.setY(m_position.getY() - 1);
}

void SDLGameObject::collideTop(SDLGameObject* p)
{
	m_velocity.setY(0);
	m_position.setY(m_position.getY() + 1);
}

void SDLGameObject::collideRight(SDLGameObject * p)
{
	m_velocity.setX(0);
	m_position.setX(m_position.getX() - 1);
}

void SDLGameObject::collideLeft(SDLGameObject * p)
{
	m_velocity.setX(0);
	m_position.setX(m_position.getX() + 1);
}