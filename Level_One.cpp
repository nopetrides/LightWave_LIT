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

void Level_One::createObjects( std::vector<GameObject* >* gameObjects)
{

	//Create objects in the level. 
	// This is where we will create a vector of all platforms for ease of coding
	// then shove them into the game objects vector. 
	GameObject* background = new Platform(new LoaderParams(0, 0, 1920, 1080, "background"));
	GameObject* plat = new Platform(new LoaderParams(0, 20, 100, 100, "platform"));
	gameObjects->push_back(background);
	gameObjects->push_back(plat);
}

