#include "Game.h"
#include <Windows.h>
#include <stdio.h>
// our Game object
//Game* g_game = 0;

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS; //page 78

int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime; ///page 78
	AllocConsole();
	FILE* myFile;

	freopen_s(&myFile,"CON","w", stdout);
	// g_game = new Game();
	if (TheGame::Instance()->init("Chapter 1", 100, 100, 640, 480, false))
	{

		while(TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks(); // page 79
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			// SDL_Delay(10); // add the delay
			
			frameTime = SDL_GetTicks() - frameStart; //page 78

			if(frameTime< DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}
	TheGame::Instance()->clean();
	return 0;
}