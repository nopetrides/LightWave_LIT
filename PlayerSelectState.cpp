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
	TheGame::Instance()->No();
	/*
	TheGame::Instance()->NumPlayers = 2;
	TheGame::Instance()->getStateMachine()->pushState(new LevelSelectState());
	*/
}
void PlayerSelectState::s_ThreePlayer()
{
	TheGame::Instance()->No();
	/*
	TheGame::Instance()->NumPlayers = 3;
	TheGame::Instance()->getStateMachine()->pushState(new LevelSelectState());
	*/
}
void PlayerSelectState::s_FourPlayer()
{
	TheGame::Instance()->No();
	/*
	TheGame::Instance()->NumPlayers = 4;
	TheGame::Instance()->getStateMachine()->pushState(new LevelSelectState());
	*/
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
	if (!TheTextureManager::Instance()->load("assets/Title.png", "gametitle", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/ReturnButton.png",
		"previousbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/1_Player.png",
		"onePbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/2_Player.png",
		"twoPbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/3_Player.png",
		"threePbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/4_Player.png",
		"fourPbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 500, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "onePbutton"), s_OnePlayer);
	GameObject* button2 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "twoPbutton"), s_TwoPlayer);
	GameObject* button3 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "threePbutton"), s_ThreePlayer);
	GameObject* button4 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 + 250, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "fourPbutton"), s_FourPlayer);

	GameObject* button5 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 + 114,
		502, 152, "previousbutton"), s_PreviousMenu);

	GameObject* title = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 325, TheGame::Instance()->screen_height / 2 - 400, 650, 106, "gametitle"), s_title);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);
	m_gameObjects.push_back(button4);
	m_gameObjects.push_back(button5);
	m_gameObjects.push_back(title);

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
	TheTextureManager::Instance()->clearFromTextureMap("gametitle");

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting PlayerSelectState\n";
	return true;
}

void PlayerSelectState::s_title()
{
	std::cout << "Easter egg?\n";
}