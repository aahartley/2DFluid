#pragma once
#include "Constants.h"
#include "Vec2.h"

class Fluid {
public:
	Fluid(float dt, float diffusion, float viscosity);
	~Fluid();
	
	float dt;
	float diff;
	float visc;
	void advect();
	void integrateBodyForces();
	void project();
	void addQuantity(int x, int y, float density);
	void bilerp();

	//MAC Staggered grid
	float* density0;
	float* density;

	float* Vx;
	float* Vy;
	
	float* Vx0;
	float* Vy0;
};