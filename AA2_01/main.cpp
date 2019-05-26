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
						player.SetDir(Direction::UP); //ARRIBA
						player.SetCanMove(true);
					}
					if (GetAsyncKeyState(VK_DOWN))
					{
						player.SetDir(Direction::DOWN);	//ABAJO
						player.SetCanMove(true);
					}
					if (GetAsyncKeyState(VK_RIGHT))
					{
						player.SetDir(Direction::RIGHT);	//IZQUIERDA
						player.SetCanMove(true);
					}
					if (GetAsyncKeyState(VK_LEFT))
					{
						player.SetDir(Direction::LEFT);	//DERECHA
						player.SetCanMove(true);
					}
					if (GetAsyncKeyState(VK_ESCAPE)) //"ESCAPE" // terminar el juego.
					{
						Play = false;
						game = false;
					}

				}
				
				else player.SetDir(Direction::ZERO);
				if (GetAsyncKeyState(0x50))
				{
					Play = false;
					Pause = true;
					Sleep(500);
					system("cls");
				}

				if (player.CanMove()) // true cuando se detecta event del teclat
				{
					if (map.NoExistMur(player.GetPos(), player.GetDir())) //Si no existeix mur a la proxima posicio.
					{
						if (map.ExistPunt(player.GetPos(), player.GetDir())) // si es punto se suma uno.
							player.SetScore(player.GetScore() + 1);
						map.MovePlayer(player); // mou al player a la prox posicio
					}
					player.SetCanMove(false);
				}
				
				map.MoveAI(player); // Es mouen els enemics.
				if (map.PlayerTouchEnemy(player))
				{
					player.SetLifes(player.GetLifes() - 1);
					
					if (player.GetLifes() == 0)
						Play = false;
				}
				Sleep(TIME); //Refresc del joc cada un segón.
				system("cls"); // limpiamos pantalla
				std::cout << "********* PLAY *********" << std::endl;
				map.PrintMap(); //printamoss MAPA
				player.PrintPlayer(); //printtamos HUD/Score
			
		}

	} while (game);

	system("cls"); // limpiamos pantalla
	std::cout << "Joc acabat" << std::endl;
	Sleep(2000); // Ending de 2 segons.

	return 0;
}
