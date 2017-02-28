#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Platform.h"
#include "PauseState.h"
#include "Level_One.h"
#include "MenuState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	std::vector<GameObject*>::iterator myIter;

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	for (myIter = m_gameObjects.begin(); myIter != m_gameObjects.end(); myIter++)
	{
		(*myIter)->update();
	}

	for (int i = 0; i < m_Platforms.size(); i++)
	{
		m_Players[0]->PlayerCollisionAgainstPlatforms(m_Platforms[i]);
	}

	if (checkForWin(level_one->getWinLocation(), m_Players[0]))
	{
		TheGame::Instance()->getStateMachine()->changeState(new MenuState());
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/player-animate-corrected.png", "player", TheGame::Instance()->getRenderer()))
	{
		return false;
	}


	//Determine what level, and load it's stuff. Might move all this out to a function

	if (TheGame::Instance()->level == 1)
	{
		//chris
		//test and instantiate correct level. 
		//load objects and textures
		level_one = new Level_One();
		level_one->loadTextures();
		level_one->createObjects(&m_gameObjects, &m_Platforms);

		//Setting the win location, this isn't "linked" to the winning platform, 
		// Just hardcoded to be above it. 
		//Height is 71 because our sprite height is 71 pixels. 
		// Y is 250 - 71 = 179. 
		//250 is the win platforms Y. 
		//Width is 110 just for some extra room. 


		level_one->setWinLocation(500, 179, 110, 71);
		//(500, 250, 100, 50, "platform"));
	}

	SDLGameObject* player = new Player(new LoaderParams(100, 100, 71, 65, "player"));
	m_gameObjects.push_back(player);
	m_Players.push_back(player);

	std::cout << "entering PlayState\n";
	return true;
}

bool PlayState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
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

bool PlayState::checkForWin(SDL_Rect winLocation, SDLGameObject* player)
{
	//Chris
	// Checking to see if the passed in SDLGameObject (assuming it's a player)
	// is within the bounds of the SDL_rect passed in. Each level will provide 
	// a SDLRect win location through a return function. ie return winLocation;

	//Create vars for easier readability. 
	int playerTop = player->getPos().m_y; // Top of the player Rect
	int playerBottom = player->getPos().m_y + player->getHeight(); // Bottom of the player Rect
	int playerLeft = player->getPos().m_x; // Left of the player Rect 
	int playerRight = player->getPos().m_x + player->getWidth(); // Right of the player Rect
	int playerMidPoint = player->getPos().m_x + (player->getWidth() / 2); // Mid point of player-> 
	int playerHeight = player->getHeight();
	int playerWidth = player->getWidth();

	if (playerLeft >= winLocation.x && playerRight <= (winLocation.x + winLocation.w) &&
		playerTop >= winLocation.y && playerBottom <= (winLocation.y + winLocation.h))
	{
		//player is within x range of rect, now check the y range
		std::cout << "Win location.\n";
		return true; // Player is within the Rect. 
	}
	else
		return false;

}