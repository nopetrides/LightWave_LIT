//
//  GameObject.h
//  SDL Game Programming Book
//
//  Created by shaun mitchell on 31/12/2012.
//  Copyright (c) 2012 shaun mitchell. All rights reserved.
//

#ifndef SDL_Game_Programming_Book_GameObject_h
#define SDL_Game_Programming_Book_GameObject_h

#include <iostream>
#include "SDL.h"
#include "LoaderParams.h"
class GameObject
{
public:
	virtual void draw()=0; //pure virtual function
	virtual void update()=0;//pure virtual function
	virtual void clean()=0;//pure virtual function

protected:
	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}
};

#endif /* defined(__SDL_Game_Programming_Book__Chapter_3_GameObject__) */