#pragma once

constexpr int TIME = 400; //Temps de refresc 

//Dibuixos 
constexpr char JUGADOR = '>'; //Dibuix jugador
constexpr char PUNT = '*';
constexpr char NOTHING = ' ';
constexpr char MUR = 'X';
constexpr char BLINKY = '#';
constexpr char INKY = '&';
constexpr char CLYDE = '$';
constexpr char POWER_UP = '0';

//EVENT
#define KEYPRESSED (GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT))
