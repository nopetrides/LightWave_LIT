#ifndef  LEVEL_THREE_H
#define  LEVEL_THREE_H
#include "Game.h"
#include "Background.h"
#include "Platform.h"
#include "Hazard.h"
#include <vector>


/*
Chris :
Created Class
Created update function so the background Rect follows player position
Created loadTextures function to load each texture to the texture manager
Created createObjects to handle object instantiation and pushBack calls

*/
class Level_Three
{
public:

	Level_Three();
	void loadTextures();
	void createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms, std::vector<SDLGameObject*>* hazards);
	void setWinLocation(int x, int y, int width, int height);
	SDL_Rect getWinLocation();


protected:
private:
	SDL_Rect p_winLocation;


};


#endif //  LEVEL_Three_H