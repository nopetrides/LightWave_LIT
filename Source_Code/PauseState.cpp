#include "PauseState.h"
//#include "TextureManager.h"
#include "Game.h"
//#include "Player.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "PlayState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new	MenuState());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void PauseState::update()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	if(!TheTextureManager::Instance()->load("assets/ResumeButton.png",
		"resumebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/RetryButton.png",
		"restartbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if(!TheTextureManager::Instance()->load("assets/MainButton.png",
		"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 - 76, 502, 152, "mainbutton"), s_pauseToMain);

	GameObject* button2 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 - 280, 502, 152, "resumebutton"), s_resumePlay);

	GameObject* button3 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 + 114, 502, 152, "restartbutton"), s_restartPlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);

	std::cout << "entering PauseState\n";

	return true;
}

bool PauseState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

		m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");

	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");

	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting PauseState\n";
	return true;
}