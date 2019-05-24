#pragma once
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "Constants.h"
#include "Types.h"


struct Player 
{

#pragma region Variables
	int score; // Puntuació
	int lifes; // Les vides del jugador
	char playerRef; // '>' la referencia del personatge, com es veura per pantalla.
	char input; // variable que farem servir per guardar el input del teclat.
	Direction mov; // Enum que conté el tipus de moviment a realitzar
	vec2 pos; // Variable que tindra guardades les posicions en els eixos de les 'x' i 'y';
	bool aMoure; //Aquesta condicio es posara a true, cada cop que el jugador premi una tecla, així el moviment del jugador només funcióna quan es manté la tecla presa.
#pragma endregion

#pragma region Constructor
	Player(); // Constructor per defecte
	Player(int posX, int posY, int lifes); // Per si volem posar nosaltres la posició, i el numero de vides.
#pragma endregion

#pragma region Deconstructor
	~Player();
#pragma endregion

#pragma region Position and key events functions
	void UpdatePosition(); //On es fan els events de input
	bool isGameEnded(); //retorna escape
	void SetPosition(vec2 position);
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
	void printPlayer(); // La HUD del jugador.
#pragma endregion

};