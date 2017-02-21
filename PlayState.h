#ifndef SDL_PlayState_h
#define SDL_PlayState_h

#include "GameState.h"
#include "GameObject.h"
#include "SDLGameObject.h"
#include <vector>
#include "Level_One.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }
	bool checkForWin(SDL_Rect winLocation, SDLGameObject* player);
	Level_One* level_one;


private:
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;
	std::vector<SDLGameObject*> m_Platforms;
	std::vector<SDLGameObject*> m_Players;
};

#endif