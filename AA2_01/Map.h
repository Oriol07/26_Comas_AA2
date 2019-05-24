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

struct Map 
{
 private:
	#pragma region Variables
		int filas; // numero de files que tindra el tauler.
		int columnas; // numero de columnes que tindra el tauler.
		std::vector<Blinky> eBlinky; 
		std::vector<Inky> eInky;
		std::vector<Clyde> eClyde;

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
		bool bordeMapa(vec2 pos, Direction dir);
		bool existPunt(vec2 pos, Direction dir);
		bool noExistMur(vec2 pos, Direction dir);
		bool touchEnemy(vec2 pos, Direction dir);
		bool playerTouchEnemy();
	#pragma endregion

		int getCols();
		int getRows();
	#pragma region Position functions
		void setPlayer(vec2 pos);
		void movePlayer(vec2 &pos_, Direction move);
		void moveAI(Player player);
		void moveBlinky(Blinky &blink);
		void moveInky(Inky &ink);
		void moveClyde(Clyde &clyd, Player player);
		char NextCharPosition(Direction dir, vec2 p);
		void setFirstDirBlinky(Blinky &blink);

	#pragma endregion

	#pragma region Read and Print function
		void printMap();
	#pragma endregion
};