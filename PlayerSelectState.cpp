#include "PlayerSelectState.h"
//#include "TextureManager.h"
#include "Game.h"
//#include "Player.h"
#include "MenuButton.h"
#include "LevelSelectState.h"

const std::string PlayerSelectState::s_pauseID = "PAUSE";

void PlayerSelectState::s_OnePlayer()
{
	TheGame::Instance()->NumPlayers = 1;
	TheGame::Instance()->getStateMachine()->pushState(new LevelSelectState());
}
void PlayerSelectState::s_TwoPlayer()
{
	TheGame::Instance()->NumPlayers = 2;
	TheGame::Instance()->getStateMachine()->pushState(new LevelSelectState());
}
void PlayerSelectState::s_ThreePlayer()
{
	TheGame::Instance()->NumPlayers = 3;
	TheGame::Instance()->getStateMachine()->pushState(new LevelSelectState());
}
void PlayerSelectState::s_FourPlayer()
{
	TheGame::Instance()->NumPlayers = 4;
	TheGame::Instance()->getStateMachine()->pushState(new LevelSelectState());
}

void PlayerSelectState::s_PreviousMenu()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PlayerSelectState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PlayerSelectState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PlayerSelectState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/previousbutton.png",
		"previousbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Players_1.png",
		"onePbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Players_2.png",
		"twoPbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Players_3.png",
		"threePbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Players_4.png",
		"fourPbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(20, 100,
		120, 145, "onePbutton"), s_OnePlayer);
	GameObject* button2 = new MenuButton(new LoaderParams(150, 100,
		120, 145, "twoPbutton"), s_TwoPlayer);
	GameObject* button3 = new MenuButton(new LoaderParams(280, 100,
		120, 145, "threePbutton"), s_ThreePlayer);
	GameObject* button4 = new MenuButton(new LoaderParams(410, 100,
		120, 145, "fourPbutton"), s_FourPlayer);

	GameObject* button5 = new MenuButton(new LoaderParams(200, 300,
		200, 80, "previousbutton"), s_PreviousMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);
	m_gameObjects.push_back(button4);
	m_gameObjects.push_back(button5);

	std::cout << "entering PlayerSelectState\n";

	return true;
}

bool PlayerSelectState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("previousbutton");

	TheTextureManager::Instance()->clearFromTextureMap("onePbutton");
	TheTextureManager::Instance()->clearFromTextureMap("twoPbutton");
	TheTextureManager::Instance()->clearFromTextureMap("threePbutton");
	TheTextureManager::Instance()->clearFromTextureMap("fourPbutton");

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting PlayerSelectState\n";
	return true;
}