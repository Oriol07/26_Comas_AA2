#pragma once

#include <iostream>
#include <windows.h> 
#include <fstream>
#include <vector>

#include "Types.h"
#include "Constants.h"
#include "Blinky.h"
#include "Player.h"
#include "Clyde.h"
#include "Inky.h"

class Map 
{
 private:
	#pragma region Variables
		int filas; // numero de files que tindra el tauler.
		int columnas; // numero de columnes que tindra el tauler.
		std::vector<Blinky> eBlinky; 
		std::vector<Inky> eInky;
		std::vector<Clyde> eClyde;
		Blinky b;
		Inky i;
		Clyde c;
		vec2 posMap;

	#pragma endregion 
	
 public:
	 char ** map;// Contindra tots els elements del tauler en un array dinamic 2D.
	#pragma region Constructor
		Map(Player &jugador);
	#pragma endregion

	#pragma region Deconstructor
		~Map();
	#pragma endregion
	
	#pragma region Collision functions
		bool BordeMapa(vec2 pos, Direction dir);
		bool ExistPunt(vec2 pos, Direction dir);
		bool NoExistMur(vec2 pos, Direction dir);
		bool TouchEnemy(vec2 pos, Direction dir);
		bool PlayerTouchEnemy(Player player);
	#pragma endregion

		int getCols();
		int getRows();
	#pragma region Position functions
		void SetPlayer(vec2 pos);
		void MovePlayer(Player &player);
		void MoveAI(Player player);
		void MoveBlinky(Blinky &blink);
		void MoveInky(Inky &ink, Player player);
		void MoveClyde(Clyde &clyd, Player player);
		char NextCharPosition(Direction dir, vec2 p);
		void SetFirstDirBlinky(Blinky &blink);

	#pragma endregion

	#pragma region Read and Print function
		void PrintMap();
	#pragma endregion
};