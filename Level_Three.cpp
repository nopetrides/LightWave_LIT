#include "Level_Three.h"


/*
Caleb:
Added a number of platforms. Stairs, a wall with a ledge, a long platform, and an overhead block.
The stairs gradually increase in intensity, for testing purposes. The highest increase is currently 25.

With high enough velocity and a thin enough platform, the character can jump right through them. Something to be careful of.
This is because the player overlaps with the platform a bit on contact, depending on velocity. This also allows stairs to work,
albeit at the cost of slowing the player. Maybe we can turn this into a gameplay element? Side collisions lower vertical speed, maybe?
Also brings to mind wall jumping/clinging.

*/

Level_Three::Level_Three()
{

}

void Level_Three::loadTextures()
{
	//Load the background texture. 
	if (!TheTextureManager::Instance()->load("assets/5-DarkBlocks.png", "background", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	//Load the platform texture
	if (!TheTextureManager::Instance()->load("assets/GreenFloor.png", "platform", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	//Load the platform texture
	if (!TheTextureManager::Instance()->load("assets/hazard.png", "hazard", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	if (!TheTextureManager::Instance()->load("assets/checker.png", "finish", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
}

void Level_Three::createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms, std::vector<SDLGameObject*>* hazards)
{
	//Create objects in the level. 
	// This is where we will create a vector of all platforms for ease of coding
	// then shove them into the game objects vector. 
	SDLGameObject* background = new Platform(new LoaderParams(0, 0, 50000, 2080, "background"));
	SDLGameObject* plat = new Platform(new LoaderParams(500, 700, 500, 50, "platform"));
	SDLGameObject* plat1 = new Platform(new LoaderParams(1800, 700, 200, 50, "platform"));
	SDLGameObject* plat2 = new Platform(new LoaderParams(2500, 500, 200, 50, "platform"));
	SDLGameObject* plat3 = new Platform(new LoaderParams(3000, -100, 200, 100, "platform"));
	SDLGameObject* plat4 = new Platform(new LoaderParams(3200, 700, 400, 100, "platform"));
	SDLGameObject* plat5 = new Platform(new LoaderParams(3700, 100, 200, 100, "platform"));
	SDLGameObject* plat6 = new Platform(new LoaderParams(4200, 0, 200, 100, "platform"));
	SDLGameObject* plat7 = new Platform(new LoaderParams(4700, -200, 100, 100, "platform"));
	SDLGameObject* plat8 = new Platform(new LoaderParams(5200, -400, 100, 100, "platform"));
	SDLGameObject* plat9 = new Platform(new LoaderParams(4700, -600, 100, 100, "platform"));
	SDLGameObject* plat10 = new Platform(new LoaderParams(5200, -800, 100, 100, "platform"));
	SDLGameObject* plat11 = new Platform(new LoaderParams(4600, -1000, 100, 100, "platform"));
	SDLGameObject* plat12 = new Platform(new LoaderParams(5500, 800, 500, 100, "platform"));
	SDLGameObject* plat13 = new Platform(new LoaderParams(5500, -1100, 50, 1500, "platform"));
	SDLGameObject* plat14 = new Platform(new LoaderParams(5500, -1200, 400, 100, "platform"));
	SDLGameObject* plat15 = new Platform(new LoaderParams(7700, -1200, 400, 100, "platform"));
	SDLGameObject* plat16 = new Platform(new LoaderParams(3100, 300, 200, 100, "platform"));
	SDLGameObject* plat17 = new Platform(new LoaderParams(5500, 300, 3000, 100, "platform"));
	SDLGameObject* plat18 = new Platform(new LoaderParams(8700, 800, 400, 100, "platform"));
	SDLGameObject* plat19 = new Platform(new LoaderParams(8300, -1600, 50, 1200, "platform"));
	SDLGameObject* plat20 = new Platform(new LoaderParams(6800, -500, 200, 100, "platform"));
	SDLGameObject* plat21 = new Platform(new LoaderParams(5500, -200, 2500, 100, "platform"));
	SDLGameObject* plat22 = new Platform(new LoaderParams(8200, -100, 200, 100, "platform"));
	SDLGameObject* plat23 = new Platform(new LoaderParams(9400, 600, 100, 100, "platform"));
	SDLGameObject* plat24 = new Platform(new LoaderParams(10000, 400, 100, 100, "platform"));
	SDLGameObject* plat25 = new Platform(new LoaderParams(8800, -300, 200, 100, "platform"));
	SDLGameObject* plat26 = new Platform(new LoaderParams(9400, -500, 100, 100, "platform"));
	SDLGameObject* plat27 = new Platform(new LoaderParams(9900, -400, 100, 100, "platform"));
	//SDLGameObject* plat28 = new Platform(new LoaderParams(10500, 200, 500, 100, "platform"));

	SDLGameObject* winPlat = new Platform(new LoaderParams(10500, 20, 500, 100, "finish"));
	
	SDLGameObject* haz = new Hazard(new LoaderParams(1400, 500, 100, 100, "hazard"));
	SDLGameObject* haz1 = new Hazard(new LoaderParams(2200, 300, 100, 100, "hazard"));
	SDLGameObject* haz2= new Hazard(new LoaderParams(2700, -100, 100, 100, "hazard"));
	SDLGameObject* haz3 = new Hazard(new LoaderParams(2800, 500, 100, 100, "hazard"));
	SDLGameObject* haz4 = new Hazard(new LoaderParams(3000, 400, 100, 100, "hazard"));
	SDLGameObject* haz5 = new Hazard(new LoaderParams(4000, 200, 100, 100, "hazard"));
	SDLGameObject* haz6 = new Hazard(new LoaderParams(4500, 100, 100, 100, "hazard"));
	SDLGameObject* haz7 = new Hazard(new LoaderParams(5000, 0, 100, 100, "hazard"));
	SDLGameObject* haz8 = new Hazard(new LoaderParams(5400, -100, 100, 100, "hazard"));
	SDLGameObject* haz9 = new Hazard(new LoaderParams(4400, -800, 100, 100, "hazard"));
	SDLGameObject* haz10 = new Hazard(new LoaderParams(3500, 400, 100, 100, "hazard"));
	SDLGameObject* haz11 = new Hazard(new LoaderParams(3400, 400, 100, 100, "hazard"));
	SDLGameObject* haz12 = new Hazard(new LoaderParams(3300, 400, 100, 100, "hazard"));
	SDLGameObject* haz13 = new Hazard(new LoaderParams(5400, 400, 100, 100, "hazard"));
	SDLGameObject* haz14 = new Hazard(new LoaderParams(4800, 300, 100, 100, "hazard"));
	SDLGameObject* haz15 = new Hazard(new LoaderParams(6000, -1000, 100, 100, "hazard"));
	SDLGameObject* haz16 = new Hazard(new LoaderParams(6200, -800, 100, 100, "hazard"));
	SDLGameObject* haz17 = new Hazard(new LoaderParams(6900, -1200, 100, 100, "hazard"));
	SDLGameObject* haz18 = new Hazard(new LoaderParams(7200, -900, 100, 100, "hazard"));
	SDLGameObject* haz19 = new Hazard(new LoaderParams(6500, -500, 100, 100, "hazard"));
	SDLGameObject* haz20 = new Hazard(new LoaderParams(6100, -300, 100, 100, "hazard"));
	SDLGameObject* haz21 = new Hazard(new LoaderParams(7600, -1100, 100, 100, "hazard"));



	gameObjects->push_back(background);
	gameObjects->push_back(plat);
	gameObjects->push_back(plat1);
	gameObjects->push_back(plat2);
	gameObjects->push_back(plat3);
	gameObjects->push_back(plat4);
	gameObjects->push_back(plat5);
	gameObjects->push_back(plat6);
	gameObjects->push_back(plat7);
	gameObjects->push_back(plat8);
	gameObjects->push_back(plat9);
	gameObjects->push_back(plat10);
	gameObjects->push_back(plat11);
	gameObjects->push_back(plat12);
	gameObjects->push_back(plat13);
	gameObjects->push_back(plat14);
	gameObjects->push_back(plat15);
	gameObjects->push_back(plat16);
	gameObjects->push_back(plat17);
	gameObjects->push_back(plat18);
	gameObjects->push_back(plat19);
	gameObjects->push_back(plat20);
	gameObjects->push_back(plat21);
	gameObjects->push_back(plat22);
	gameObjects->push_back(plat23);
	gameObjects->push_back(plat24);
	gameObjects->push_back(plat25);
	gameObjects->push_back(plat26);
	gameObjects->push_back(plat27);
	gameObjects->push_back(winPlat);
	
	gameObjects->push_back(haz);
	gameObjects->push_back(haz1);
	gameObjects->push_back(haz2);
	gameObjects->push_back(haz3);
	gameObjects->push_back(haz4);
	gameObjects->push_back(haz5);
	gameObjects->push_back(haz6);
	gameObjects->push_back(haz7);
	gameObjects->push_back(haz8);
	gameObjects->push_back(haz9);
	gameObjects->push_back(haz10);
	gameObjects->push_back(haz11);
	gameObjects->push_back(haz12);
	gameObjects->push_back(haz13);
	gameObjects->push_back(haz14);
	gameObjects->push_back(haz15);
	gameObjects->push_back(haz16);
	gameObjects->push_back(haz17);
	gameObjects->push_back(haz18);
	gameObjects->push_back(haz19);
	gameObjects->push_back(haz20);
	gameObjects->push_back(haz21);

	platforms->push_back(plat);
	platforms->push_back(plat1);
	platforms->push_back(plat2);
	platforms->push_back(plat3);
	platforms->push_back(plat4);
	platforms->push_back(plat5);
	platforms->push_back(plat6);
	platforms->push_back(plat7);
	platforms->push_back(plat8);
	platforms->push_back(plat9);
	platforms->push_back(plat10);
	platforms->push_back(plat11);
	platforms->push_back(plat12);
	platforms->push_back(plat13);
	platforms->push_back(plat14);
	platforms->push_back(plat15);
	platforms->push_back(plat16);
	platforms->push_back(plat17);
	platforms->push_back(plat18);
	platforms->push_back(plat19);
	platforms->push_back(plat20);
	platforms->push_back(plat21);
	platforms->push_back(plat22);
	platforms->push_back(plat23);
	platforms->push_back(plat24);
	platforms->push_back(plat25);
	platforms->push_back(plat26);
	platforms->push_back(plat27);
	//platforms->push_back(plat28);

	platforms->push_back(winPlat);

	//Adding the hazards to the hazard vector
	hazards->push_back(haz);
	hazards->push_back(haz1);
	hazards->push_back(haz2);
	hazards->push_back(haz3);
	hazards->push_back(haz4);
	hazards->push_back(haz5);
	hazards->push_back(haz6);
	hazards->push_back(haz7);
	hazards->push_back(haz8);
	hazards->push_back(haz9);
	hazards->push_back(haz10);
	hazards->push_back(haz11);
	hazards->push_back(haz12);
	hazards->push_back(haz13);
	hazards->push_back(haz14);
	hazards->push_back(haz15);
	hazards->push_back(haz16);
	hazards->push_back(haz17);
	hazards->push_back(haz18);
	hazards->push_back(haz19);
	hazards->push_back(haz20);
	hazards->push_back(haz21);

}
void Level_Three::setWinLocation(int x, int y, int width, int height)
{
	p_winLocation.x = x;
	p_winLocation.y = y;
	p_winLocation.w = width;
	p_winLocation.h = height;
}

SDL_Rect Level_Three::getWinLocation()
{
	return p_winLocation;
}