#ifndef __Game__
#define __Game__
#include "SDL.h"
#include "TextureManager.h"
#include "SDLGameObject.h"
#include "SDL_mixer.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include "GameStateMachine.h"
#include "Timer.h"
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
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}


	//	Game() {}
	~Game() {}

	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	void render();
	void update();
	void handleEvents();
	void clean();
	void draw();
	void quit();

	// a function to access the private running variable
	bool running() { return m_bRunning; }

	// MUSIC VARIABLES
	Mix_Chunk *gJumpFX; // SOUND BYTE
	Mix_Chunk *gLandFX; // SOUND BYTE
	Mix_Chunk *gWalkFX; // SOUND BYTE
	Mix_Chunk *gDashFX; // SOUND BYTE
	Mix_Chunk *gDieFX; // SOUND BYTE
	Mix_Chunk *gWrongFX; // SOUND BYTE
	void No();
	void changeToPlay();

	Mix_Music *gMusic; // BACKGROUND MUSIC	
	Mix_Music *gMusic_future; // BACKGROUND MUSIC	
	Timer* p_Timer;
	bool SoundOn = true;
	bool SFXOn = true;

	bool HotReload = false;
	int NumPlayers = 0;
	int level = 0;
	int levelPreviouslyPlayed;
	static const int level_height = 1080;
	static const int level_width = 1920;
	static const int screen_width = 1920;
	static const int screen_height = 1080;



};
// create the typedef
typedef Game TheGame;

#endif /* defined(__Game__) */
