#ifndef SDL_ScoreState_h
#define SDL_ScoreState_h

#include "GameState.h"
//#include "GameObject.h"
#include <vector>
#include "Game.h"
#include <fstream>
#include <iostream>
class GameObject;

class ScoreState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

	int screen_width = TheGame::Instance()->screen_width;
	int screen_height = TheGame::Instance()->screen_height;


	void getTimeFromFile();
	void prepareCurrentScore();
	void drawCurrentScore(SDL_Renderer* renderer, int x, int y, int w, int h);

	bool playerTimeIsLower();
	void prepareHighScore();
	void drawHighScore(SDL_Renderer* renderer, int x, int y, int w, int h);
	void writeHighScoreToFile();
	bool doOonce = false;
	bool doOnce2 = false;
	bool timeRead = false;
	bool playerBeatTime = false;

private:
	static void s_returnToMain();
	static void s_retryPlay();

	static const std::string s_pauseID;
	std::vector<GameObject*> m_gameObjects;

	std::stringstream currentScore;
	std::stringstream highScore;
	int lowestTime;
	int playerTimeAsInt;

	SDL_Texture* highScoreTexture;
	SDL_Surface* highScoreSurface;

	SDL_Texture* currentScoreTexture;
	SDL_Surface* currentScoreSurface;


};

#endif