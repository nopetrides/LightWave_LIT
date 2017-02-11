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

	void PlayerCollisionAgainstPlatforms(Player player , SDLGameObject* platforms);

private:
	static const std::string s_playID;
	std::vector<GameObject*> m_gameObjects;

	int considerForCollision = 20;
	float collideDistance = 2.0f;

};

#endif