#include <iostream>
#include "Player.h"

Player::Player(const LoaderParams* pParams) :SDLGameObject(pParams)
{
	start_posX = pParams->getX();
	start_posY = pParams->getY();
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
	if (m_position.getY() > TheGame::Instance()->level_height)
	{
		alive = false;
	}
	if (b_collideBottom)
	{
		collideBottom(current_collide);
	}
	if (b_collideTop)
	{
		collideTop(current_collide);
	}
	if (b_collideLeft)
	{
		collideLeft(current_collide);
	}
	if (b_collideRight)
	{
		collideRight(current_collide);
	}
	if (!alive)
	{
		respawn();
	}
}

void Player::clean()
{
}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))//	std::cout << "Key down right key detected " << "\n";
	{
		if (m_velocity.getX() < 0) // if moving to the left
		{

			m_velocity.setX(m_velocity.getX() + 1); // move quickly the opposite direction (put on the brakes)
		}
		else if (m_velocity.getX() < 5) // Max velocity of 5 to the right
		{
			if (!jumping)
				m_velocity.setX(m_velocity.getX() + 0.5); // good control on ground
			else
				m_velocity.setX(m_velocity.getX() + 0.1); // bad control in air
		}
		
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))//	std::cout << "Key down left key detected " << "\n";
	{
		if (m_velocity.getX() > 0) // if moving to the right
		{
			m_velocity.setX(m_velocity.getX() - 1); // move quickly the opposite direction (put on the brakes)
		}
		else if (m_velocity.getX() > -5) // Max velocity of 5 to the left
		{
			if (!jumping)
				m_velocity.setX(m_velocity.getX() - 0.5); // good control on ground
			else
				m_velocity.setX(m_velocity.getX() - 0.1); // bad control in air
		}
		
	}
	else
	{
		if (m_velocity.getX() > 0.2 || m_velocity.getX() < -0.2) // if moving left or right
		{
			if (m_velocity.getX() > 0.2) // if moving to the right
				m_velocity.setX(m_velocity.getX() - 0.2); // decelerate
			if (m_velocity.getX() < -0.2) // if moving to the left
				m_velocity.setX(m_velocity.getX() + 0.2); // decelerate
		}
		else
			m_velocity.setX(0);
	}
	if (TheInputHandler::Instance()->joysticksInitialised()) { // Check if joystick is initialised
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) || TheInputHandler::Instance()->getButtonState(0, 0)) // **replace (0,0) with joystick for each player
		{
			//m_velocity.setY(-2);
			if (!jumping) // if on the ground
			{
				m_velocity.setY(-10); // set upwards velocity
				jumping = true;
			}
			else if (m_velocity.getY() < 0) // if still moving upwards
			{
				m_velocity.setY(m_velocity.getY() + 0.2); // 'gravity' is lessened (this allows to hold the up button and jump higher)
			}
			else // if falling
			{
				m_velocity.setY(m_velocity.getY() + 0.5);
			}
		}
		else // if not holding button up
		{ 
			m_velocity.setY(m_velocity.getY() + 0.5); // gravity
		}
	}
	else
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) // no joystick
		{
			//m_velocity.setY(-2);
			if (!jumping) // if on the ground
			{
				m_velocity.setY(-10); // set upwards velocity
				jumping = true;
			}
			else if (m_velocity.getY() < 0) // if still moving upwards
			{
				m_velocity.setY(m_velocity.getY() + 0.2); // 'gravity' is lessened (this allows to hold the up button and jump higher)
			}
			else // if falling
			{
				m_velocity.setY(m_velocity.getY() + 0.5); // gravity
			}
		}
		else // if not holding button up
		{
			m_velocity.setY(m_velocity.getY() + 0.5); // gravity
		}
	}
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		//Does nothing yet
	}

}
/*
void Player::collideBottom(SDLGameObject* p)
{
	m_velocity.setY(0);
	jumping = false;
	m_position.setY(m_position.getY() - 1);
}

void Player::collideTop(SDLGameObject* p)
{
	m_velocity.setY(0);
	m_position.setY(m_position.getY() + 1);
}

void Player::collideRight(SDLGameObject * p)
{
	m_velocity.setX(0);
	m_position.setX(m_position.getX() - 1);
}

void Player::collideLeft(SDLGameObject * p)
{
	m_velocity.setX(0);
	m_position.setX(m_position.getX() + 1);
}
*/
void Player::respawn()
{
	m_position.setX(start_posX);
	m_position.setY(start_posY);
	m_velocity.setX(0);
	m_velocity.setY(0);
	alive = true;
}