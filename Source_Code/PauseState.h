#ifndef SDL_PauseState_h
#define SDL_PauseState_h

#include "GameState.h"
//#include "GameObject.h"
#include <vector>

class GameObject;

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static void s_pauseToMain();
	static void s_resumePlay();
	static void s_restartPlay();

	static const std::string s_pauseID;
	std::vector<GameObject*> m_gameObjects;

};

#endif