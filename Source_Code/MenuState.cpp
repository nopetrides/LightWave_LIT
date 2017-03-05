#include "MenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "SettingsState.h"
#include "PlayerSelectState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update()
{
	
	for(int i = 0; i < m_gameObjects.size(); i++) //page 112
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	
	//page 112
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

}

bool MenuState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/Title.png", "Title", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/StartButton.png","playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/OptionsButton.png", "optionbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/ExitButton.png","quitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* title = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 325, TheGame::Instance()->screen_height / 2 - 400, 650, 106, "Title"), s_title);
	GameObject* button1 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width /2 - 250, TheGame::Instance()->screen_height /2 - 280, 502, 152, "playbutton"),s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width /2 - 250, TheGame::Instance()->screen_height /2 - 76, 502, 152, "optionbutton"), s_settingsMenu);
	GameObject* button3 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width /2 - 250, TheGame::Instance()->screen_height /2 + 114, 502, 152, "quitbutton"),s_exitFromMenu);

	m_gameObjects.push_back(title);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	m_gameObjects.push_back(button3);

	if (TheGame::Instance()->SoundOn) {
		Mix_PlayMusic(TheGame::Instance()->gMusic, -1); // ** START BGM, the '-1' means it will loop ad inifitum
		//SDL_Delay(5000); // ** NOTE THAT DELAYS DO NOT PAUSE SOUND FX OR MUSIC, AS THEY ARE RUNNING ON A THREAD (?)
	}
	
	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	for(int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("optionbutton");
	TheTextureManager::Instance()->clearFromTextureMap("quitbutton");
	TheTextureManager::Instance()->clearFromTextureMap("Title");
	

	std::cout << "exiting MenuState\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked\n";
	//TheGame::Instance()->getStateMachine()->changeState(new PlayState());
	TheGame::Instance()->getStateMachine()->pushState(new PlayerSelectState());
}

void MenuState::s_settingsMenu()
{
	std::cout << "Settings button clicked\n";
	TheGame::Instance()->getStateMachine()->pushState(new SettingsState());
}

void MenuState::s_exitFromMenu()
{
	std::cout << "Quit button clicked\n";
	TheGame::Instance()->quit();
}

void MenuState::s_title()
{
	std::cout << "Easter egg?\n";
}