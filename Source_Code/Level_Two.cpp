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
	if (!TheTextureManager::Instance()->load("assets/BG12.png", "background", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Light.png", "light", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	//Load the platform texture.
	if (!TheTextureManager::Instance()->load("assets/GreenFloor.png", "platform", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	// Load the hazard textures.
	// Hazard 4 is not used, but is included for possible future editing. 
	if (!TheTextureManager::Instance()->load("assets/hazard.png", "hazard", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/hazard2.png", "hazard2", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/hazard3.png", "hazard3", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/hazard4.png", "hazard4", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	// Load the finish line texture.
	if (!TheTextureManager::Instance()->load("assets/checker.png", "finish", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
}

void Level_Two::createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms, std::vector<SDLGameObject*>* hazards)
{
	// This level will be composed primarily of three

	SDLGameObject* background = new Platform(new LoaderParams(-5000, -11000, 27200, 16000, "background"));

	/*
	//Player* player = new Player(new LoaderParams(500, 500, 71, 65, "player")); // Player start location
	SDLGameObject* startplat = new Platform(new LoaderParams(100, 2000, 3000, 100, "platform")); // Starting location
	(500, 500, 71, 65, "player")
	(100, 2000, 3000, 100, "platform")
	(600, 300, 300, 40, "finish"))

	A bit of manual testing..+400, -1400 will work.
	Tested more. Reduce by 1400 on X, for -800 net change.
	*/

	SDLGameObject* startplat = new Platform(new LoaderParams(-900, 600, 3000, 100, "platform")); // Starting location

	SDLGameObject* cplat1 = new Platform(new LoaderParams(250, 400, 1000, 40, "platform")); // Center-Bottom
	SDLGameObject* cplat2 = new Platform(new LoaderParams(-350, 380, 600, 40, "platform"));
	SDLGameObject* cplat3 = new Platform(new LoaderParams(1240, 380, 500, 40, "platform"));
	SDLGameObject* cplat4 = new Platform(new LoaderParams(1740, -120, 40, 500, "platform")); // Center-Right side
	SDLGameObject* cplat5 = new Platform(new LoaderParams(1770, -320, 40, 200, "platform"));
	SDLGameObject* cplat6 = new Platform(new LoaderParams(1790, -620, 40, 300, "platform"));
	SDLGameObject* cplat7 = new Platform(new LoaderParams(1770, -920, 40, 300, "platform"));
	SDLGameObject* cplat8 = new Platform(new LoaderParams(1680, -1020, 100, 100, "platform"));
	SDLGameObject* cplat9 = new Platform(new LoaderParams(1600, -1040, 100, 40, "platform"));
	SDLGameObject* cplat10 = new Platform(new LoaderParams(-360, -120, 40, 500, "platform")); // Center-Left side
	SDLGameObject* cplat11 = new Platform(new LoaderParams(-390, -320, 40, 200, "platform"));
	SDLGameObject* cplat12 = new Platform(new LoaderParams(-390, -620, 40, 300, "platform"));
	SDLGameObject* cplat13 = new Platform(new LoaderParams(-390, -920, 40, 300, "platform"));
	SDLGameObject* cplat14 = new Platform(new LoaderParams(-3600, -1020, 100, 100, "platform"));
	SDLGameObject* cplat15 = new Platform(new LoaderParams(-1800, -1040, 100, 40, "platform"));
	SDLGameObject* iplat1 = new Platform(new LoaderParams(-330, -700, 800, 40, "platform")); // Center-Internal
	SDLGameObject* iplat2 = new Platform(new LoaderParams(950, -700, 800, 40, "platform"));
	SDLGameObject* iplat3 = new Platform(new LoaderParams(-30, -500, 1600, 40, "platform"));
	SDLGameObject* iplat4 = new Platform(new LoaderParams(-330, -100, 800, 40, "platform"));
	SDLGameObject* iplat5 = new Platform(new LoaderParams(950, -100, 800, 40, "platform"));
	SDLGameObject* lplat1 = new Platform(new LoaderParams(-950, 400, 120, 40, "platform")); // Left side
	SDLGameObject* lplat2 = new Platform(new LoaderParams(-1350, 200, 100, 40, "platform"));
	SDLGameObject* lplat3 = new Platform(new LoaderParams(-700, -150, 60, 40, "platform"));
	SDLGameObject* lplat4 = new Platform(new LoaderParams(-720, -300, 300, 40, "platform"));
	SDLGameObject* lplat5 = new Platform(new LoaderParams(-1050, -600, 40, 600, "platform"));
	SDLGameObject* lplat6 = new Platform(new LoaderParams(-1500, -600, 440, 200, "platform")); // Floating blocks
	SDLGameObject* lplat7 = new Platform(new LoaderParams(-1650, -1000, 40, 40, "platform"));
	SDLGameObject* lplat8 = new Platform(new LoaderParams(-1600, -1200, 40, 40, "platform"));

	SDLGameObject* rplat1 = new Platform(new LoaderParams(2000, 450, 800, 40, "platform")); // Right side
	SDLGameObject* rplat2 = new Platform(new LoaderParams(1800, 250, 400, 40, "platform"));
	SDLGameObject* rplat3 = new Platform(new LoaderParams(2400, -150, 300, 40, "platform"));
	SDLGameObject* rplat4 = new Platform(new LoaderParams(3000, -300, 300, 40, "platform"));
	SDLGameObject* rplat5 = new Platform(new LoaderParams(1800, -600, 200, 40, "platform"));
	SDLGameObject* rplat6 = new Platform(new LoaderParams(1820, -750, 40, 40, "platform")); // Stepping stone
																						   
	SDLGameObject* rhaz1 = new Hazard(new LoaderParams(1750, 350, 120, 120, "hazard3")); // Hazards
	SDLGameObject* rhaz2 = new Hazard(new LoaderParams(1900, 150, 120, 120, "hazard3"));
	SDLGameObject* rhaz3 = new Hazard(new LoaderParams(2650, -350, 120, 120, "hazard3"));
	SDLGameObject* rhaz4 = new Hazard(new LoaderParams(2000, -600, 120, 120, "hazard3"));
	SDLGameObject* rhaz5 = new Hazard(new LoaderParams(2100, -600, 120, 120, "hazard3"));

	SDLGameObject* ihaz1 = new Hazard(new LoaderParams(650, -750, 148, 170, "hazard2"));
	SDLGameObject* ihaz2 = new Hazard(new LoaderParams(-230, -200, 100, 100, "hazard"));
	SDLGameObject* ihaz3 = new Hazard(new LoaderParams(100, -200, 100, 100, "hazard"));
	SDLGameObject* ihaz4 = new Hazard(new LoaderParams(5800, -200, 100, 100, "hazard"));
	SDLGameObject* ihaz5 = new Hazard(new LoaderParams(900, -200, 100, 100, "hazard"));
	SDLGameObject* ihaz6 = new Hazard(new LoaderParams(1300, -200, 100, 100, "hazard"));
	SDLGameObject* ihaz7 = new Hazard(new LoaderParams(1550, -200, 100, 100, "hazard"));


	// This class type may change, if we make an actual winning zone class. 
	SDLGameObject* winPlat = new Platform(new LoaderParams(600, 300, 300, 40, "finish"));
	SDLGameObject* light = new Platform(new LoaderParams(700, 200, 100, 79, "light"));

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
	gameObjects->push_back(light);

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