#ifndef SDL_PlayState_h
#define SDL_PlayState_h

#include "GameState.h"
#include "GameObject.h"





class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;

};

#endif