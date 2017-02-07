#include "SettingsState.h"
//#include "TextureManager.h"
#include "Game.h"
//#include "Player.h"
#include "MenuButton.h"
#include "MenuState.h"

const std::string SettingsState::s_pauseID = "PAUSE";

void SettingsState::s_Toggle()
{
	if (TheGame::Instance()->SoundOn)
	{
		TheGame::Instance()->SoundOn = false;
		Mix_PauseMusic();
	}
	else
	{
		TheGame::Instance()->SoundOn = true;
		Mix_ResumeMusic();
	}
}

void SettingsState::s_PreviousMenu()
{
	TheGame::Instance()->getStateMachine()->popState();
}

void SettingsState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}
}

void SettingsState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool SettingsState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/resume.png",
		"resumebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/togglebutton.png",
		"togglebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(200, 100,
		120, 145, "togglebutton"), s_Toggle);

	GameObject* button2 = new MenuButton(new LoaderParams(200, 300,
		200, 80, "resumebutton"), s_PreviousMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "entering SettingsState\n";

	return true;
}

bool SettingsState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("resumebutton");

	TheTextureManager::Instance()->clearFromTextureMap("togglebutton");

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting SettingsState\n";
	return true;
}