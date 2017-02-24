#pragma once
#ifndef  LEVEL_ONE_H
#define  LEVEL_ONE_H
#include "Game.h"
#include "Background.h"
#include "Platform.h"
#include <vector>


/*
Chris :
Created Class
Created update function so the background Rect follows player position
Created loadTextures function to load each texture to the texture manager
Created createObjects to handle object instantiation and pushBack calls

*/
class Level_One
{
public:

	Level_One();
	void loadTextures();
	void createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms);
	void setWinLocation(int x, int y, int width, int height);
	SDL_Rect getWinLocation();


protected:
private:
	SDL_Rect p_winLocation;


};


#endif //  LEVEL_ONE_H