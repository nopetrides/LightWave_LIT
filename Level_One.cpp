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
	if (!TheTextureManager::Instance()->load("assets/Instruct_Move.png", "Instruc1", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Instruct_Jump.png", "Instruc2", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Instruc_Hold.png", "Instruc3", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Instruct_Double.png", "Instruc4", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Instruct_Dash.png", "Instruc5", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Instruct_Aim.png", "Instruc6", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Instruct_Fire.png", "Instruc7", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}
	if (!TheTextureManager::Instance()->load("assets/Instruct_Death.png", "death", TheGame::Instance()->getRenderer())) {
		std::cout << "Error: " << SDL_GetError();
	}

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

	//Load the hazard texture
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

void Level_One::createObjects(std::vector<SDLGameObject* >* gameObjects, std::vector<SDLGameObject*>* platforms, std::vector<SDLGameObject*>* hazards)
{
	//Create objects in the level. 
	// This is where we will create a vector of all platforms for ease of coding
	// then shove them into the game objects vector. 
	SDLGameObject* background = new Platform(new LoaderParams(0, 0, 1920, 1080, "background"));

	// Starting Platform
	SDLGameObject* plat = new Platform(new LoaderParams(400, 900, 100, 40, "platform"));
	SDLGameObject* plat1 = new Platform(new LoaderParams(500, 900, 100, 40, "platform"));
	SDLGameObject* plat2 = new Platform(new LoaderParams(600, 900, 100, 40, "platform"));
	SDLGameObject* plat3 = new Platform(new LoaderParams(700, 900, 100, 40, "platform"));
	SDLGameObject* plat4 = new Platform(new LoaderParams(800, 900, 100, 40, "platform"));
	SDLGameObject* plat5 = new Platform(new LoaderParams(900, 900, 100, 40, "platform"));
	SDLGameObject* plat6 = new Platform(new LoaderParams(1000, 900, 100, 40, "platform"));
	SDLGameObject* plat7 = new Platform(new LoaderParams(1100, 900, 100, 40, "platform"));
	SDLGameObject* plat8 = new Platform(new LoaderParams(1200, 900, 100, 40, "platform"));
	SDLGameObject* plat9 = new Platform(new LoaderParams(1300, 900, 100, 40, "platform"));
	SDLGameObject* plat10 = new Platform(new LoaderParams(1400, 900, 100, 40, "platform"));
	SDLGameObject* plat11 = new Platform(new LoaderParams(1500, 900, 100, 40, "platform"));
	SDLGameObject* plat12 = new Platform(new LoaderParams(1600, 900, 100, 40, "platform"));
	// First Jump
	SDLGameObject* plat13 = new Platform(new LoaderParams(2300, 900, 100, 40, "platform"));
	SDLGameObject* plat14 = new Platform(new LoaderParams(2400, 900, 100, 40, "platform"));
	SDLGameObject* plat15 = new Platform(new LoaderParams(2500, 900, 100, 40, "platform"));
	// Second Jump
	SDLGameObject* plat16 = new Platform(new LoaderParams(3700, 900, 100, 40, "platform"));
	SDLGameObject* plat17 = new Platform(new LoaderParams(3800, 900, 100, 40, "platform"));
	SDLGameObject* plat18 = new Platform(new LoaderParams(3900, 900, 100, 40, "platform"));
	SDLGameObject* plat19 = new Platform(new LoaderParams(4000, 900, 100, 40, "platform"));
	// Double Jump
	SDLGameObject* box1 = new Platform(new LoaderParams(4000, 780, 160, 160, "bluebox"));
	SDLGameObject* box2 = new Platform(new LoaderParams(4000, 620, 160, 160, "bluebox"));
	SDLGameObject* box3 = new Platform(new LoaderParams(3700, 340, 160, 160, "bluebox"));
	SDLGameObject* box5 = new Platform(new LoaderParams(4160, 460, 160, 160, "bluebox"));
	SDLGameObject* box6 = new Platform(new LoaderParams(4160, 300, 160, 160, "bluebox"));
	SDLGameObject* box7 = new Platform(new LoaderParams(4160, 140, 160, 160, "bluebox"));
	//SDLGameObject* box8 = new Platform(new LoaderParams(4160, -20, 160, 160, "bluebox"));
	SDLGameObject* box9 = new Platform(new LoaderParams(4160, 780, 160, 160, "bluebox"));
	SDLGameObject* box10 = new Platform(new LoaderParams(4160, 620, 160, 160, "bluebox"));
	// Dash
	SDLGameObject* box11 = new Platform(new LoaderParams(4100, -420, 160, 160, "greenbox"));
	SDLGameObject* box12 = new Platform(new LoaderParams(4260, -420, 160, 160, "greenbox"));
	SDLGameObject* box13 = new Platform(new LoaderParams(4420, -420, 160, 160, "greenbox"));
	SDLGameObject* box14 = new Platform(new LoaderParams(4580, -420, 160, 160, "greenbox"));
	SDLGameObject* box15 = new Platform(new LoaderParams(4740, -420, 160, 160, "greenbox"));
	SDLGameObject* box16 = new Platform(new LoaderParams(4900, -420, 160, 160, "greenbox"));
	SDLGameObject* box17 = new Platform(new LoaderParams(4100, -580, 160, 160, "greenbox"));
	SDLGameObject* plat20 = new Platform(new LoaderParams(4900, -120, 100, 40, "platform"));
	SDLGameObject* plat21 = new Platform(new LoaderParams(5000, -120, 100, 40, "platform"));
	// Hook
	SDLGameObject* plat22 = new Platform(new LoaderParams(6000, -700, 100, 40, "platform"));
	SDLGameObject* plat23 = new Platform(new LoaderParams(6100, -700, 100, 40, "platform"));
	SDLGameObject* plat24 = new Platform(new LoaderParams(6200, -700, 100, 40, "platform"));
	SDLGameObject* box18 = new Platform(new LoaderParams(6000, -1500, 160, 160, "bluebox"));
	SDLGameObject* box19 = new Platform(new LoaderParams(6320, -1340, 160, 160, "bluebox"));
	SDLGameObject* box20 = new Platform(new LoaderParams(6320, -1180, 160, 160, "bluebox"));
	SDLGameObject* box21 = new Platform(new LoaderParams(6320, -1020, 160, 160, "bluebox"));
	SDLGameObject* box22 = new Platform(new LoaderParams(6320, -860, 160, 160, "bluebox"));
	// Finish
	SDLGameObject* winPlat = new Platform(new LoaderParams(5500, -1800, 100, 40, "finish"));
	// Instructions
	SDLGameObject* intruct1 = new Platform(new LoaderParams(400, 600, 400, 300, "Instruc1"));
	SDLGameObject* intruct2 = new Platform(new LoaderParams(1400, 600, 400, 300, "Instruc2"));
	SDLGameObject* intruct3 = new Platform(new LoaderParams(2300, 600, 400, 300, "Instruc3"));
	SDLGameObject* intruct4 = new Platform(new LoaderParams(3500, 600, 400, 300, "Instruc4"));
	SDLGameObject* intruct5 = new Platform(new LoaderParams(4800, 0, 400, 300, "Instruc5"));
	SDLGameObject* intruct6 = new Platform(new LoaderParams(5700, -1000, 400, 300, "Instruc6"));
	SDLGameObject* intruct7 = new Platform(new LoaderParams(6480, -1000, 400, 300, "Instruc7"));

	//Hazards
	
	SDLGameObject* haz1 = new Hazard(new LoaderParams(3100, 700, 100, 100, "hazard"));
	SDLGameObject* haz2 = new Hazard(new LoaderParams(4143, -700, 74, 85, "hazard2"));
	SDLGameObject* haz3 = new Hazard(new LoaderParams(6050, -1320, 60, 60, "hazard3"));
	SDLGameObject* haz4 = new Hazard(new LoaderParams(1716, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz5 = new Hazard(new LoaderParams(1780, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz6 = new Hazard(new LoaderParams(1844, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz7 = new Hazard(new LoaderParams(1908, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz8 = new Hazard(new LoaderParams(1972, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz9 = new Hazard(new LoaderParams(2036, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz10 = new Hazard(new LoaderParams(2100, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz11 = new Hazard(new LoaderParams(2164, 1000, 64, 28, "hazard4"));
	SDLGameObject* haz12 = new Hazard(new LoaderParams(2228, 1000, 64, 28, "hazard4"));

	//Death Warnings
	SDLGameObject* death1 = new Platform(new LoaderParams(1980, 1050, 150, 100, "death"));
	SDLGameObject* death2 = new Platform(new LoaderParams(4125, -800, 150, 100, "death"));
	SDLGameObject* death3 = new Platform(new LoaderParams(6030, -1250, 150, 100, "death"));
	SDLGameObject* death4 = new Platform(new LoaderParams(3080, 800, 150, 100, "death"));


	gameObjects->push_back(background);
	gameObjects->push_back(intruct1);
	gameObjects->push_back(intruct2);
	gameObjects->push_back(intruct3);
	gameObjects->push_back(intruct4);
	gameObjects->push_back(intruct5);
	gameObjects->push_back(intruct6);
	gameObjects->push_back(intruct7);

	// Starting Platform
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
	gameObjects->push_back(death1);
	gameObjects->push_back(death2);
	gameObjects->push_back(death3);
	gameObjects->push_back(death4);

	gameObjects->push_back(box1);
	gameObjects->push_back(box2);
	gameObjects->push_back(box3);
	gameObjects->push_back(box5);
	gameObjects->push_back(box6);
	gameObjects->push_back(box7);
	//gameObjects->push_back(box8);
	gameObjects->push_back(box9);
	gameObjects->push_back(box10);
	gameObjects->push_back(box11);
	gameObjects->push_back(box12);
	gameObjects->push_back(box13);
	gameObjects->push_back(box14);
	gameObjects->push_back(box15);
	gameObjects->push_back(box16);
	gameObjects->push_back(box17);
	gameObjects->push_back(box18);
	gameObjects->push_back(box19);
	gameObjects->push_back(box20);
	gameObjects->push_back(box21);
	gameObjects->push_back(box22);

	gameObjects->push_back(winPlat);

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

	platforms->push_back(box1);
	platforms->push_back(box2);
	platforms->push_back(box3);
	platforms->push_back(box5);
	platforms->push_back(box6);
	platforms->push_back(box7);
	//platforms->push_back(box8);
	platforms->push_back(box9);
	platforms->push_back(box10);
	platforms->push_back(box11);
	platforms->push_back(box12);
	platforms->push_back(box13);
	platforms->push_back(box14);
	platforms->push_back(box15);
	platforms->push_back(box16);
	platforms->push_back(box17);
	platforms->push_back(box18);
	platforms->push_back(box19);
	platforms->push_back(box20);
	platforms->push_back(box21);
	platforms->push_back(box22);

	platforms->push_back(winPlat);

	//Adding the hazards to the hazard vector
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