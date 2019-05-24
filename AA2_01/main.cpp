/***************************************************
* Grup 26.								           *
* - Desirèe Moreno						           *
* - Oriol Comas Llurià                             *
* Github: https://github.com/Oriol07/Grup26_AA2_1  *
****************************************************/

#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <vector>

#include "Constants.h"
#include "Types.h"
#include "Player.h"
#include "Blinky.h"
#include "Map.h"



int main()
{
	//Variables
	Player player;
	Map map = Map(player);
	bool game = true;
	bool Init = true;
	bool MainMenu = false;
	bool Play = false;
	bool Pause = false;
	bool GameOver = false;
	int time = 0;
	//MAIN LOOP del joc.
	do
	{
		while (Init)
		{
			std::cout << " ********* SPLASHSCREEN ********* " << std::endl;
			Sleep(200);
			std::cout << " Welcome to PACMAN";
			Sleep(200);
			std::cout << "."; Sleep(200); std::cout << "."; Sleep(200); std::cout << "."; Sleep(200);
			time++;
			if (GetAsyncKeyState(VK_SPACE))
			{
				Init = false;
				Play = true;
			}
			if (GetAsyncKeyState(VK_ESCAPE)) //"ESCAPE" // terminar el juego.
			{
				Init = false;
				game = false;
			}

			if (time == 3)
			{
				Init = false;
				Play = true;
			}
			system("cls");

		}

		while (Pause)
		{
			if (GetAsyncKeyState(VK_ESCAPE)) //"ESCAPE" // terminar el juego.
			{
				Init = false;
				game = false;
			}

			std::cout << " Pause//EN PAUSA.\n PREM 'P' per jugar" << std::endl;
			if (GetAsyncKeyState(0x50))
			{
				Play = true;
				Pause = false;
				Sleep(1000);
			}
			system("cls");
		}

		while (Play)
		{

				//Detecta el event del teclat, i determina quina sera la seguent posicio del jugador 
				if (KEYPRESSED)
				{

					if (GetAsyncKeyState(VK_UP))
					{
						player.mov = Direction::UP; //ARRIBA
						player.aMoure = true;
					}
					if (GetAsyncKeyState(VK_DOWN))
					{
						player.mov = Direction::DOWN;	//ABAJO
						player.aMoure = true;
					}
					if (GetAsyncKeyState(VK_RIGHT))
					{
						player.mov = Direction::RIGHT;	//IZQUIERDA
						player.aMoure = true;
					}
					if (GetAsyncKeyState(VK_LEFT))
					{
						player.mov = Direction::LEFT;	//DERECHA
						player.aMoure = true;
					}
					if (GetAsyncKeyState(VK_ESCAPE)) //"ESCAPE" // terminar el juego.
					{
						Play = false;
						game = false;
					}

				}
				
				else player.mov = Direction::ZERO;
				if (GetAsyncKeyState(0x50))
				{
					Play = false;
					Pause = true;
					Sleep(500);
					system("cls");
				}

				if (player.aMoure) // true cuando se detecta event del teclat
				{
					if (map.noExistMur(player.pos, player.mov)) //Si no existeix mur a la proxima posicio.
					{
						if (map.existPunt(player.pos, player.mov)) // si es punto se suma uno.
							player.SetScore(player.GetScore() + 1);
						map.movePlayer(player.pos, player.mov); // mou al player a la prox posicio
					}
					player.aMoure = false;
				}
				
				map.moveAI(player); // Es mouen els enemics.
				if (map.playerTouchEnemy())
				{
					player.lifes--;
					if (player.lifes == 0)
						Play = false;
				}
				Sleep(TIME); //Refresc del joc cada un segón.
				system("cls"); // limpiamos pantalla
				std::cout << "********* PLAY *********" << std::endl;
				map.printMap(); //printamoss MAPA
				player.printPlayer(); //printtamos HUD/Score
			
		}

	} while (game);

	system("cls"); // limpiamos pantalla
	std::cout << "Joc acabat" << std::endl;
	Sleep(2000); // Ending de 2 segons.

	return 0;
}
