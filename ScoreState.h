#ifndef SDL_ScoreState_h
#define SDL_ScoreState_h

#include "GameState.h"
//#include "GameObject.h"
#include <vector>

class GameObject;

class ScoreState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static void s_returnToMain();
	static void s_retryPlay();

	static const std::string s_pauseID;
	std::vector<GameObject*> m_gameObjects;

};

#endif