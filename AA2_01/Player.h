#pragma once
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "Constants.h"
#include "Types.h"


class Player 
{
private:
#pragma region Variables
	int score; // Puntuació
	int lifes; // Les vides del jugador
	Direction mov; // Enum que conté el tipus de moviment a realitzar
	vec2 pos; // Variable que tindra guardades les posicions en els eixos de les 'x' i 'y';
	bool toMove; //Aquesta condicio es posara a true, cada cop que el jugador premi una tecla, així el moviment del jugador només funcióna quan es manté la tecla presa.
	char charStepped; //character que passa per sobre.
	vec2 initPos;

#pragma endregion

public:
#pragma region Constructor
	Player(); // Constructor per defecte
	Player(int posX, int posY, int lifes); // Per si volem posar nosaltres la posició, i el numero de vides.
#pragma endregion

#pragma region Deconstructor
	~Player();
#pragma endregion

#pragma region Position and move functions
	void SetPosition(vec2 position);
	vec2 GetPos(); 
	void SetInitPos(vec2 position);
	bool TouchEnemy(); //comprova si toca l'enemic.
	void SetCharStepped(char stepp);
	void ReturnInitPos();
	void SetDir(Direction d);
	Direction GetDir();
	bool CanMove();
	void SetCanMove(bool can);
#pragma endregion

#pragma region Score functions
	int GetScore();
	void SetScore(int score);
#pragma endregion

#pragma region Lifes functions
	int GetLifes();
	void SetLifes(int lifes);
#pragma endregion

#pragma region Print
	void PrintPlayer(); // La HUD del jugador.
#pragma endregion

};