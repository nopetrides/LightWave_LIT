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
	prepareToShowScore(TheGame::Instance()->getRenderer());
}

void ScoreState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	TheGame::Instance()->p_Timer->draw(TheGame::Instance()->getRenderer(), screen_width / 3, 10, 650, 250);
}

bool ScoreState::onEnter()
{
	if (!TheTextureManager::Instance()->load("assets/RetryButton.png",
		"retrybutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("assets/MainButton.png",
		"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 - 76, 502, 152, "mainbutton"), s_returnToMain);

	GameObject* button2 = new MenuButton(new LoaderParams(TheGame::Instance()->screen_width / 2 - 250, TheGame::Instance()->screen_height / 2 + 114, 502, 152, "retrybutton"), s_retryPlay);

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
	TheTextureManager::Instance()->clearFromTextureMap("retrybutton");

	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");

	// reset the mouse button states to false
	TheInputHandler::Instance()->reset();
	std::cout << "exiting ScoreState\n";
	return true;
}
void ScoreState::prepareToShowScore(SDL_Renderer* renderer)
{
	if (!doOonce)
	{
		std::stringstream currentScore;
		
		currentScore << "Your time was: " << TheGame::Instance()->p_Timer->getTicks() / 1000.f;
		//Checl to see if the string stream is empty. 
		if (currentScore.rdbuf()->in_avail() > 0)
			TheGame::Instance()->p_Timer->p_Time = TTF_RenderText_Solid(TheGame::Instance()->p_Timer->myFont, currentScore.str().c_str(), TheGame::Instance()->p_Timer->white);
		TheGame::Instance()->p_Timer->p_Texture = SDL_CreateTextureFromSurface(renderer, TheGame::Instance()->p_Timer->p_Time);
		SDL_FreeSurface(TheGame::Instance()->p_Timer->p_Time); // Free the surface
		doOonce = true;
	}

}