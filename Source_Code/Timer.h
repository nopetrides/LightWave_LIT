#include "SDL.h"
#include "SDL_ttf.h"
#include <sstream>

#pragma once
#ifndef TIMER_H
#define TIMER_H


// Chris - 02/22/2017
// Created Timer class.
// Not sure if it needs to be rendered the same way other game objects are, therefore it may not go in the game objects list. 
// Might handle it's own rendering etc...

class Timer
{

private:
	
	int pausedTicks; // Var to track number of ticks passed while timer was paused. 
	int startedTicks; // Var for ticks while running
	bool b_Paused; 
	bool b_Started;

public: 
	Timer(); // Constructor
	//Timer function prototypes
	void start();
	void stop();
	void pause();
	void unpause();
	void draw(SDL_Renderer* renderer, int x, int y, int w, int h);
	void init();

	int getTicks(); // Function to return the amount of ticks passed. 

	//Checks to see status of Timer.
	bool isStarted();
	bool isPaused();
	
	void update(SDL_Renderer* renderer);
	SDL_Surface *p_Time;
	SDL_Texture* p_Texture;

	TTF_Font* myFont;
	SDL_Color white = { 255,255,255};
	

private: 	

};

#endif