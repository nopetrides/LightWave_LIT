#include "TTF_Controller.h"
#include <iostream>
void TTF_Controller::init()
{
	if (TTF_Init() < 0)
	{
		std::cout << "Failed to Init TTF.\n";
	}
}

void TTF_Controller::setUpFont()
{
					  //Set font to "Times New Roman" and 10 size
	if (TTF_OpenFont("Times.ttf", 10) < 0)
	{
		std::cout << "Failed to open font. Error: " << TTF_GetError();
	}


	
	
	
}
/*
void TTF_Controller::freeFontSurface()
{
SDL_FreeSurface(textSurface);
}

void TTF_Controller::Quit()
{
TTF_Quit(); // Quit the TTF engine before closing SDL.
}

SDL_Surface TTF_Controller::getSurface()
{
return *textSurface;
}

*/
