#pragma once

#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "Player.h"
#include "Constants.h"


class Clyde
{

	private:
	#pragma region Variables
	Direction mov; // Enum que conté el tipus de moviment a realitzar
	vec2 pos; //(x,y)
	char charStepped; // char que contindra el caracter que té a sota.
	vec2 initPos; //vector que guardara la posició inicial
	bool dead; //bolea que ens dira si a mort o no
	#pragma endregion

	public:  

	#pragma region Constructor/Destructoor
		Clyde();
		~Clyde();
	#pragma endregion

	#pragma region Position/Collision functions
			void setPosition(vec2 position);
			vec2 getPosition();
			void returnInitPos();
			void setInitPos(vec2 position);
			void setDir(Direction d);
			Direction getDir();
			vec2 getInitPos();

			void setCharStepped(char a);
			char getCharStepped();
			bool touchPlayer();
	#pragma endregion

	#pragma region Other functions
			bool isDead();
			void setDead(bool d);
	#pragma endregion

};