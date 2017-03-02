#include "Level_Two.h"


/*
Caleb:
Added a number of platforms. Stairs, a wall with a ledge, a long platform, and an overhead block.
The stairs gradually increase in intensity, for testing purposes. The highest increase is currently 25.

With high enough velocity and a thin enough platform, the character can jump right through them. Something to be careful of.
This is because the player overlaps with the platform a bit on contact, depending on velocity. This also allows stairs to work,
albeit at the cost of slowing the player. Maybe we can turn this into a gameplay element? Side collisions lower vertical speed, maybe?
Also brings to mind wall jumping/clinging.

*/

Level_Two::Level_Two()
{

}

void Level_Two::loadTextures()
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

void Level_Two::createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms, std::vector<SDLGameObject*>* hazards)
{
	// This level will be composed primarily of three

	SDLGameObject* background = new Platform(new LoaderParams(0, 0, 3840, 2160, "background"));

	SDLGameObject* startplat = new Platform(new LoaderParams(100, 2000, 3000, 100, "platform")); // Starting location

	SDLGameObject* cplat1 = new Platform(new LoaderParams(1250, 1800, 1000, 40, "platform")); // Center-Bottom
	SDLGameObject* cplat2 = new Platform(new LoaderParams(750, 1780, 500, 40, "platform"));
	SDLGameObject* cplat3 = new Platform(new LoaderParams(2240, 1780, 500, 40, "platform"));
	SDLGameObject* cplat4 = new Platform(new LoaderParams(2740, 1280, 40, 500, "platform")); // Center-Right side
	SDLGameObject* cplat5 = new Platform(new LoaderParams(2770, 1080, 40, 200, "platform"));
	SDLGameObject* cplat6 = new Platform(new LoaderParams(2790, 780, 40, 300, "platform"));
	SDLGameObject* cplat7 = new Platform(new LoaderParams(2770, 480, 40, 300, "platform"));
	SDLGameObject* cplat8 = new Platform(new LoaderParams(2680, 380, 100, 100, "platform"));
	SDLGameObject* cplat9 = new Platform(new LoaderParams(2600, 360, 100, 40, "platform"));
	SDLGameObject* cplat10 = new Platform(new LoaderParams(740, 1280, 40, 500, "platform")); // Center-Left side
	SDLGameObject* cplat11 = new Platform(new LoaderParams(710, 1080, 40, 200, "platform"));
	SDLGameObject* cplat12 = new Platform(new LoaderParams(690, 780, 40, 300, "platform"));
	SDLGameObject* cplat13 = new Platform(new LoaderParams(710, 480, 40, 300, "platform"));
	SDLGameObject* cplat14 = new Platform(new LoaderParams(740, 380, 100, 100, "platform"));
	SDLGameObject* cplat15 = new Platform(new LoaderParams(820, 360, 100, 40, "platform"));
	SDLGameObject* iplat1 = new Platform(new LoaderParams(770, 700, 800, 40, "platform")); // Center-Internal
	SDLGameObject* iplat2 = new Platform(new LoaderParams(1950, 700, 800, 40, "platform"));
	SDLGameObject* iplat3 = new Platform(new LoaderParams(970, 900, 1600, 40, "platform"));
	SDLGameObject* iplat4 = new Platform(new LoaderParams(770, 1300, 800, 40, "platform"));
	SDLGameObject* iplat5 = new Platform(new LoaderParams(1950, 1300, 800, 40, "platform"));

	SDLGameObject* lplat1 = new Platform(new LoaderParams(50, 1800, 120, 40, "platform")); // Left side
	SDLGameObject* lplat2 = new Platform(new LoaderParams(-350, 1600, 100, 40, "platform"));
	SDLGameObject* lplat3 = new Platform(new LoaderParams(300, 1250, 60, 40, "platform"));
	SDLGameObject* lplat4 = new Platform(new LoaderParams(280, 1100, 300, 40, "platform"));
	SDLGameObject* lplat5 = new Platform(new LoaderParams(-50, 800, 40, 600, "platform"));
	SDLGameObject* lplat6 = new Platform(new LoaderParams(-500, 800, 440, 200, "platform")); // Floating blocks
	SDLGameObject* lplat7 = new Platform(new LoaderParams(-650, 400, 40, 40, "platform"));
	SDLGameObject* lplat8 = new Platform(new LoaderParams(-600, 200, 40, 40, "platform"));

	SDLGameObject* rplat1 = new Platform(new LoaderParams(3000, 1850, 800, 40, "platform")); // Right side
	SDLGameObject* rplat2 = new Platform(new LoaderParams(2800, 1650, 400, 40, "platform"));
	SDLGameObject* rplat3 = new Platform(new LoaderParams(3400, 1250, 300, 40, "platform"));
	SDLGameObject* rplat4 = new Platform(new LoaderParams(4000, 1100, 300, 40, "platform"));
	SDLGameObject* rplat5 = new Platform(new LoaderParams(2800, 800, 200, 40, "platform"));
	SDLGameObject* rplat6 = new Platform(new LoaderParams(2820, 650, 40, 40, "platform")); // Stepping stone

																						   //Hazards
	SDLGameObject* rhaz1 = new Hazard(new LoaderParams(2750, 1750, 100, 100, "hazard"));
	SDLGameObject* rhaz2 = new Hazard(new LoaderParams(2900, 1550, 100, 100, "hazard"));
	SDLGameObject* rhaz3 = new Hazard(new LoaderParams(3650, 1050, 100, 100, "hazard"));
	SDLGameObject* rhaz4 = new Hazard(new LoaderParams(3000, 800, 100, 100, "hazard"));
	SDLGameObject* rhaz5 = new Hazard(new LoaderParams(3100, 800, 100, 100, "hazard"));

	SDLGameObject* ihaz1 = new Hazard(new LoaderParams(1650, 650, 180, 180, "hazard"));

	SDLGameObject* ihaz2 = new Hazard(new LoaderParams(770, 1200, 100, 100, "hazard"));
	SDLGameObject* ihaz3 = new Hazard(new LoaderParams(1100, 1200, 100, 100, "hazard"));
	SDLGameObject* ihaz4 = new Hazard(new LoaderParams(1520, 1200, 100, 100, "hazard"));
	SDLGameObject* ihaz5 = new Hazard(new LoaderParams(1900, 1200, 100, 100, "hazard"));
	SDLGameObject* ihaz6 = new Hazard(new LoaderParams(2300, 1200, 100, 100, "hazard"));
	SDLGameObject* ihaz7 = new Hazard(new LoaderParams(2650, 1200, 100, 100, "hazard"));

	// This class type may change, if we make an actual winning zone class. 
	SDLGameObject* winPlat = new Platform(new LoaderParams(1600, 1700, 300, 40, "platform"));

	gameObjects->push_back(background);
	gameObjects->push_back(startplat);
	gameObjects->push_back(winPlat);

	gameObjects->push_back(cplat1); // Center
	gameObjects->push_back(cplat2);
	gameObjects->push_back(cplat3);
	gameObjects->push_back(cplat4); // Center-Left
	gameObjects->push_back(cplat5);
	gameObjects->push_back(cplat6);
	gameObjects->push_back(cplat7);
	gameObjects->push_back(cplat8);
	gameObjects->push_back(cplat9);
	gameObjects->push_back(cplat10); // Center-Right
	gameObjects->push_back(cplat11);
	gameObjects->push_back(cplat12);
	gameObjects->push_back(cplat13);
	gameObjects->push_back(cplat14);
	gameObjects->push_back(cplat15);
	gameObjects->push_back(iplat1); // Center-Internal
	gameObjects->push_back(iplat2);
	gameObjects->push_back(iplat3);
	gameObjects->push_back(iplat4);
	gameObjects->push_back(iplat5);

	gameObjects->push_back(lplat1); // Left
	gameObjects->push_back(lplat2);
	gameObjects->push_back(lplat3);
	gameObjects->push_back(lplat4);
	gameObjects->push_back(lplat5);
	gameObjects->push_back(lplat6); // Floating blocks
	gameObjects->push_back(lplat7);
	gameObjects->push_back(lplat8);

	gameObjects->push_back(rplat1); // Right
	gameObjects->push_back(rplat2);
	gameObjects->push_back(rplat3);
	gameObjects->push_back(rplat4);
	gameObjects->push_back(rplat5);
	gameObjects->push_back(rplat6);

	gameObjects->push_back(rhaz1); // Hazards
	gameObjects->push_back(rhaz2);
	gameObjects->push_back(rhaz3);
	gameObjects->push_back(rhaz4);
	gameObjects->push_back(rhaz5);
	gameObjects->push_back(ihaz1); // Internal
	gameObjects->push_back(ihaz2);
	gameObjects->push_back(ihaz3);
	gameObjects->push_back(ihaz4);
	gameObjects->push_back(ihaz5);
	gameObjects->push_back(ihaz6);
	gameObjects->push_back(ihaz7);

	platforms->push_back(cplat1); // Center
	platforms->push_back(cplat2);
	platforms->push_back(cplat3);
	platforms->push_back(cplat4); // Center-Left
	platforms->push_back(cplat5);
	platforms->push_back(cplat6);
	platforms->push_back(cplat7);
	platforms->push_back(cplat8);
	platforms->push_back(cplat9);
	platforms->push_back(cplat10); // Center-Right
	platforms->push_back(cplat11);
	platforms->push_back(cplat12);
	platforms->push_back(cplat13);
	platforms->push_back(cplat14);
	platforms->push_back(cplat15);
	platforms->push_back(iplat1); // Center-Internal
	platforms->push_back(iplat2);
	platforms->push_back(iplat3);
	platforms->push_back(iplat4);
	platforms->push_back(iplat5);

	platforms->push_back(lplat1); // Left
	platforms->push_back(lplat2);
	platforms->push_back(lplat3);
	platforms->push_back(lplat4);
	platforms->push_back(lplat5);
	platforms->push_back(lplat6); // Floating blocks
	platforms->push_back(lplat7);
	platforms->push_back(lplat8);

	platforms->push_back(rplat1); // Right
	platforms->push_back(rplat2);
	platforms->push_back(rplat3);
	platforms->push_back(rplat4);
	platforms->push_back(rplat5);
	platforms->push_back(rplat6);

	platforms->push_back(startplat);
	platforms->push_back(winPlat);

	//Adding the hazards to the hazard vector

	hazards->push_back(rhaz1);
	hazards->push_back(rhaz2);
	hazards->push_back(rhaz3);
	hazards->push_back(rhaz4);
	hazards->push_back(rhaz5);
	hazards->push_back(ihaz1); // Internal
	hazards->push_back(ihaz2);
	hazards->push_back(ihaz3);
	hazards->push_back(ihaz4);
	hazards->push_back(ihaz5);
	hazards->push_back(ihaz6);
	hazards->push_back(ihaz7);

}
void Level_Two::setWinLocation(int x, int y, int width, int height)
{
	p_winLocation.x = x;
	p_winLocation.y = y;
	p_winLocation.w = width;
	p_winLocation.h = height;
}

SDL_Rect Level_Two::getWinLocation()
{
	return p_winLocation;
}