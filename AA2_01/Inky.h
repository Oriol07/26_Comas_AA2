#pragma once

#include <iostream>
#include <Windows.h>
#include "Types.h"
#include "Player.h"
#include "Constants.h"

class Inky
{
	private:
	#pragma region Variables
		Direction mov; // Enum que conté el tipus de moviment a realitzar
		vec2 pos; // Variable que tindra guardades les posicions en els eixos de les 'x' i 'y'
		vec2 initPos; //vector que guardara la posició inicial
		bool dead; //bolea que ens dira si a mort o no
		char charStepped; // char que contindra el caracter que té a sota.
	#pragma endregion

	public:
	#pragma region Constructor/Destructor
		Inky();
		~Inky();
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
	#pragma endregion

	#pragma region Other functions
		bool isDead();
		void setDead(bool d);
	#pragma endregion

};
