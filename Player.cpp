#include <iostream>
#include "Player.h"

Player::Player(const LoaderParams* pParams) :SDLGameObject(pParams)
{
	start_posX = pParams->getX();
	start_posY = pParams->getY();
	setType("Player");
}

void Player::draw()
{
	SDL_Point* rotationPoint = new SDL_Point();
	rotationPoint->x = 0; //midpointX;
	rotationPoint->y = rotationPoint->y + 5;// midpointY;

											//Check to seee if player is extending hook, then do this draw. maybe...
	if (extending)
	{
		if (hookLength < maxHookDistance)
			hookLength += hookExtendSpeed;
		else hookLength -= hookExtendSpeed;

		//Adjust midPoint for camera position
		midpointX -= getCamX();
		midpointY -= getCamY();

		TextureManager::Instance()->draw("hook", midpointX, midpointY, hookLength, 10,
			TheGame::Instance()->getRenderer(), SDL_FLIP_NONE, rotationPoint, hookAngle);

		//Adjust midPoint for camera position
		midpointX += getCamX();
		midpointY += getCamY();

	}
	SDLGameObject::draw(); // we now use SDLGameObject
}

void Player::update()
{
	// Akward to try and get + set current Y pos, consider changing

	m_currentFrame = int(((SDL_GetTicks() / 50) % 7)); // Running animation
	if (m_velocity.getY() == 0 && m_velocity.getX() != 0)
	{
		if (TheGame::Instance()->SFXOn)
		{
			if (!Mix_Playing(0))
				Mix_PlayChannel(0, TheGame::Instance()->gWalkFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
		}
	}
	handleInput();

	SDLGameObject::update();
	if (m_position.getY() > TheGame::Instance()->level_height)
	{
		alive = false;

	}
	/*if (b_collideBottom)
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
	}*/
	if (!alive)
	{
		respawn();
	}
	midpointX = m_position.m_x + (m_width / 2);
	midpointY = m_position.m_y + (m_height / 2);

	//Update position of the grapplingHook point
	if (!extending)
	{
		grapplePoint->x = midpointX;
		grapplePoint->y = midpointY;

		desiredX = NULL;
		desiredY = NULL;
	}

}

void Player::clean()
{
}

void Player::handleInput()
{
	
	if (TheInputHandler::Instance()->joysticksInitialised()) { // Check if joystick is initialised
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) || TheInputHandler::Instance()->getButtonState(0, 0)) // **replace (0,0) with joystick for each player
		{
			//m_velocity.setY(-2);
			if (!jumping) // if on the ground
			{
				m_velocity.setY(-10); // set upwards velocity
				jumping = true;
				if (TheGame::Instance()->SFXOn)
					Mix_PlayChannel(-1, TheGame::Instance()->gLandFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
			}
			else if (m_velocity.getY() < 0) // if still moving upwards
			{
				m_velocity.setY(m_velocity.getY() + 0.2); // 'gravity' is lessened (this allows to hold the up button and jump higher)
			}
			else if (!double_jumping)
			{
				m_velocity.setY(-8);
				double_jumping = true;
				if (TheGame::Instance()->SFXOn)
					Mix_PlayChannel(-1, TheGame::Instance()->gLandFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
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

		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) || TheInputHandler::Instance()->getAxisX(0, 1) > 0)//	std::cout << "Key down right key detected " << "\n";
		{
			if (m_velocity.getX() < 0) // if moving to the left
			{

				m_velocity.setX(m_velocity.getX() + 1); // move quickly the opposite direction (put on the brakes)
			}
			else if (m_velocity.getX() < 15) // Max velocity of 5 to the right
			{
				if (!jumping)
					m_velocity.setX(m_velocity.getX() + 0.2); // good control on ground
				else
					m_velocity.setX(m_velocity.getX() + 0.1); // bad control in air
			}
			else if (m_velocity.getX() > 15)
			{
				m_velocity.setX(m_velocity.getX() - 0.1);
			}
		}
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) || TheInputHandler::Instance()->getAxisX(0, 1) < 0)//	std::cout << "Key down left key detected " << "\n";
		{
			if (m_velocity.getX() > 0) // if moving to the right
			{
				m_velocity.setX(m_velocity.getX() - 1); // move quickly the opposite direction (put on the brakes)
			}
			else if (m_velocity.getX() > -15) // Max velocity of 5 to the left
			{
				if (!jumping)
					m_velocity.setX(m_velocity.getX() - 0.2); // good control on ground
				else
					m_velocity.setX(m_velocity.getX() - 0.1); // bad control in air
			}
			else if (m_velocity.getX() < -15)
			{
				m_velocity.setX(m_velocity.getX() + 0.1);
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
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
		{
			//Does nothing yet
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_X) || TheInputHandler::Instance()->getButtonState(0, 2)) // **replace (0,0) with joystick for each player
		{
			if (dash_available && m_velocity.getX() != 0 && jumping)
			{
				if (m_velocity.getX() > 0) // if moving to the right
				{
					m_velocity.setX(20);
				}
				else if (m_velocity.getX() < 0) //
				{
					m_velocity.setX(-20);
				}
				dash_available = false;
				if (TheGame::Instance()->SFXOn)
					Mix_PlayChannel(-1, TheGame::Instance()->gDashFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
			}
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z) || TheInputHandler::Instance()->getButtonState(0, 5)) // **replace (0,0) with joystick for each player
		{
			//if (SDL_GetTicks() - timeHookUsed <= hookCoolDown)
			//{
				extending = true;
				timeHookUsed = SDL_GetTicks();
			//}
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z) == false && TheInputHandler::Instance()->getButtonState(0, 5) == false)
		{
			extending = false;

		}
		//Hook direction tracking
		if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) < 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) > 0) && extending)
		{	//Aiming TopRight only
			grapplePoint->x += hookExtendSpeed;
			grapplePoint->y -= hookExtendSpeed;

			desiredX = pullPlayerSpeed;
			desiredY = -pullPlayerSpeed;

			//set hook angle 
			hookAngle = 315;
		}			
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0 &&
			TheInputHandler::Instance()->getAxisX(0, 2) > 0) && extending)
		{	//Aiming bottomRight only
			grapplePoint->x += hookExtendSpeed;
			grapplePoint->y += hookExtendSpeed;

			desiredX = pullPlayerSpeed;
			desiredY = pullPlayerSpeed;
			//set hook angle 
			hookAngle = 45;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisX(0, 2) > 0) && extending)
		{	//Aiming Right only
			grapplePoint->x += hookExtendSpeed;
			desiredX = pullPlayerSpeed;
			//desiredY = m_velocity.m_y;
			//set hook angle 
			hookAngle = 0;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) < 0) && extending)
		{	//Aiming bottom left only
			grapplePoint->x -= hookExtendSpeed;
			grapplePoint->y += hookExtendSpeed;

			desiredX = -pullPlayerSpeed;
			desiredY = pullPlayerSpeed;

			//set hook angle 
			hookAngle = 135;

		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0) && extending)
		{	//Aiming bottom only
			grapplePoint->y += hookExtendSpeed;

			//desiredX = m_velocity.m_x;
			desiredY = pullPlayerSpeed;

			//set hook angle 
			hookAngle = 90;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) < 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) < 0) && extending)
		{	//Aiming  top left only
			grapplePoint->x -= hookExtendSpeed;
			grapplePoint->y -= hookExtendSpeed;

			desiredX = -pullPlayerSpeed;
			desiredY = -pullPlayerSpeed;

			//set hook angle 
			hookAngle = 225;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisX(0, 2) < 0) && extending)
		{	//Aiming  left only
			grapplePoint->x -= hookExtendSpeed;

			desiredX = -pullPlayerSpeed;
			//desiredY = m_velocity.m_y;

			//set hook angle 
			hookAngle = 180;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) < 0) && extending)
		{	//Aiming Top only
			grapplePoint->y -= hookExtendSpeed; //Update
												//desiredX = m_velocity.m_x;
			desiredY = -pullPlayerSpeed;
			//set hook angle 
			hookAngle = 270;
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
				if (TheGame::Instance()->SFXOn)
					Mix_PlayChannel(-1, TheGame::Instance()->gLandFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
			}
			else if (m_velocity.getY() < 0) // if still moving upwards
			{
				m_velocity.setY(m_velocity.getY() + 0.2); // 'gravity' is lessened (this allows to hold the up button and jump higher)
			}
			else if (!double_jumping)
			{
				m_velocity.setY(-8);
				double_jumping = true;
				if(TheGame::Instance()->SFXOn)
					Mix_PlayChannel(-1, TheGame::Instance()->gLandFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
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
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))//	std::cout << "Key down right key detected " << "\n";
		{
			if (m_velocity.getX() < 0) // if moving to the left
			{

				m_velocity.setX(m_velocity.getX() + 1); // move quickly the opposite direction (put on the brakes)
			}
			else if (m_velocity.getX() < 15) // Max velocity of 5 to the right
			{
				if (!jumping)
					m_velocity.setX(m_velocity.getX() + 0.2); // good control on ground
				else
					m_velocity.setX(m_velocity.getX() + 0.1); // bad control in air
			}
			else if (m_velocity.getX() > 15)
			{
				m_velocity.setX(m_velocity.getX() - 0.1);
			}
		}
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))//	std::cout << "Key down left key detected " << "\n";
		{
			if (m_velocity.getX() > 0) // if moving to the right
			{
				m_velocity.setX(m_velocity.getX() - 1); // move quickly the opposite direction (put on the brakes)
			}
			else if (m_velocity.getX() > -15) // Max velocity of 5 to the left
			{
				if (!jumping)
					m_velocity.setX(m_velocity.getX() - 0.2); // good control on ground
				else
					m_velocity.setX(m_velocity.getX() - 0.1); // bad control in air
			}
			else if (m_velocity.getX() < -15)
			{
				m_velocity.setX(m_velocity.getX() + 0.1);
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
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN))
		{
			//Does nothing yet
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_X)) // **replace (0,0) with joystick for each player
		{
			if (dash_available && jumping)
			{
				if (m_velocity.getX() > 0) // if moving to the right
				{
					m_velocity.setX(20);
				}
				else if (m_velocity.getX() < 0) //
				{
					m_velocity.setX(-20);
				}
				dash_available = false;
				if (TheGame::Instance()->SFXOn)
					Mix_PlayChannel(-1, TheGame::Instance()->gDashFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
			}
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z)) // **replace (0,0) with joystick for each player
		{
			extending = true;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z) == false)
		{
			extending = false;
			hooked = false;

		}
		//Hook direction tracking

		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false && extending)
		{	//Aiming Top only
			grapplePoint->y -= hookExtendSpeed; //Update
												//desiredX = m_velocity.m_x;
			desiredY = -pullPlayerSpeed;
			//set hook angle 
			hookAngle = 270;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false && extending)
		{	//Aiming TopRight only
			grapplePoint->x += hookExtendSpeed;
			grapplePoint->y -= hookExtendSpeed;

			desiredX = pullPlayerSpeed;
			desiredY = -pullPlayerSpeed;

			//set hook angle 
			hookAngle = 315;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false && extending)
		{	//Aiming Right only
			grapplePoint->x += hookExtendSpeed;
			desiredX = pullPlayerSpeed;
			//desiredY = m_velocity.m_y;
			//set hook angle 
			hookAngle = 0;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) && extending)
		{	//Aiming bottomRight only
			grapplePoint->x += hookExtendSpeed;
			grapplePoint->y += hookExtendSpeed;

			desiredX = pullPlayerSpeed;
			desiredY = pullPlayerSpeed;
			//set hook angle 
			hookAngle = 45;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) && extending)
		{	//Aiming bottom only
			grapplePoint->y += hookExtendSpeed;

			//desiredX = m_velocity.m_x;
			desiredY = pullPlayerSpeed;
			//set hook angle 
			hookAngle = 90;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) && extending)
		{	//Aiming bottom left only
			grapplePoint->x -= hookExtendSpeed;
			grapplePoint->y += hookExtendSpeed;

			desiredX = -pullPlayerSpeed;
			desiredY = pullPlayerSpeed;
			//set hook angle 
			hookAngle = 135;

		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false && extending)
		{	//Aiming  left only
			grapplePoint->x -= hookExtendSpeed;

			desiredX = -pullPlayerSpeed;
			//desiredY = m_velocity.m_y;
			//set hook angle 
			hookAngle = 180;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false && extending)
		{	//Aiming  top left only
			grapplePoint->x -= hookExtendSpeed;
			grapplePoint->y -= hookExtendSpeed;

			desiredX = -pullPlayerSpeed;
			desiredY = -pullPlayerSpeed;
			//set hook angle 
			hookAngle = 225;
		}
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
	if (TheGame::Instance()->SFXOn)
		Mix_PlayChannel(-1, TheGame::Instance()->gDieFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
	m_position.setX(start_posX);
	m_position.setY(start_posY);
	m_velocity.setX(0);
	m_velocity.setY(0);
	alive = true;
}
bool Player::didHookHitPlatform(SDLGameObject *r)
{

	if ((grapplePoint->x >= r->getPos().getX()) &&
		(grapplePoint->x < (r->getPos().getX() + r->getWidth())) &&
		(grapplePoint->y >= r->getPos().getY()) &&
		(grapplePoint->y < (r->getPos().getY() + r->getHeight())))
	{
		hooked = true;
		return true;
	}
	else return false;
}

void Player::applyForce(int x, int y)
{
	m_velocity.setX(x);
	m_velocity.setY(y);
}
