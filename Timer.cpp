#include "Timer.h"
#include <iostream>
Timer::Timer()
{
	startedTicks = 0;
	pausedTicks = 0;
	b_Started = false;
	b_Paused = false;
}

void Timer::start()
{
	startedTicks = SDL_GetTicks(); // Get the current clock ticks
	b_Started = true;
	b_Paused = false;
}

void Timer::stop()
{
	b_Started = false;
	b_Paused = false;
}

void Timer::pause()
{
	// Check to see if the timer is already running and it isn't paused already. 
	if (b_Started && !b_Paused)
	{
		b_Paused = true;
		pausedTicks = SDL_GetTicks(); // Save the time, to subtract later from total play time. 
	}
}

void Timer::unpause()
{
	if (b_Paused)
	{
		//unpause
		b_Paused = false;

		//Reset starting ticks
		startedTicks = SDL_GetTicks() - pausedTicks;

		//Reset Paused ticks
		pausedTicks = 0;
	}
}

int Timer::getTicks()
{
	if (b_Started == true)
	{
		return SDL_GetTicks() - startedTicks;
	}
	else
	{
		std::cout << "Error, timer may not be started.\n" << SDL_GetError();
		return 0;
	}

}

bool Timer::isStarted()
{
	return b_Started;
}

bool Timer::isPaused()
{
	return b_Paused;
}

void Timer::draw(SDL_Renderer* renderer)
{
	SDL_Rect destRect;
	SDL_Rect srcRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = 60;
	srcRect.h = destRect.h = 30;
	destRect.x = 0;
	destRect.y = 0;

	SDL_RenderCopyEx(renderer, p_Texture, &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void Timer::init()
{
	if (TTF_OpenFont("assets/fish.ttf", 10) < 0)
	{
		std::cout << "Failed to open font. Error: " << TTF_GetError();
	}

	myFont = TTF_OpenFont("assets/fish.ttf", 24);

	if (!myFont)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
}

void Timer::update(SDL_Renderer* renderer)
{
	std::stringstream time;
	time.precision(4);
	//time.fixed;
	//Divide by 1000 to get seconds
	time << getTicks() / 1000.f;

	//Checl to see if the string stream is empty. 
	if (time.rdbuf()->in_avail() > 0)
		p_Time = TTF_RenderText_Solid(myFont, time.str().c_str(), white);
	p_Texture = SDL_CreateTextureFromSurface(renderer, p_Time);
	SDL_FreeSurface(p_Time); // Free the surface

}







