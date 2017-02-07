#ifndef SDL_SettingsState_h
#define SDL_SettingsState_h

#include "GameState.h"
//#include "GameObject.h"
#include <vector>

class GameObject;

class SettingsState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:
	static void s_Toggle();
	static void s_PreviousMenu();

	static const std::string s_pauseID;
	std::vector<GameObject*> m_gameObjects;

};

#endif
