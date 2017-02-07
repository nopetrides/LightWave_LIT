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
	int current_pos = m_position.getY();
	current_pos += gravity;
	m_position.setY(current_pos);

	if (m_position.getY() > 200)
	{
		m_position.setY(200);
		jumping = false;
	}

	m_currentFrame = int(((SDL_GetTicks() / 50) % 7));
	m_acceleration.setX(-0.01); //page 77

	handleInput();

	SDLGameObject::update();
}

void Player::clean()
{
}

void Player::handleInput()
{

	/*Vector2D* target = TheInputHandler::Instance()->getMousePosition(); //page 117
	m_velocity = *target - m_position;
	m_velocity /= 50;*/

//	std::cout << "HandleInput called " << "\n";
//	if(TheInputHandler::Instance()->getMouseButtonState(LEFT))
//	{
//		m_velocity.setX(1);
//	}

//	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
//	m_velocity = (*vec - m_position) / 100;
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_velocity.setX(2);
	//	std::cout << "Key down right key detected " << "\n";
	}
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		m_velocity.setX(-2);
	//	std::cout << "Key down left key detected " << "\n";
	}
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP))
	{
		//m_velocity.setY(-2);
		if (!jumping)
		{
			jump();
			jumping = true;
		}
	}
	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
	{
		//m_velocity.setY(2);
	}
	
}


void Player::jump()
{
	int current_pos = m_position.getY();
	current_pos -= 100;
	m_position.setY(current_pos);
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


