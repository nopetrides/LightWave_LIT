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
	if(!TheTextureManager::Instance()->load("assets/playbutton.png","playbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("assets/optionbutton.png", "optionbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if(!TheTextureManager::Instance()->load("assets/quitbutton.png","quitbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(250, 25, 120, 145, "playbutton"),s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(250, 175, 120, 145, "optionbutton"), s_settingsMenu);
	GameObject* button3 = new MenuButton(new LoaderParams(250, 325, 120, 145, "quitbutton"),s_exitFromMenu);

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