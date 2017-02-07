#ifndef __Game__
#define __Game__
#include "SDL.h"
#include "TextureManager.h"
#include "SDLGameObject.h"
#include "SDL_mixer.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <vector>
#include "GameStateMachine.h"
class Game
{
private:
	Game() {};

	// create the s_pInstance member variable
	static Game* s_pInstance;

	
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	int m_currentFrame;
	
/*	GameObject* m_player;
	GameObject* m_player2;
	GameObject* m_enemy1;
	GameObject* m_enemy2;
	GameObject* m_enemy3;
*/
	std::vector<GameObject*> m_gameObjects;
	GameStateMachine* m_pGameStateMachine;


	bool m_bRunning;
public:
	static Game* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}


//	Game() {}
	~Game() {}

	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width,int height, bool fullscreen);

	 SDL_Renderer* getRenderer() const { return m_pRenderer; }
	 GameStateMachine* getStateMachine(){ return m_pGameStateMachine; }

	void render();
	void update();
	void handleEvents();
	void clean();
	void draw();
	void quit();

	// a function to access the private running variable
	bool running() { return m_bRunning; }

	// MUSIC VARIABLES
	Mix_Chunk *gSoundFX; // SOUND BYTE
	Mix_Music *gMusic; // BACKGROUND MUSIC	

	bool SoundOn = true;
	int NumPlayers = 0;
	int level = 0;

};
// create the typedef
	typedef Game TheGame;

#endif /* defined(__Game__) */

