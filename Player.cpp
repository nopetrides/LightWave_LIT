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
	if (extending && !hooked)
	{
		if (hookLength < maxHookDistance)
			hookLength += hookExtendSpeed;
		else if (hookLength > maxHookDistance)
			extending = false;

		//Adjust midPoint for camera position
		midpointX -= getCamX();
		midpointY -= getCamY();

		TextureManager::Instance()->draw("hook", midpointX, midpointY, hookLength, 10,
			TheGame::Instance()->getRenderer(), SDL_FLIP_NONE, rotationPoint, hookAngle);

		//Adjust midPoint for camera position
		midpointX += getCamX();
		midpointY += getCamY();
	}
	else if (hookLength >= 0)
	{
		hookLength -= hookExtendSpeed;

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
	if (!extending)
	{
		grapplePoint->x = midpointX;
		grapplePoint->y = midpointY;

		desiredX = NULL;
		desiredY = NULL;
		//hookLength = 0;
	}
	if (m_velocity.m_x  >0 || m_velocity.m_x < 0)
	{
		m_currentRow = 1;
		m_currentFrame = int(((SDL_GetTicks() / 50) % 7)); // Running animation
	}
	else if (m_velocity.m_x == 0)
	{
		m_currentRow = 2;
		m_currentFrame = int(((SDL_GetTicks() / 300) % 7)); // Idle anim

	}
	if (m_velocity.m_y != 0)
	{
		m_currentRow = 3;
		m_currentFrame = int(((SDL_GetTicks() / 50) % 7)); // Idle anim
	}

	if (m_velocity.getY() == 0 && m_velocity.getX() != 0)
	{
		if (TheGame::Instance()->SFXOn)
		{
			if (!Mix_Playing(0))
				Mix_PlayChannel(0, TheGame::Instance()->gWalkFX, 0); // ** PLAY SFX/SOUND BYTE
		}
	}
	handleInput();

	SDLGameObject::update();
	if (m_velocity.getY() > 0)
	{
		jumping = true;
	}
	if (m_position.getY() > TheGame::Instance()->level_height)
	{
		alive = false;

	}

	midpointX = m_position.m_x + (m_width / 2);
	midpointY = m_position.m_y + (m_height / 2);

	//dist =  sqrt (( deltaX)^2 - (deltaY)^2)
	float deltaX = (grapplePoint->x - midpointX);
	float deltaY = (grapplePoint->y - midpointY);

	grapplePointDistance = sqrtf((deltaX*deltaX) + (deltaY*deltaY));
	std::cout << "Grapple Point Distance: " << grapplePointDistance << std::endl;
	
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
	
	if (TheInputHandler::Instance()->joysticksInitialised()) { // Check if joystick is initialised
		if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_V) == false && TheInputHandler::Instance()->getButtonState(0, 6) == false) && TheGame::Instance()->HotReload)
		{
			TheGame::Instance()->HotReload = false;
		}
		if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_V) || TheInputHandler::Instance()->getButtonState(0, 6)) && TheGame::Instance()->HotReload == false)
		{
			TheGame::Instance()->changeToPlay();
			TheGame::Instance()->HotReload = true;
		}
		
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) || TheInputHandler::Instance()->getButtonState(0, 0) || TheInputHandler::Instance()->getButtonState(0, 4)) // **replace (0,0) with joystick for each player
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
			facingRight = true;
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
			facingRight = false;
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
			if (!hookpressed)
			{
				extending = true;
				timeHookUsed = SDL_GetTicks();
				hookpressed = true;
			}
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z) == false && TheInputHandler::Instance()->getButtonState(0, 5) == false)
		{
			if (hookpressed) {
				extending = false;
				hookpressed = false;
			}
			hooked = false;
		}
		//Hook direction tracking
		if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) < 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) > 0) && extending && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming TopRight only
				grapplePoint->x += hookExtendSpeed;
				grapplePoint->y -= hookExtendSpeed;

				desiredX = pullPlayerSpeed;
				desiredY = -pullPlayerSpeed;

				//set hook angle 
				hookAngle = 315;
			}
		}			
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0 &&
			TheInputHandler::Instance()->getAxisX(0, 2) > 0) && extending && jumping && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming bottomRight only
				grapplePoint->x += hookExtendSpeed;
				grapplePoint->y += hookExtendSpeed;

				desiredX = pullPlayerSpeed;
				desiredY = pullPlayerSpeed;
				//set hook angle 
				hookAngle = 45;
			}
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) > 0) && extending && !hooked)
		{
			extending = false;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisX(0, 2) > 0) && extending && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming Right only
				grapplePoint->x += hookExtendSpeed;
				desiredX = pullPlayerSpeed;
				//desiredY = m_velocity.m_y;
				//set hook angle 
				hookAngle = 0;
			}
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) < 0) && extending && jumping && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming bottom left only
				grapplePoint->x -= hookExtendSpeed;
				grapplePoint->y += hookExtendSpeed;

				desiredX = -pullPlayerSpeed;
				desiredY = pullPlayerSpeed;

				//set hook angle 
				hookAngle = 135;
			}

		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) < 0) && extending && !hooked)
		{
			extending = false;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0) && extending && jumping && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming bottom only
				grapplePoint->y += hookExtendSpeed;

				//desiredX = m_velocity.m_x;
				desiredY = pullPlayerSpeed;

				//set hook angle 
				hookAngle = 90;
			}
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) > 0) && extending && !hooked)
		{
			extending = false;
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) < 0 &&
				TheInputHandler::Instance()->getAxisX(0, 2) < 0) && extending && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming  top left only
				grapplePoint->x -= hookExtendSpeed;
				grapplePoint->y -= hookExtendSpeed;

				desiredX = -pullPlayerSpeed;
				desiredY = -pullPlayerSpeed;

				//set hook angle 
				hookAngle = 225;
			}
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisX(0, 2) < 0) && extending && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming  left only
				grapplePoint->x -= hookExtendSpeed;

				desiredX = -pullPlayerSpeed;
				//desiredY = m_velocity.m_y;

				//set hook angle 
				hookAngle = 180;
			}
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) ||
			(TheInputHandler::Instance()->getAxisY(0, 2) < 0) && extending && !hooked)
		{
			if (grapplePointDistance <= maxHookDistance)
			{
				//Aiming Top only
				grapplePoint->y -= hookExtendSpeed; //Update
													//desiredX = m_velocity.m_x;
				desiredY = -pullPlayerSpeed;
				//set hook angle 
				hookAngle = 270;
			}
		}
		else
		{
			extending = false;
		}
	}
	else
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_V) == false && TheGame::Instance()->HotReload)
		{
			TheGame::Instance()->HotReload = false;
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_V) && TheGame::Instance()->HotReload == false)
		{
			TheGame::Instance()->changeToPlay();
			TheGame::Instance()->HotReload = true;
		}
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
				if (TheGame::Instance()->SFXOn)
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
			facingRight = true;
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
			facingRight = false;
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
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z))
		{
			if (!hookpressed)
			{
				extending = true;
				timeHookUsed = SDL_GetTicks();
				hookpressed = true;
			}
		}
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_Z) == false)
		{
			if (hookpressed) {
				extending = false;
				hookpressed = false;
			}
			hooked = false;
		}
		//Hook direction tracking

		if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) && extending && !hooked)
		{
			if (grapplePointDistance < maxHookDistance)
			{
				//Aiming Top only
				grapplePoint->y -= hookExtendSpeed; //Update
													//desiredX = m_velocity.m_x;
				desiredY = -pullPlayerSpeed;
				//set hook angle 
				hookAngle = 270;
			}
		}
		else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
			TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) && extending && !hooked)
		{
			if (grapplePointDistance < maxHookDistance)
			{//Aiming TopRight only
				grapplePoint->x += hookExtendSpeed;
				grapplePoint->y -= hookExtendSpeed;

				desiredX = pullPlayerSpeed;
				desiredY = -pullPlayerSpeed;

				//set hook angle 
				hookAngle = 315;
			}
		}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) && extending && !hooked)
			{
				if (grapplePointDistance < maxHookDistance)
				{
					//Aiming Right only
					grapplePoint->x += hookExtendSpeed;
					desiredX = pullPlayerSpeed;
					//desiredY = m_velocity.m_y;
					//set hook angle 
					hookAngle = 0;
				}
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) && extending && jumping && !hooked)
			{
				if (grapplePointDistance < maxHookDistance)
				{
					//Aiming bottomRight only
					grapplePoint->x += hookExtendSpeed;
					grapplePoint->y += hookExtendSpeed;

					desiredX = pullPlayerSpeed;
					desiredY = pullPlayerSpeed;
					//set hook angle 
					hookAngle = 45;
				}
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) && extending && !hooked)
			{
				extending = false;
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) && extending && jumping && !hooked)
			{
				if (grapplePointDistance < maxHookDistance)
				{
					//Aiming bottom only
					grapplePoint->y += hookExtendSpeed;

					//desiredX = m_velocity.m_x;
					desiredY = pullPlayerSpeed;
					//set hook angle 
					hookAngle = 90;
				}
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) && extending && !hooked)
			{
				extending = false;
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) && extending && jumping && !hooked)
			{
				if (grapplePointDistance < maxHookDistance)
				{
					//Aiming bottom left only
					grapplePoint->x -= hookExtendSpeed;
					grapplePoint->y += hookExtendSpeed;

					desiredX = -pullPlayerSpeed;
					desiredY = pullPlayerSpeed;
					//set hook angle 
					hookAngle = 135;
				}
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F)) && extending && !hooked)
			{
				extending = false;
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) && extending && !hooked)
			{
				if (grapplePointDistance < maxHookDistance)
				{//Aiming  left only
					grapplePoint->x -= hookExtendSpeed;

					desiredX = -pullPlayerSpeed;
					//desiredY = m_velocity.m_y;
					//set hook angle 
					hookAngle = 180;
				}
			}
			else if ((TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_R) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_G) == false &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_D) &&
				TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_F) == false) && extending && !hooked)
			{
				if (grapplePointDistance < maxHookDistance)
				{
					//Aiming  top left only
					grapplePoint->x -= hookExtendSpeed;
					grapplePoint->y -= hookExtendSpeed;

					desiredX = -pullPlayerSpeed;
					desiredY = -pullPlayerSpeed;
					//set hook angle 
					hookAngle = 225;
				}
			}
			else
			{
				extending = false;
			}
		}
	}

void Player::respawn()
{
	if (TheGame::Instance()->SFXOn)
		Mix_PlayChannel(-1, TheGame::Instance()->gDieFX, 0); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
	m_position.setX(start_posX);
	m_position.setY(start_posY);
	m_velocity.setX(0);
	m_velocity.setY(0);
	grapplePoint->x = midpointX;
	grapplePoint->y = midpointY;
	extending = false;
	hooked = true;

	alive = true;
}
bool Player::didHookHitPlatform(SDLGameObject *r)
{

	if ((grapplePoint->x >= r->getPos().getX()) &&
		(grapplePoint->x < (r->getPos().getX() + r->getWidth())) &&
		(grapplePoint->y >= r->getPos().getY()) &&
		(grapplePoint->y < (r->getPos().getY() + r->getHeight())) && hooked == false)
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