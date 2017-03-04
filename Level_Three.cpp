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
	if (!TheTextureManager::Instance()->load("assets/BG12.png", "background", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Light.png", "light", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	//Load the platform texture
	if (!TheTextureManager::Instance()->load("assets/GreenFloor.png", "platform", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/BlueBox.png", "bluebox", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/GreenBox.png", "greenbox", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/checker.png", "finish", TheGame::Instance()->getRenderer()))
	{
		std::cout << "Error: " << SDL_GetError();
	}

	//Load the platform texture
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


}

void Level_Three::createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms, std::vector<SDLGameObject*>* hazards)
{
	//Create objects in the level. 
	// This is where we will create a vector of all platforms for ease of coding
	// then shove them into the game objects vector. 
	SDLGameObject* background = new Platform(new LoaderParams(-5000, -11000, 27200, 16000, "background"));

	SDLGameObject* plat = new Platform(new LoaderParams(500, 700, 100, 50, "platform"));
	SDLGameObject* plat_1 = new Platform(new LoaderParams(600, 700, 100, 50, "platform"));
	SDLGameObject* plat_2 = new Platform(new LoaderParams(700, 700, 100, 50, "platform"));
	SDLGameObject* plat_3 = new Platform(new LoaderParams(800, 700, 100, 50, "platform"));
	SDLGameObject* plat_4 = new Platform(new LoaderParams(900, 700, 100, 50, "platform"));



	SDLGameObject* plat1 = new Platform(new LoaderParams(1800, 700, 100, 50, "platform"));
	SDLGameObject* plat1_1 = new Platform(new LoaderParams(1900, 700, 100, 50, "platform"));

	SDLGameObject* plat2 = new Platform(new LoaderParams(2500, 500, 100, 50, "platform"));
	SDLGameObject* plat2_1 = new Platform(new LoaderParams(2600, 500, 100, 50, "platform"));

	SDLGameObject* plat3 = new Platform(new LoaderParams(2900, -300, 100, 50, "platform"));
	SDLGameObject* plat3_1 = new Platform(new LoaderParams(3000, -300, 100, 50, "platform"));

	SDLGameObject* plat4 = new Platform(new LoaderParams(3200, 700, 100, 50, "platform"));
	SDLGameObject* plat4_1 = new Platform(new LoaderParams(3300, 700, 100, 50, "platform"));
	SDLGameObject* plat4_2 = new Platform(new LoaderParams(3400, 700, 100, 50, "platform"));
	SDLGameObject* plat4_3 = new Platform(new LoaderParams(3500, 700, 100, 50, "platform"));
	SDLGameObject* plat4_4 = new Platform(new LoaderParams(3100, 700, 100, 50, "platform"));

	SDLGameObject* plat5 = new Platform(new LoaderParams(3700, 100, 100, 50, "platform"));
	SDLGameObject* plat5_1 = new Platform(new LoaderParams(3800, 100, 100, 50, "platform"));

	SDLGameObject* plat6 = new Platform(new LoaderParams(4200, 0, 100, 50, "platform"));
	SDLGameObject* plat6_1 = new Platform(new LoaderParams(4300, 0, 100, 50, "platform"));

	SDLGameObject* plat7 = new Platform(new LoaderParams(4700, -200, 150, 50, "platform"));

	SDLGameObject* plat8 = new Platform(new LoaderParams(5200, -400, 150, 50, "platform"));

	SDLGameObject* plat9 = new Platform(new LoaderParams(4700, -600, 150, 50, "platform"));

	SDLGameObject* plat10 = new Platform(new LoaderParams(5200, -800, 150, 50, "platform"));

	SDLGameObject* plat11 = new Platform(new LoaderParams(4600, -1000, 150, 50, "platform"));

	SDLGameObject* plat12 = new Platform(new LoaderParams(5500, 800, 100, 50, "platform"));
	SDLGameObject* plat12_1 = new Platform(new LoaderParams(5600, 800, 100, 50, "platform"));
	SDLGameObject* plat12_2 = new Platform(new LoaderParams(5700, 800, 100, 50, "platform"));
	SDLGameObject* plat12_3 = new Platform(new LoaderParams(5800, 800, 100, 50, "platform"));
	SDLGameObject* plat12_4 = new Platform(new LoaderParams(5900, 800, 100, 50, "platform"));

	//SDLGameObject* plat13 = new Platform(new LoaderParams(5500, -1100, 50, 1500, "platform"));

	SDLGameObject* plat14 = new Platform(new LoaderParams(5500, -1200, 100, 50, "platform"));
	SDLGameObject* plat14_1 = new Platform(new LoaderParams(5600, -1200, 100, 50, "platform"));
	SDLGameObject* plat14_2 = new Platform(new LoaderParams(5700, -1200, 100, 50, "platform"));
	SDLGameObject* plat14_3 = new Platform(new LoaderParams(5800, -1200, 100, 50, "platform"));

	SDLGameObject* plat15 = new Platform(new LoaderParams(7700, -1200, 100, 50, "platform"));
	SDLGameObject* plat15_1 = new Platform(new LoaderParams(7800, -1200, 100, 50, "platform"));
	SDLGameObject* plat15_2 = new Platform(new LoaderParams(7900, -1200, 100, 50, "platform"));
	SDLGameObject* plat15_3 = new Platform(new LoaderParams(8000, -1200, 100, 50, "platform"));

	SDLGameObject* plat16 = new Platform(new LoaderParams(3100, 300, 100, 50, "platform"));
	SDLGameObject* plat16_1 = new Platform(new LoaderParams(3200, 300, 100, 50, "platform"));

	SDLGameObject* plat17 = new Platform(new LoaderParams(5500, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_1 = new Platform(new LoaderParams(5660, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_2 = new Platform(new LoaderParams(5820, 190, 160, 160, "greenbox"));

	SDLGameObject* plat17_3 = new Platform(new LoaderParams(6140, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_4 = new Platform(new LoaderParams(6300, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_5 = new Platform(new LoaderParams(6460, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_6 = new Platform(new LoaderParams(6620, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_7 = new Platform(new LoaderParams(6780, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_8 = new Platform(new LoaderParams(6940, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_9 = new Platform(new LoaderParams(7100, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_10 = new Platform(new LoaderParams(7260, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_11 = new Platform(new LoaderParams(7420, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_12 = new Platform(new LoaderParams(7580, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_13 = new Platform(new LoaderParams(7740, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_14 = new Platform(new LoaderParams(7900, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_15 = new Platform(new LoaderParams(8060, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_16 = new Platform(new LoaderParams(8220, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_17 = new Platform(new LoaderParams(8380, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_18 = new Platform(new LoaderParams(8540, 190, 160, 160, "greenbox"));
	SDLGameObject* plat17_19 = new Platform(new LoaderParams(5980, 190, 160, 160, "greenbox"));

	SDLGameObject* plat18 = new Platform(new LoaderParams(8700, 800, 400, 50, "platform"));

	//SDLGameObject* plat19 = new Platform(new LoaderParams(8300, -1600, 50, 1200, "platform"));

	SDLGameObject* plat20 = new Platform(new LoaderParams(6800, -500, 200, 50, "platform"));

	//SDLGameObject* plat21 = new Platform(new LoaderParams(5500, -200, 2500, 50, "platform"));

	//SDLGameObject* plat22 = new Platform(new LoaderParams(7600, -100, 200, 50, "platform"));

	SDLGameObject* plat23 = new Platform(new LoaderParams(9400, 600, 100, 50, "platform"));

	SDLGameObject* plat24 = new Platform(new LoaderParams(10000, 400, 100, 50, "platform"));

	SDLGameObject* plat25 = new Platform(new LoaderParams(8600, -300, 200, 50, "platform"));

	SDLGameObject* plat26 = new Platform(new LoaderParams(9400, -500, 100, 50, "platform"));

	SDLGameObject* plat27 = new Platform(new LoaderParams(10000, -400, 100, 50, "platform"));

	SDLGameObject* plat28 = new Platform(new LoaderParams(3300, 190, 160, 160, "bluebox"));
	SDLGameObject* plat28_1 = new Platform(new LoaderParams(3300, 30, 160, 160, "bluebox"));
	SDLGameObject* plat28_2 = new Platform(new LoaderParams(3300, -130, 160, 160, "bluebox"));
	SDLGameObject* plat28_3 = new Platform(new LoaderParams(3300, -290, 160, 160, "bluebox"));
	SDLGameObject* plat29 = new Platform(new LoaderParams(4240, -860, 160, 160, "bluebox"));
	SDLGameObject* plat29_1 = new Platform(new LoaderParams(4240, -700, 160, 160, "bluebox"));


	SDLGameObject* plat30 = new Platform(new LoaderParams(7700, -400, 200, 50, "platform"));
	SDLGameObject* plat31 = new Platform(new LoaderParams(10200,100, 100, 50, "platform"));

	SDLGameObject* winPlat = new Platform(new LoaderParams(10500, -120, 500, 50, "finish"));
	SDLGameObject* light = new Platform(new LoaderParams(10500, -220, 100, 79, "light"));
	
	SDLGameObject* haz = new Hazard(new LoaderParams(1400, 500, 100, 100, "hazard"));
	SDLGameObject* haz1 = new Hazard(new LoaderParams(2200, 300, 100, 100, "hazard"));
	SDLGameObject* haz2= new Hazard(new LoaderParams(2700, -100, 100, 100, "hazard"));
	SDLGameObject* haz3 = new Hazard(new LoaderParams(2710, 500, 60, 60, "hazard3"));
	SDLGameObject* haz4 = new Hazard(new LoaderParams(3000, 400, 60, 60, "hazard3"));
	SDLGameObject* haz5 = new Hazard(new LoaderParams(4000, 200, 100, 100, "hazard"));
	SDLGameObject* haz6 = new Hazard(new LoaderParams(4500, 100, 100, 100, "hazard"));
	SDLGameObject* haz7 = new Hazard(new LoaderParams(5000, 0, 100, 100, "hazard"));
	SDLGameObject* haz8 = new Hazard(new LoaderParams(5400, -100, 100, 100, "hazard"));
	SDLGameObject* haz9 = new Hazard(new LoaderParams(4130, -500, 100, 100, "hazard"));

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
	SDLGameObject* haz22 = new Hazard(new LoaderParams(3345, -450, 74, 85, "hazard2"));
	SDLGameObject* haz23 = new Hazard(new LoaderParams(3100, -750, 60, 60, "hazard3"));
	SDLGameObject* haz24 = new Hazard(new LoaderParams(3200, -750, 60, 60, "hazard3"));
	SDLGameObject* haz25 = new Hazard(new LoaderParams(3300, -750, 60, 60, "hazard3"));

	SDLGameObject* haz26 = new Hazard(new LoaderParams(5500, -1150, 60, 60, "hazard3"));
	SDLGameObject* haz27 = new Hazard(new LoaderParams(5500, -1050, 60, 60, "hazard3"));
	SDLGameObject* haz28 = new Hazard(new LoaderParams(5500, -950, 60, 60, "hazard3"));
	SDLGameObject* haz29 = new Hazard(new LoaderParams(5500, -850, 60, 60, "hazard3"));
	SDLGameObject* haz30 = new Hazard(new LoaderParams(5500, -750, 60, 60, "hazard3"));
	SDLGameObject* haz31 = new Hazard(new LoaderParams(5500, -650, 60, 60, "hazard3"));
	SDLGameObject* haz32 = new Hazard(new LoaderParams(5500, -550, 60, 60, "hazard3"));
	SDLGameObject* haz33 = new Hazard(new LoaderParams(5500, -450, 60, 60, "hazard3"));
	SDLGameObject* haz34 = new Hazard(new LoaderParams(5500, -350, 60, 60, "hazard3"));
	SDLGameObject* haz35 = new Hazard(new LoaderParams(5500, -250, 60, 60, "hazard3"));
	SDLGameObject* haz36 = new Hazard(new LoaderParams(5500, -150, 60, 60, "hazard3"));
	SDLGameObject* haz37 = new Hazard(new LoaderParams(5500, -50, 60, 60, "hazard3"));
	SDLGameObject* haz38 = new Hazard(new LoaderParams(5500, 50, 60, 60, "hazard3"));
	SDLGameObject* haz39 = new Hazard(new LoaderParams(5500, 150, 60, 60, "hazard3"));

	//SDLGameObject* plat17 = new Platform(new LoaderParams(5500, 190, 160, 160, "greenbox"));
	SDLGameObject* haz40 = new Hazard(new LoaderParams(5500, 122, 64, 28, "hazard4"));
	SDLGameObject* haz41 = new Hazard(new LoaderParams(5564, 122, 64, 28, "hazard4"));
	SDLGameObject* haz42 = new Hazard(new LoaderParams(5628, 122, 64, 28, "hazard4"));
	SDLGameObject* haz43 = new Hazard(new LoaderParams(5692, 105, 74, 85, "hazard2"));

	SDLGameObject* haz44 = new Hazard(new LoaderParams(5766, 122, 64, 28, "hazard4"));
	SDLGameObject* haz45 = new Hazard(new LoaderParams(5830, 122, 64, 28, "hazard4"));
	SDLGameObject* haz46 = new Hazard(new LoaderParams(5894, 122, 64, 28, "hazard4"));
	SDLGameObject* haz47 = new Hazard(new LoaderParams(5958, 105, 74, 85, "hazard2"));

	SDLGameObject* haz48 = new Hazard(new LoaderParams(6032, 122, 64, 28, "hazard4"));
	SDLGameObject* haz49 = new Hazard(new LoaderParams(6096, 122, 64, 28, "hazard4"));
	SDLGameObject* haz50 = new Hazard(new LoaderParams(6160, 122, 64, 28, "hazard4"));
	SDLGameObject* haz51 = new Hazard(new LoaderParams(6224, 105, 74, 85, "hazard2"));

	SDLGameObject* haz52 = new Hazard(new LoaderParams(6298, 122, 64, 28, "hazard4"));
	SDLGameObject* haz53 = new Hazard(new LoaderParams(6362, 122, 64, 28, "hazard4"));
	SDLGameObject* haz54 = new Hazard(new LoaderParams(6426, 122, 64, 28, "hazard4"));
	SDLGameObject* haz55 = new Hazard(new LoaderParams(6490, 105, 74, 85, "hazard2"));

	SDLGameObject* haz56 = new Hazard(new LoaderParams(6564, 122, 64, 28, "hazard4"));
	SDLGameObject* haz57 = new Hazard(new LoaderParams(6628, 122, 64, 28, "hazard4"));
	SDLGameObject* haz58 = new Hazard(new LoaderParams(6692, 122, 64, 28, "hazard4"));
	SDLGameObject* haz59 = new Hazard(new LoaderParams(6756, 105, 74, 85, "hazard2"));

	SDLGameObject* haz60 = new Hazard(new LoaderParams(6830, 122, 64, 28, "hazard4"));
	SDLGameObject* haz61 = new Hazard(new LoaderParams(6894, 122, 64, 28, "hazard4"));
	SDLGameObject* haz62 = new Hazard(new LoaderParams(6958, 122, 64, 28, "hazard4"));
	SDLGameObject* haz63 = new Hazard(new LoaderParams(7022, 105, 74, 85, "hazard2"));

	SDLGameObject* haz64 = new Hazard(new LoaderParams(7096, 122, 64, 28, "hazard4"));
	SDLGameObject* haz65 = new Hazard(new LoaderParams(7160, 122, 64, 28, "hazard4"));
	SDLGameObject* haz66 = new Hazard(new LoaderParams(7224, 122, 64, 28, "hazard4"));
	SDLGameObject* haz67 = new Hazard(new LoaderParams(7288, 105, 74, 85, "hazard2"));

	SDLGameObject* haz68 = new Hazard(new LoaderParams(7362, 122, 64, 28, "hazard4"));
	SDLGameObject* haz69 = new Hazard(new LoaderParams(7426, 122, 64, 28, "hazard4"));
	SDLGameObject* haz70 = new Hazard(new LoaderParams(7490, 122, 64, 28, "hazard4"));
	SDLGameObject* haz71 = new Hazard(new LoaderParams(7554, 105, 74, 85, "hazard2"));

	SDLGameObject* haz72 = new Hazard(new LoaderParams(7628, 122, 64, 28, "hazard4"));
	SDLGameObject* haz73 = new Hazard(new LoaderParams(7692, 122, 64, 28, "hazard4"));
	SDLGameObject* haz74 = new Hazard(new LoaderParams(7756, 122, 64, 28, "hazard4"));
	SDLGameObject* haz75 = new Hazard(new LoaderParams(7820, 105, 74, 85, "hazard2"));

	SDLGameObject* haz76 = new Hazard(new LoaderParams(7894, 122, 64, 28, "hazard4"));
	SDLGameObject* haz77 = new Hazard(new LoaderParams(7958, 122, 64, 28, "hazard4"));
	SDLGameObject* haz78 = new Hazard(new LoaderParams(8022, 122, 64, 28, "hazard4"));
	SDLGameObject* haz79 = new Hazard(new LoaderParams(8086, 105, 74, 85, "hazard2"));

	SDLGameObject* haz80 = new Hazard(new LoaderParams(8160, 122, 64, 28, "hazard4"));
	SDLGameObject* haz81 = new Hazard(new LoaderParams(8224, 122, 64, 28, "hazard4"));
	SDLGameObject* haz82 = new Hazard(new LoaderParams(8288, 122, 64, 28, "hazard4"));
	SDLGameObject* haz83 = new Hazard(new LoaderParams(8352, 105, 74, 85, "hazard2"));

	SDLGameObject* haz84 = new Hazard(new LoaderParams(8426, 122, 64, 28, "hazard4"));
	SDLGameObject* haz85 = new Hazard(new LoaderParams(8490, 122, 64, 28, "hazard4"));
	SDLGameObject* haz86 = new Hazard(new LoaderParams(8554, 122, 64, 28, "hazard4"));
	SDLGameObject* haz87 = new Hazard(new LoaderParams(8618, 105, 74, 85, "hazard2"));

	SDLGameObject* haz88 = new Hazard(new LoaderParams(6140, 700, 74, 85, "hazard2"));
	SDLGameObject* haz89 = new Hazard(new LoaderParams(6780, 700, 74, 85, "hazard2"));
	SDLGameObject* haz90 = new Hazard(new LoaderParams(7420, 700, 74, 85, "hazard2"));
	SDLGameObject* haz91 = new Hazard(new LoaderParams(8060, 700, 74, 85, "hazard2"));
	SDLGameObject* haz92 = new Hazard(new LoaderParams(8540, 700, 74, 85, "hazard2"));

	SDLGameObject* haz93 = new Hazard(new LoaderParams(8300, -1600, 60, 60, "hazard3"));
	SDLGameObject* haz94 = new Hazard(new LoaderParams(8300, -1500, 60, 60, "hazard3"));
	SDLGameObject* haz95 = new Hazard(new LoaderParams(8300, -1400, 60, 60, "hazard3"));
	SDLGameObject* haz96 = new Hazard(new LoaderParams(8300, -1300, 60, 60, "hazard3"));
	SDLGameObject* haz97 = new Hazard(new LoaderParams(8300, -1200, 60, 60, "hazard3"));
	SDLGameObject* haz98 = new Hazard(new LoaderParams(8300, -1100, 60, 60, "hazard3"));
	SDLGameObject* haz99 = new Hazard(new LoaderParams(8300, -1000, 60, 60, "hazard3"));
	SDLGameObject* haz100 = new Hazard(new LoaderParams(8300, -900, 60, 60, "hazard3"));
	SDLGameObject* haz101 = new Hazard(new LoaderParams(8300, -800, 60, 60, "hazard3"));
	SDLGameObject* haz102 = new Hazard(new LoaderParams(8300, -700, 60, 60, "hazard3"));
	SDLGameObject* haz103 = new Hazard(new LoaderParams(8300, -800, 60, 60, "hazard3"));






	gameObjects->push_back(background);

	gameObjects->push_back(plat);
	gameObjects->push_back(plat_1);
	gameObjects->push_back(plat_2);
	gameObjects->push_back(plat_3);
	gameObjects->push_back(plat_4);

	gameObjects->push_back(plat1);
	gameObjects->push_back(plat1_1);

	gameObjects->push_back(plat2);
	gameObjects->push_back(plat2_1);

	gameObjects->push_back(plat3);
	gameObjects->push_back(plat3_1);

	gameObjects->push_back(plat4);
	gameObjects->push_back(plat4_1);
	gameObjects->push_back(plat4_2);
	gameObjects->push_back(plat4_3);
	gameObjects->push_back(plat4_4);

	gameObjects->push_back(plat5);
	gameObjects->push_back(plat5_1);

	gameObjects->push_back(plat6);
	gameObjects->push_back(plat6_1);

	gameObjects->push_back(plat7);

	gameObjects->push_back(plat8);

	gameObjects->push_back(plat9);

	gameObjects->push_back(plat10);

	gameObjects->push_back(plat11);

	gameObjects->push_back(plat12);
	gameObjects->push_back(plat12_1);
	gameObjects->push_back(plat12_2);
	gameObjects->push_back(plat12_3);
	gameObjects->push_back(plat12_4);

	//gameObjects->push_back(plat13);

	gameObjects->push_back(plat14);
	gameObjects->push_back(plat14_1);
	gameObjects->push_back(plat14_2);
	gameObjects->push_back(plat14_3);

	gameObjects->push_back(plat15);
	gameObjects->push_back(plat15_1);
	gameObjects->push_back(plat15_2);
	gameObjects->push_back(plat15_3);

	gameObjects->push_back(plat16);
	gameObjects->push_back(plat16_1);

	gameObjects->push_back(plat17);
	gameObjects->push_back(plat17_1);
	gameObjects->push_back(plat17_2);
	gameObjects->push_back(plat17_3);
	gameObjects->push_back(plat17_4);
	gameObjects->push_back(plat17_5);
	gameObjects->push_back(plat17_6);
	gameObjects->push_back(plat17_7);
	gameObjects->push_back(plat17_8);
	gameObjects->push_back(plat17_9);
	gameObjects->push_back(plat17_10);
	gameObjects->push_back(plat17_11);
	gameObjects->push_back(plat17_12);
	gameObjects->push_back(plat17_13);
	gameObjects->push_back(plat17_14);
	gameObjects->push_back(plat17_15);
	gameObjects->push_back(plat17_16);
	gameObjects->push_back(plat17_17);
	gameObjects->push_back(plat17_18);
	gameObjects->push_back(plat17_19);

	gameObjects->push_back(plat18);

	//gameObjects->push_back(plat19);

	gameObjects->push_back(plat20);

	//gameObjects->push_back(plat21);

	//gameObjects->push_back(plat22);

	gameObjects->push_back(plat23);

	gameObjects->push_back(plat24);

	gameObjects->push_back(plat25);

	gameObjects->push_back(plat26);

	gameObjects->push_back(plat27);
	
	gameObjects->push_back(plat28);
	gameObjects->push_back(plat28_1);
	gameObjects->push_back(plat28_2);
	gameObjects->push_back(plat28_3);
	gameObjects->push_back(plat29);
	gameObjects->push_back(plat29_1);

	gameObjects->push_back(plat30);
	gameObjects->push_back(plat31);

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
	gameObjects->push_back(haz22);
	gameObjects->push_back(haz23);
	gameObjects->push_back(haz24);
	gameObjects->push_back(haz25);
	gameObjects->push_back(haz26);
	gameObjects->push_back(haz27);
	gameObjects->push_back(haz28);
	gameObjects->push_back(haz29);
	gameObjects->push_back(haz30);
	gameObjects->push_back(haz31);
	gameObjects->push_back(haz32);
	gameObjects->push_back(haz33);
	gameObjects->push_back(haz34);
	gameObjects->push_back(haz35);
	gameObjects->push_back(haz36);
	gameObjects->push_back(haz37);
	gameObjects->push_back(haz38);
	gameObjects->push_back(haz39);
	gameObjects->push_back(haz40);
	gameObjects->push_back(haz41);
	gameObjects->push_back(haz42);
	gameObjects->push_back(haz43);
	gameObjects->push_back(haz44);
	gameObjects->push_back(haz45);
	gameObjects->push_back(haz46);
	gameObjects->push_back(haz47);
	gameObjects->push_back(haz48);
	gameObjects->push_back(haz49);
	gameObjects->push_back(haz50);
	gameObjects->push_back(haz51);
	gameObjects->push_back(haz52);
	gameObjects->push_back(haz53);
	gameObjects->push_back(haz54);
	gameObjects->push_back(haz55);
	gameObjects->push_back(haz56);
	gameObjects->push_back(haz57);
	gameObjects->push_back(haz58);
	gameObjects->push_back(haz59);
	gameObjects->push_back(haz60);
	gameObjects->push_back(haz61);
	gameObjects->push_back(haz62);
	gameObjects->push_back(haz63);
	gameObjects->push_back(haz64);
	gameObjects->push_back(haz65);
	gameObjects->push_back(haz66);
	gameObjects->push_back(haz67);
	gameObjects->push_back(haz68);
	gameObjects->push_back(haz69);
	gameObjects->push_back(haz70);
	gameObjects->push_back(haz71);
	gameObjects->push_back(haz72);
	gameObjects->push_back(haz73);
	gameObjects->push_back(haz74);
	gameObjects->push_back(haz75);
	gameObjects->push_back(haz76);
	gameObjects->push_back(haz77);
	gameObjects->push_back(haz78);
	gameObjects->push_back(haz79);
	gameObjects->push_back(haz80);
	gameObjects->push_back(haz81);
	gameObjects->push_back(haz82);
	gameObjects->push_back(haz83);
	gameObjects->push_back(haz84);
	gameObjects->push_back(haz85);
	gameObjects->push_back(haz86);
	gameObjects->push_back(haz87);
	gameObjects->push_back(haz88);
	gameObjects->push_back(haz89);
	gameObjects->push_back(haz90);
	gameObjects->push_back(haz91);
	gameObjects->push_back(haz92);
	gameObjects->push_back(haz93);
	gameObjects->push_back(haz94);
	gameObjects->push_back(haz95);
	gameObjects->push_back(haz96);
	gameObjects->push_back(haz97);
	gameObjects->push_back(haz98);
	gameObjects->push_back(haz99);
	gameObjects->push_back(haz100);
	gameObjects->push_back(haz101);
	gameObjects->push_back(haz102);
	gameObjects->push_back(haz103);
	gameObjects->push_back(light);


	platforms->push_back(plat);
	platforms->push_back(plat_1);
	platforms->push_back(plat_2);
	platforms->push_back(plat_3);
	platforms->push_back(plat_4);

	platforms->push_back(plat1);
	platforms->push_back(plat1_1);

	platforms->push_back(plat2);
	platforms->push_back(plat2_1);

	platforms->push_back(plat3);
	platforms->push_back(plat3_1);

	platforms->push_back(plat4);
	platforms->push_back(plat4_1);
	platforms->push_back(plat4_2);
	platforms->push_back(plat4_3);
	platforms->push_back(plat4_4);

	platforms->push_back(plat5);
	platforms->push_back(plat5_1);

	platforms->push_back(plat6);
	platforms->push_back(plat6_1);

	platforms->push_back(plat7);

	platforms->push_back(plat8);

	platforms->push_back(plat9);

	platforms->push_back(plat10);

	platforms->push_back(plat11);

	platforms->push_back(plat12);
	platforms->push_back(plat12_1);
	platforms->push_back(plat12_2);
	platforms->push_back(plat12_3);
	platforms->push_back(plat12_4);

//	platforms->push_back(plat13);

	platforms->push_back(plat14);
	platforms->push_back(plat14_1);
	platforms->push_back(plat14_2);
	platforms->push_back(plat14_3);

	platforms->push_back(plat15);
	platforms->push_back(plat15_1);
	platforms->push_back(plat15_2);
	platforms->push_back(plat15_3);

	platforms->push_back(plat16);
	platforms->push_back(plat16_1);

	platforms->push_back(plat17);
	platforms->push_back(plat17_1);
	platforms->push_back(plat17_2);
	platforms->push_back(plat17_3);
	platforms->push_back(plat17_4);
	platforms->push_back(plat17_5);
	platforms->push_back(plat17_6);
	platforms->push_back(plat17_7);
	platforms->push_back(plat17_8);
	platforms->push_back(plat17_9);
	platforms->push_back(plat17_10);
	platforms->push_back(plat17_11);
	platforms->push_back(plat17_12);
	platforms->push_back(plat17_13);
	platforms->push_back(plat17_14);
	platforms->push_back(plat17_15);
	platforms->push_back(plat17_16); 
	platforms->push_back(plat17_17);
	platforms->push_back(plat17_18);
	platforms->push_back(plat17_19);


	platforms->push_back(plat18);

	//platforms->push_back(plat19);

	platforms->push_back(plat20);

	//platforms->push_back(plat21);

	//platforms->push_back(plat22);

	platforms->push_back(plat23);

	platforms->push_back(plat24);

	platforms->push_back(plat25);

	platforms->push_back(plat26);

	platforms->push_back(plat27);

	platforms->push_back(plat28);
	platforms->push_back(plat28_1);
	platforms->push_back(plat28_2);
	platforms->push_back(plat28_3);
	platforms->push_back(plat29);
	platforms->push_back(plat29_1);
	platforms->push_back(plat30);
	platforms->push_back(plat31);

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
	hazards->push_back(haz22);
	hazards->push_back(haz23);
	hazards->push_back(haz24);
	hazards->push_back(haz25);
	hazards->push_back(haz26);
	hazards->push_back(haz27);
	hazards->push_back(haz28);
	hazards->push_back(haz29);
	hazards->push_back(haz30);
	hazards->push_back(haz31);
	hazards->push_back(haz32);
	hazards->push_back(haz33);
	hazards->push_back(haz34);
	hazards->push_back(haz35);
	hazards->push_back(haz36);
	hazards->push_back(haz37);
	hazards->push_back(haz38);
	hazards->push_back(haz39);
	hazards->push_back(haz40);
	hazards->push_back(haz41);
	hazards->push_back(haz42);
	hazards->push_back(haz43);
	hazards->push_back(haz44);
	hazards->push_back(haz45);
	hazards->push_back(haz46);
	hazards->push_back(haz47);
	hazards->push_back(haz48);
	hazards->push_back(haz49);
	hazards->push_back(haz50);
	hazards->push_back(haz51);
	hazards->push_back(haz52);
	hazards->push_back(haz53);
	hazards->push_back(haz54);
	hazards->push_back(haz55);
	hazards->push_back(haz56);
	hazards->push_back(haz57);
	hazards->push_back(haz58);
	hazards->push_back(haz59);
	hazards->push_back(haz60);
	hazards->push_back(haz61);
	hazards->push_back(haz62);
	hazards->push_back(haz63);
	hazards->push_back(haz64);
	hazards->push_back(haz65);
	hazards->push_back(haz66);
	hazards->push_back(haz67);
	hazards->push_back(haz68);
	hazards->push_back(haz69);
	hazards->push_back(haz70);
	hazards->push_back(haz71);
	hazards->push_back(haz72);
	hazards->push_back(haz73);
	hazards->push_back(haz74);
	hazards->push_back(haz75);
	hazards->push_back(haz76);
	hazards->push_back(haz77);
	hazards->push_back(haz78);
	hazards->push_back(haz79);
	hazards->push_back(haz80);
	hazards->push_back(haz81);
	hazards->push_back(haz82);
	hazards->push_back(haz83);
	hazards->push_back(haz84);
	hazards->push_back(haz85);
	hazards->push_back(haz86);
	hazards->push_back(haz87);
	hazards->push_back(haz88);
	hazards->push_back(haz89);
	hazards->push_back(haz90);
	hazards->push_back(haz91);
	hazards->push_back(haz92);
	hazards->push_back(haz93);
	hazards->push_back(haz94);
	hazards->push_back(haz95);
	hazards->push_back(haz96);
	hazards->push_back(haz97);
	hazards->push_back(haz98);
	hazards->push_back(haz99);
	hazards->push_back(haz100);
	hazards->push_back(haz101);
	hazards->push_back(haz102);
	hazards->push_back(haz103);

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