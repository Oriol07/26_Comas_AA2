#pragma once

constexpr int TIME = 300; //Temps de refresc 

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
#define KEYPRESSED (keyboard[(int)InputKey::K_UP] || keyboard[(int)InputKey::K_DOWN] || keyboard[(int)InputKey::K_RIGHT] || keyboard[(int)InputKey::K_LEFT])
