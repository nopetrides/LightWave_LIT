#include "Level_One.h"

Level_One::Level_One()
{

}

void Level_One::loadTextures()
{
	//Load the background texture. 
	if (!TheTextureManager::Instance()->load("assets/street.png", "background", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	//Load the platform texture
	if (!TheTextureManager::Instance()->load("assets/platform.png", "platform", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
}

void Level_One::createObjects(std::vector<GameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms)
{

	//Create objects in the level. 
	// This is where we will create a vector of all platforms for ease of coding
	// then shove them into the game objects vector. 
	SDLGameObject* background = new Platform(new LoaderParams(0, 0, 1920, 1080, "background"));
	SDLGameObject* plat = new Platform(new LoaderParams(100, 200, 100, 100, "platform"));
	SDLGameObject* plat1 = new Platform(new LoaderParams(200, 250, 100, 100, "platform"));

	//Instantiate Win Location Object. 
	// This class type may change, if we make an actual winning zone class. 
	SDLGameObject* winPlat = new Platform(new LoaderParams(500, 250, 100, 50, "platform"));

	gameObjects->push_back(background);
	gameObjects->push_back(plat);
	gameObjects->push_back(plat1);
	gameObjects->push_back(winPlat);

	platforms->push_back(plat);
	platforms->push_back(plat1);

	//Adding the win platform to the platforms array for collision, since we will 
	// probably show a victory overlay and the player will stand on the platform 
	// waiting for the others to finish. 
	platforms->push_back(winPlat);
}
void Level_One::setWinLocation(int x, int y, int width, int height)
{
	p_winLocation.x = x;
	p_winLocation.y = y;
	p_winLocation.w = width;
	p_winLocation.h = height;
}

SDL_Rect Level_One::getWinLocation()
{
	return p_winLocation;
}