#include "Game.h"
#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>
#include "MenuState.h"
#include "PlayState.h"


Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width,int height, bool fullscreen)
{
	
	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//Load Audio Mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) // ** OPEN THE MIXER, DEFAULT VALUES 
		{
			std::cout << "Failed to make Mixer.";
		}
		//Load Sound Files
		gSoundFX = Mix_LoadWAV("assets/Dawn.wav"); // ** LOAD A SOUND FX / SOUND BYTE FROM FILE - CAN ONLY BE .WAV (?)
		gMusic = Mix_LoadMUS("assets/Upbeat 8 bit.wav"); // ** LOAD A MUSIC FILE, USUALLY USED FOR BGM AS IT CAN BE LOOPED LATER 


		int flags = 0;
		if(fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
		}
		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,width, height, flags);
		if(m_pWindow != 0) // window init success
		{
			std::cout << "window creation success about to setup textures\n";
			
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			
			//Play sounds
			//TO DO: Move these to where we need them
			//Mix_PlayChannel(-1, gSoundFX, 2); // ** PLAY SFX/SOUND BYTE - PUT THIS WHEREVER THE SFX WOULD BE PLAYED - the '2' means it loops 3 times total
			/*
			Mix_PlayMusic(gMusic, -1); // ** START BGM, the '-1' means it will loop ad inifitum
									   //SDL_Delay(5000); // ** NOTE THAT DELAYS DO NOT PAUSE SOUND FX OR MUSIC, AS THEY ARE RUNNING ON A THREAD (?)
			*/


			if(m_pRenderer != 0) // renderer init success
			{
			/*									// to load
				if(!TheTextureManager::Instance()->load("assets/animate-alpha.png","animate", m_pRenderer))
				{
					return false;
				}

				if(!TheTextureManager::Instance()->load("assets/animate-fish-alpha-square.png","animate-fish", m_pRenderer))
				{
					return false;
				}
				std::cout << "renderer creation success\n";



				m_gameObjects.push_back(new Player(new LoaderParams(500, 100, 128, 82,"animate")));

				m_gameObjects.push_back(new Enemy(new LoaderParams(190, 190, 43, 43, "animate-fish")));
				m_gameObjects.push_back(new Enemy(new LoaderParams(290, 290, 43, 43, "animate-fish")));
				m_gameObjects.push_back(new Enemy(new LoaderParams(390, 390, 43, 43, "animate-fish")));

				*/

				SDL_SetRenderDrawColor(m_pRenderer,0,0,0,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MenuState());
	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully, start the main loop
	return true;
}
void Game::render()
{
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();


	SDL_RenderPresent(m_pRenderer);
}
void Game::clean()
{
	std::cout << "cleaning game\n";
	TheInputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::update()
{
	//TheInputHandler::Instance()->update();

	m_pGameStateMachine->update();
}


void Game::draw()
{
	for(std::vector<GameObject*>::size_type i = 0; i !=m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}


void Game::handleEvents()
{

	TheInputHandler::Instance()->update();

	if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_pGameStateMachine->changeState(new PlayState());
	}

}

void Game::quit()
{
	SDL_Quit();
}
