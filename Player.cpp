#include <iostream>
#include "Player.h"

Player::Player(const LoaderParams* pParams) :SDLGameObject(pParams)
{
}

void Player::draw()
{
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Player::update()
{
	// Akward to try and get + set current Y pos, consider changing


	m_currentFrame = int(((SDL_GetTicks() / 50) % 7)); // Running animation


	handleInput();


	SDLGameObject::update();

}

void Player::clean()
{
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		if (m_velocity.getX() < 0)
		{

			m_velocity.setX(m_velocity.getX() + 1);
		}
		else if (m_velocity.getX() < 5)
		{
			if (!jumping)
				m_velocity.setX(m_velocity.getX() + 0.5);
			else
				m_velocity.setX(m_velocity.getX() + 0.10);
		}
		//	std::cout << "Key down right key detected " << "\n";
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		if (m_velocity.getX() > 0)
		{
			m_velocity.setX(m_velocity.getX() - 1);
		}
		else if (m_velocity.getX() > -5)
		{
			if (!jumping)
				m_velocity.setX(m_velocity.getX() - 0.5);
			else
				m_velocity.setX(m_velocity.getX() - 0.1);
		}
		//	std::cout << "Key down left key detected " << "\n";
	}
	else
	{
		if (m_velocity.getX() > 0.2 || m_velocity.getX() < -0.2)
		{
			if (m_velocity.getX() > 0.2)
				m_velocity.setX(m_velocity.getX() - 0.2);
			if (m_velocity.getX() < -0.2)
				m_velocity.setX(m_velocity.getX() + 0.2);
		}
		else
			m_velocity.setX(0);
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		//m_velocity.setY(-2);
		if (!jumping)
		{
			m_velocity.setY(-10);
			jumping = true;
		}
		else if (m_velocity.getY() < 0)
		{
			m_velocity.setY(m_velocity.getY() + 0.2);
		}
		else if (m_position.getY() > 200) // floor collision goes here
		{
			m_velocity.setY(0);
			jumping = false;
		}
		else
		{
			m_velocity.setY(m_velocity.getY() + 0.5);
		}
	}
	else
	{
		if (m_position.getY() > 200) // floor collision goes here
		{
			m_velocity.setY(0);
			jumping = false;
		}
		else
		{
			m_velocity.setY(m_velocity.getY() + 0.5);
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		//m_velocity.setY(2);
	}

}

void Player::collideBottom(SDLGameObject* p)
{
	m_position.setY(p->getPos().getY() - m_height);
}

void Player::collideTop()
{
	//TODO:: Set Up velocity to 0
}

void Player::collideRight(SDLGameObject * p)
{
	m_position.setX(p->getPos().getX() - m_width);
}

void Player::collideLeft(SDLGameObject * p)
{
	m_position.setX(p->getPos().getX() + p->getWidth());
}


/*
void Player::draw(SDL_Renderer* pRenderer)
{
GameObject::draw(pRenderer);
}
void Player::update()
{
//using the fish sprite which has 5 frames
m_x += 2;
m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}
*/
