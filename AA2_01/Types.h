#pragma once

//Vector que ens servira per determinar la direcció a la que anira el jugador.
enum class Direction
{
	UP,DOWN,LEFT,RIGHT,ZERO
};

//Struct que ens servira per les cordenadas x i y
struct vec2 
{
	int x;
	int y;
};