#include "ScoreState.h"
//#include "TextureManager.h"
#include "Game.h"
//#include "Player.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"

const std::string ScoreState::s_pauseID = "PAUSE";

void ScoreState::s_returnToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new	MenuState());
}

void ScoreState::s_retryPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new	PlayState());
}

void ScoreState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void ScoreState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool ScoreState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/restart.png",
		"resumebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/main.png",
		"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(50, 300,
		200, 80, "mainbutton"), s_returnToMain);

	GameObject* button2 = new MenuButton(new LoaderParams(300, 300,
		200, 80, "resumebutton"), s_retryPlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering ScoreState\n";

	return true;
}

bool ScoreState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");

	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting ScoreState\n";
	return true;
}