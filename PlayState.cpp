#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Platform.h"
#include "PauseState.h"
#include "Level_One.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PlayState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (TheGame::Instance()->level == 1)
	{
		Level_One* level = new Level_One();
		level->loadTextures();
		level->createObjects(&m_gameObjects);
	}

	if(!TheTextureManager::Instance()->load("assets/player-animate-corrected.png","player", TheGame::Instance()->getRenderer()))
	{
	return false;
	}

	/*if (!TheTextureManager::Instance()->load("assets/platform.png", "platform", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/street.png", "BG", TheGame::Instance()->getRenderer()))
	{
		return false;
	}*/

	GameObject* player = new Player(new LoaderParams(100, 100, 71,65, "player"));
	m_gameObjects.push_back(player);


	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("player");
	TheTextureManager::Instance()->clearFromTextureMap("platform");
	TheTextureManager::Instance()->clearFromTextureMap("BG");
	std::cout << "exiting PlayState\n";
	return true;
}
void PlayState::PlayerCollisionAgainstPlatforms(Player player, SDLGameObject* p)
{	//Chris
	//First compare each platform's X position to the players and only check if the 
	//platform is within a certain range. Doing this so we only do 1 check instead
	//of 6+ every frame on every platform. 

	int playerTop = player.getPos().getY(); // Top of the player Rect
	int playerBottom = player.getPos().getY() + player.getHeight(); // Bottom of the player Rect
	int playerLeft = player.getPos().getX(); // Left of the player Rect 
	int playerRight = player.getPos().getX() + player.getWidth(); // Right of the player Rect
	int playerMidPoint = player.getWidth() / 2;

	int platformTop = NULL;
	int platformBottom = NULL;
	int platformLeft = NULL;
	int platformRight = NULL;

	std::vector<GameObject*>::const_iterator iter; // Create iterator to loop through the list with


		//calculate distance from player to platform
	int dist = sqrt((player.getPos().getX() - p->getPos().getX()) + (player.getPos().getY() - p->getPos().getY)); //p->getX()) + (getY() - p->getY()));
		//int dist = sqrt((getX() - p->getX()) + (getY() - p->getY()));

		// If player is close enough to platform, check all collisions
		if (dist <= considerForCollision)
		{
			//Calculate top, bottom, left and right of platform
			platformTop = p->getPos().getY(); // Top of the platform Rect
			platformBottom = p->getPos().getY() + p->getHeight(); // Bottom of the platform Rect
			platformLeft = p->getPos().getX(); // Left of the platform Rect 
			platformRight = p->getPos().getX() + p->getWidth(); // Right of the platform Rect

															 //Player on top of platform check
			if (playerBottom <= platformTop
				&& playerTop >= (platformTop - player.getHeight() - collideDistance)
				&& playerMidPoint >= platformLeft
				|| playerMidPoint <= platformRight)
			{
				// set the player on top of the platform
				player.collideBottom(p);
			}

			//player bumps head to bottom of platform
			if (playerTop >= platformBottom
				&& playerBottom <= (platformTop + player.getHeight() + collideDistance)
				&& playerMidPoint >= platformLeft
				|| playerMidPoint <= platformRight)
			{
				player.collideTop();
			}

			//Player bumps into left side of platform check
			if (playerRight <= platformLeft
				&& playerLeft >= (platformLeft - player.getWidth() - collideDistance)
				&& playerBottom >= platformTop
				|| playerTop <= platformBottom)
			{
				player.collideRight(p); // limit the players x movement because of collision
			}

			//Player bumps into right side of platform check
			if (playerLeft >= platformRight
				&& playerRight <= (platformRight + player.getWidth() + collideDistance)
				&& playerBottom >= platformTop
				|| playerTop <= platformBottom)
			{
				player.collideLeft(p); // limit the players x movement because of collision
			}


		}

	}


