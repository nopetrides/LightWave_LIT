#ifndef SDL_PlayState_h
#define SDL_PlayState_h

#include "GameState.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include <vector>
#include "Level_One.h"
#include "Timer.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }
	bool checkForWin(SDL_Rect winLocation, SDLGameObject* player);
	void keepCameraInBounds();
	Level_One* level_one;
	Timer* p_Timer;

	int screen_w = TheGame::Instance()->screen_width;
	int screen_h = TheGame::Instance()->screen_height;
	SDL_Rect * camera = new SDL_Rect { 0,0,screen_w,screen_h };


private:
	static const std::string s_playID;
	std::vector<SDLGameObject*> m_gameObjects;
	std::vector<SDLGameObject*> m_Platforms;
	std::vector<SDLGameObject*> m_Players;
};

#endif