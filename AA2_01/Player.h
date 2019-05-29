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
	bool hasPowerUp;
	int powerUpTime;
#pragma endregion

public:
#pragma region Constructor
	Player(); // Constructor per defecte
	Player(int posX, int posY, int lifes); // Per si volem posar nosaltres la posició, i el numero de vides.
#pragma endregion

#pragma region Deconstructor
	~Player();
#pragma endregion

#pragma region Position/Collision functions
	void setPosition(vec2 position);
	vec2 getPos(); 
	void setInitPos(vec2 position);
	bool touchEnemy(); //comprova si toca l'enemic.
	bool touchPowerUp();
	void setCharStepped(char stepp);
	char getCharStepped();
	void returnInitPos();
	void setDir(Direction d);
	Direction getDir();
	bool canMove();
	void setCanMove(bool can);
#pragma endregion

#pragma region Score functions
	int getScore();
	void setScore(int score);
	void setHasPowerUp(bool powerUp);
	bool getHasPowerUp();
#pragma endregion

#pragma region Lifes functions
	int getLifes();
	void setLifes(int lifes);
#pragma endregion

#pragma region Time functions
	void setTimePowerUp(int time);
	int getTimePowerUp();
#pragma endregion

#pragma region Print
	void printPlayer(); // La HUD del jugador.
#pragma endregion

};