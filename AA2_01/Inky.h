

#pragma once

#include <conio.h>
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

	char charStepped;
#pragma endregion


public:
	Inky();
	Inky(int posX, int posY, int lifes); // Per si volem posar nosaltres la posició, i el numero de vides.

#pragma region Position functions
	//void UpdatePosition(); //On es fan els events de input
	//char NextCharPosition(Direction dir);
	void SetPosition(vec2 position);
	vec2 GetPosition();
	void SetInitPos(vec2 position);
	void ReturnInitPos();
	vec2 GetInitPos();

	void SetDir(Direction d);
	Direction GetDir();

	void SetCharStepped(char a);
	char GetCharStepped();
	bool TouchPlayer();

#pragma region Destructor
	~Inky();

#pragma endregion
};
