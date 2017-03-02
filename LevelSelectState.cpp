#include "LevelSelectState.h"
//#include "TextureManager.h"
#include "Game.h"
//#include "Player.h"
#include "MenuButton.h"
#include "PlayState.h"

const std::string LevelSelectState::s_pauseID = "PAUSE";

void LevelSelectState::s_LevelOne()
{
	TheGame::Instance()->level = 1;
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
void LevelSelectState::s_LevelTwo()
{
	TheGame::Instance()->level = 2;
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
void LevelSelectState::s_LevelThree()
{
	TheGame::Instance()->No();
	/*
	TheGame::Instance()->level = 3;
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	*/
}
void LevelSelectState::s_LevelFour()
{
	TheGame::Instance()->No();
	/*
	TheGame::Instance()->level = 4;
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	*/
}
void LevelSelectState::s_LevelFive()
{
	TheGame::Instance()->No();
	/*
	TheGame::Instance()->level = 5;
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	*/
}



void LevelSelectState::s_PreviousMenu()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void LevelSelectState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void LevelSelectState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool LevelSelectState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/Title.png", "gameTitle", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/ReturnButton.png",
		"backbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/Level_1.png",
		"level1button", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Level_2.png",
		"level2button", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Level_3.png",
		"level3button", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Level_4.png",
		"level4button", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/Level_5.png",
		"level5button", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 620, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "level1button"), s_LevelOne);
	GameObject* button2 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 370, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "level2button"), s_LevelTwo);
	GameObject* button3 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 120, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "level3button"), s_LevelThree);
	GameObject* button4 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 + 130, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "level4button"), s_LevelFour);
	GameObject* button5 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 + 380, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "level5button"), s_LevelFive);

	GameObject* button6 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 + 114,
		502, 152, "backbutton"), s_PreviousMenu);

	GameObject* title = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 325, TheGame::Instance()->screen_height / 2 - 400, 650, 106, "gameTitle"), s_title);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);
	m_gameObjects.push_back(button4);
	m_gameObjects.push_back(button5);
	m_gameObjects.push_back(button6);
	m_gameObjects.push_back(title);

	std::cout << "entering LevelSelectState\n";

	return true;
}

bool LevelSelectState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("backbutton");

	
	TheTextureManager::Instance()->clearFromTextureMap("level1button");
	TheTextureManager::Instance()->clearFromTextureMap("level2button");
	TheTextureManager::Instance()->clearFromTextureMap("level3button");
	TheTextureManager::Instance()->clearFromTextureMap("level4button");
	TheTextureManager::Instance()->clearFromTextureMap("level5button");
	TheTextureManager::Instance()->clearFromTextureMap("gameTitle");

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting LevelSelectState\n";
	return true;
}

void LevelSelectState::s_title()
{
	std::cout << "Easter egg?\n";
}