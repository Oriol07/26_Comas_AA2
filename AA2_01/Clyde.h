#pragma once

#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "Player.h"
#include "Constants.h"


class Clyde
{

private:
#pragma region Variables
	Direction mov;
	vec2 pos; //(x,y)
	char charStepped;


public:  
	Clyde();
	Clyde(int posX, int posY, int lifes);   

	void setPosition(vec2 position);

	vec2 getPosition();

	void setDir(Direction d);

	Direction getDir();

	void setCharStepped(char step);
	
	char getCharStepped();

	bool touchPlayer();

	~Clyde();

};