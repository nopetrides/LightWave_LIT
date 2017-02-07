#ifndef SDL_PlayerSelectState_h
#define SDL_PlayerSelectState_h

#include "GameState.h"
//#include "GameObject.h"
#include <vector>

class GameObject;

class PlayerSelectState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static void s_OnePlayer();
	static void s_TwoPlayer();
	static void s_ThreePlayer();
	static void s_FourPlayer();
	static void s_PreviousMenu();

	static const std::string s_pauseID;
	std::vector<GameObject*> m_gameObjects;

};

#endif
