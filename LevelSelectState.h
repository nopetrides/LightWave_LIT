#ifndef SDL_LevelSelectState_h
#define SDL_LevelSelectState_h

#include "GameState.h"
//#include "GameObject.h"
#include <vector>

class GameObject;

class LevelSelectState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static void s_LevelOne();
	static void s_LevelTwo();
	static void s_LevelThree();
	static void s_LevelFour();
	static void s_LevelFive();
	static void s_PreviousMenu();

	static const std::string s_pauseID;
	std::vector<GameObject*> m_gameObjects;

};

#endif
