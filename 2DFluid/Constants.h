#pragma once
#include "Vec2.h"
#include <iostream>

const int N = 512;
extern Vec2f gravity;

extern int WINDOW_SIZE_X ;
extern int WINDOW_SIZE_Y ;

extern int originX;
extern int originY;
extern int unitLength;
extern int mx, my;
extern bool clickD;
extern bool clickV;


//y is rows, x is cols
//row * width + col
inline int index(int x, int y) {
	int index = (static_cast<int>(y * N) + x);
	//if (index < 0)index = 0;
	//if (index > 511)index = 511;
	return index;
}