#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "Platform.h"
#include "PauseState.h"

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
	if(!TheTextureManager::Instance()->load("assets/player-animate-corrected.png","player", TheGame::Instance()->getRenderer()))
	{
	return false;
	}

	if (!TheTextureManager::Instance()->load("assets/platform.png", "platform", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/street.png", "BG", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* player = new Player(new LoaderParams(100, 100, 71,65, "player"));
	GameObject* platform = new Platform(new LoaderParams(100, 100, 100, 40, "platform"));
	GameObject* BG = new Platform(new LoaderParams(0, 0, 1000, 300, "BG"));
	m_gameObjects.push_back(BG);
	m_gameObjects.push_back(player);
	m_gameObjects.push_back(platform);

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
