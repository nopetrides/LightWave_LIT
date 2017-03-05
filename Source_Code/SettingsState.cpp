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

void SettingsState::s_SFXToggle()
{
	if (TheGame::Instance()->SFXOn)
	{
		TheGame::Instance()->SFXOn = false;
	}
	else
	{
		TheGame::Instance()->SFXOn = true;
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
	if (!TheTextureManager::Instance()->load("assets/Title.png",
		"title", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/ReturnButton.png",
		"resumebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/togglebutton.png",
		"togglebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/SFXtogglebutton.png",
		"SFXtogglebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* title = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 325, TheGame::Instance()->screen_height / 2 - 400, 650, 106, "title"), s_title);

	GameObject* button1 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "togglebutton"), s_Toggle);

	GameObject* button2 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 + 114,
		502, 152, "resumebutton"), s_PreviousMenu);

	GameObject* button3 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2, TheGame::Instance()->screen_height / 2 - 228,
		240, 290, "SFXtogglebutton"), s_SFXToggle);

	m_gameObjects.push_back(title);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);

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

	TheTextureManager::Instance()->clearFromTextureMap("SFXtogglebutton");

	TheTextureManager::Instance()->clearFromTextureMap("title");

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting SettingsState\n";
	return true;
}

void SettingsState::s_title()
{
	std::cout << "Easter egg?\n";
}