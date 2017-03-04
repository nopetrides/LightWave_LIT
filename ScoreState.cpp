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
	//TheGame::Instance()->p_Timer->draw(TheGame::Instance()->getRenderer(), screen_width / 3, screen_height / 6., 650, 100);
	drawCurrentScore(TheGame::Instance()->getRenderer(), screen_width / 3, 0, 650, 150);
	drawHighScore(TheGame::Instance()->getRenderer(), screen_width / 3, 200, 650, 150);
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


	getTimeFromFile();
	prepareHighScore();
	prepareCurrentScore();
	if (playerTimeAsInt / 1000 < lowestTime)
		writeHighScoreToFile();

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

void ScoreState::prepareCurrentScore()
{

	currentScore << "Your time was: " << TheGame::Instance()->p_Timer->getTicks() / 1000.f;
	//Checl to see if the string stream is empty. 
	if (currentScore.rdbuf()->in_avail() > 0)
		currentScoreSurface = TTF_RenderText_Solid(TheGame::Instance()->p_Timer->myFont, currentScore.str().c_str(), TheGame::Instance()->p_Timer->white);

	currentScoreTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), currentScoreSurface);
	SDL_FreeSurface(currentScoreSurface); // Free the surface

										  /*TheGame::Instance()->p_Timer->p_Time = TTF_RenderText_Solid(TheGame::Instance()->p_Timer->myFont, currentScore.str().c_str(), TheGame::Instance()->p_Timer->white);
										  TheGame::Instance()->p_Timer->p_Texture = SDL_CreateTextureFromSurface(renderer, TheGame::Instance()->p_Timer->p_Time);
										  SDL_FreeSurface(TheGame::Instance()->p_Timer->p_Time); // Free the surface*/


}
void ScoreState::drawCurrentScore(SDL_Renderer* renderer, int x, int y, int w, int h)
{
	SDL_Rect destRect;
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, currentScoreTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
void ScoreState::getTimeFromFile()
{

	std::string temp;
	std::ifstream file;
	if (TheGame::Instance()->levelPreviouslyPlayed == 1)
	{
		file.open("level1.txt");
	}
	else if (TheGame::Instance()->levelPreviouslyPlayed == 2)
	{
		file.open("level2.txt");
	}
	else if (TheGame::Instance()->levelPreviouslyPlayed == 3)
	{
		file.open("level3.txt");
	}

	

	if (file.is_open())
	{
		while (file.good())
		{
			while (std::getline(file, temp))
			{
				file >> temp;
			}
			file.close();

			lowestTime = atoi(temp.c_str());

			std::string temp2;
			temp2 = currentScore.str();

			playerTimeAsInt = TheGame::Instance()->p_Timer->getTicks();

			std::cout << "Lowest Time: " << lowestTime << "\n";
			std::cout << "playTimeAsInt: " << playerTimeAsInt << "\n";


		}
	}
	else std::cout << "Unable to open file.txt.\n";
	


}
bool ScoreState::playerTimeIsLower()
{
	if (playerTimeAsInt < lowestTime)
		return true;
	else
		return false;
}

void ScoreState::prepareHighScore()
{

	if ((playerTimeAsInt / 1000) < lowestTime)
	{
		//highScore.precision(1);
		//this means we want to render the layerTimeAsInt in the highscore area. 
		highScore << "Best time is: " << playerTimeAsInt / 1000.f;
		//Checl to see if the string stream is empty. 
		if (highScore.rdbuf()->in_avail() > 0)
			highScoreSurface = TTF_RenderText_Solid(TheGame::Instance()->p_Timer->myFont, highScore.str().c_str(), TheGame::Instance()->p_Timer->white);
		highScoreTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), highScoreSurface);
		SDL_FreeSurface(highScoreSurface); // Free the surface


	}
	else
	{
		//this means we want to render the layerTimeAsInt in the highscore area. 
		highScore << "Best time is: " << lowestTime;
		//Checl to see if the string stream is empty. 
		if (highScore.rdbuf()->in_avail() > 0)
			highScoreSurface = TTF_RenderText_Solid(TheGame::Instance()->p_Timer->myFont, highScore.str().c_str(), TheGame::Instance()->p_Timer->white);
		highScoreTexture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), highScoreSurface);
		SDL_FreeSurface(highScoreSurface); // Free the surface
	}



}
void ScoreState::drawHighScore(SDL_Renderer* renderer, int x, int y, int w, int h)
{

	SDL_Rect destRect;
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = w;
	srcRect.h = destRect.h = h;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(renderer, highScoreTexture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}
void ScoreState::writeHighScoreToFile()
{

	//Additionally, overwrite the current high score. 
	std::ofstream file;

	if (TheGame::Instance()->levelPreviouslyPlayed == 1)
	{
		file.open("level1.txt");
	}
	else if (TheGame::Instance()->levelPreviouslyPlayed == 2)
	{
		file.open("level2.txt");
	}
	else if (TheGame::Instance()->levelPreviouslyPlayed == 3)
	{
		file.open("level3.txt");
	}

	if (file.is_open())
		file << playerTimeAsInt / 1000;
	file.close();

}