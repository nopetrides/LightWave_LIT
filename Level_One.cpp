#include "Level_One.h"


/*
Caleb:
Added a number of platforms. Stairs, a wall with a ledge, a long platform, and an overhead block.
The stairs gradually increase in intensity, for testing purposes. The highest increase is currently 25.

With high enough velocity and a thin enough platform, the character can jump right through them. Something to be careful of.
This is because the player overlaps with the platform a bit on contact, depending on velocity. This also allows stairs to work,
albeit at the cost of slowing the player. Maybe we can turn this into a gameplay element? Side collisions lower vertical speed, maybe?
Also brings to mind wall jumping/clinging.

*/

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

void Level_One::createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms, std::vector<SDLGameObject*>* hazards)
{
	//Create objects in the level. 
	// This is where we will create a vector of all platforms for ease of coding
	// then shove them into the game objects vector. 
	SDLGameObject* background = new Platform(new LoaderParams(0, 0, 1920, 1080, "background"));
	SDLGameObject* plat = new Platform(new LoaderParams(100, 200, 100, 100, "platform"));
	SDLGameObject* plat1 = new Platform(new LoaderParams(200, 250, 100, 100, "platform"));

	// Added more platforms. -CM
	SDLGameObject* plat2 = new Platform(new LoaderParams(300, 430, 100, 30, "platform")); // Stairs
	SDLGameObject* plat3 = new Platform(new LoaderParams(400, 440, 100, 30, "platform"));
	SDLGameObject* plat4 = new Platform(new LoaderParams(500, 455, 100, 30, "platform"));
	SDLGameObject* plat5 = new Platform(new LoaderParams(600, 475, 100, 30, "platform"));
	SDLGameObject* plat6 = new Platform(new LoaderParams(700, 500, 100, 30, "platform"));
	SDLGameObject* plat7 = new Platform(new LoaderParams(1200, 150, 100, 250, "platform")); // Wall
	SDLGameObject* plat8 = new Platform(new LoaderParams(1200, 400, 100, 250, "platform"));
	SDLGameObject* plat9 = new Platform(new LoaderParams(1200, 650, 100, 250, "platform"));
	SDLGameObject* plat10 = new Platform(new LoaderParams(1200, 800, 100, 250, "platform"));
	SDLGameObject* plat11 = new Platform(new LoaderParams(1100, 650, 100, 100, "platform")); // Ledge
	SDLGameObject* plat12 = new Platform(new LoaderParams(50, 900, 850, 30, "platform")); // Long platform
	SDLGameObject* plat13 = new Platform(new LoaderParams(650, 50, 400, 50, "platform")); // Overhead block


																						  //Hazards
	SDLGameObject* haz = new Hazard(new LoaderParams(400, 350, 100, 100, "hazard"));
	SDLGameObject* haz1 = new Hazard(new LoaderParams(250, 0, 100, 100, "hazard"));																		  //Instantiate Win Location Object. 
																						  // This class type may change, if we make an actual winning zone class. 
	SDLGameObject* winPlat = new Platform(new LoaderParams(500, 250, 100, 50, "platform"));

	gameObjects->push_back(background);
	gameObjects->push_back(plat);
	gameObjects->push_back(plat1);

	gameObjects->push_back(plat2); // Stairs
	gameObjects->push_back(plat3);
	gameObjects->push_back(plat4);
	gameObjects->push_back(plat5);
	gameObjects->push_back(plat6);
	gameObjects->push_back(plat7); // Wall
	gameObjects->push_back(plat8);
	gameObjects->push_back(plat9);
	gameObjects->push_back(plat10);
	gameObjects->push_back(plat11); // Ledge
	gameObjects->push_back(plat12); // Long platform
	gameObjects->push_back(plat13); // Overhead block

	gameObjects->push_back(winPlat);

	gameObjects->push_back(haz);
	gameObjects->push_back(haz1);

	platforms->push_back(plat);
	platforms->push_back(plat1);

	platforms->push_back(plat2); // Stairs
	platforms->push_back(plat3);
	platforms->push_back(plat4);
	platforms->push_back(plat5);
	platforms->push_back(plat6);
	platforms->push_back(plat7); // Wall
	platforms->push_back(plat8);
	platforms->push_back(plat9);
	platforms->push_back(plat10);
	platforms->push_back(plat11); // Ledge
	platforms->push_back(plat12); // Long platform
	platforms->push_back(plat13); // Overhead block

								  //Adding the win platform to the platforms array for collision, since we will 
								  // probably show a victory overlay and the player will stand on the platform 
								  // waiting for the others to finish. 
	platforms->push_back(winPlat);

	//Adding the hazards to the hazard vector
	hazards->push_back(haz);
	hazards->push_back(haz1);
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