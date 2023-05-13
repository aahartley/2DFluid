#include "Fluid.h"


Fluid::Fluid(float dt, float diffusion, float viscosity) {
	this->dt = dt;
	this->diff = diffusion;
	this->visc = viscosity;

	this->density0 = new float[N * N];
	this->density = new float[N * N];

	this->Vx = new float[(N + 1) *N];
	this->Vy = new float[(N + 1) * N];

	this->Vx0 = new float[(N + 1) * N];
	this->Vy0 = new float[(N + 1) * N];

	for (int x = 0; x < N;x++) {
		for (int y = 0; y < N; y++) {
			if (x == 0 || y == 0 || x == N - 1 || y == N - 1) {
				density[index(x, y)] = 0;
				density0[index(x, y)] = 0;
		
			}
			density[index(x,y)] = 1000;
			density0[index(x,y)] = 1000;
		}
	}
	//solenoidal velocity field
	for (int x = 0; x < N+1; x++) {
		for (int y = 0; y < N+1; y++) {
			if (x == 0 || y == 0 || x == (N+1)-1  || y == (N+1)-1 ) {
				//boundary walls 
				Vx[index(x,y)] = 0;
				Vy[index(x,y)] = 0;
			}
			Vx[index(x,y)] = -5; Vx0[index(x,y)] = 0;
			Vy[index(x, y)] = 5; Vy0[index(x, y)] = 0;
		}
	}

}
void Fluid::addQuantity(int x, int y, float dens) {
	density0[index(x, y)] += dens;
}

//Solve material derivative Dq/dt=0
//backwards particle trace
//semi-lagrangian advection
void Fluid::advect() {
	//ignore boundary walls
	for (int x = 1; x < N-1; x++) {
		for (int y = 1; y < N-1; y++) {
			//position we want to find new density for
			Vec2f position{ static_cast<float>(x),static_cast<float>(y) };
	


			//euler to find prevPos
			float prevPosX = position.x - Vx[index(x, y)] * dt;
			float prevPosY = position.y - Vy[index(x, y)] * dt;
			if (prevPosX < 1)prevPosX = 1;
			if (prevPosY < 1) prevPosY = 1;
			if (prevPosX > 511)prevPosX = 510;
			if (prevPosY >511) prevPosY = 510;
			Vec2f prevPos(prevPosX,prevPosY );

			//indexes of the 4 densities to interpolate with to find density of prevPos
			//converting to int to give  me top left point
			Vec2f position1{ static_cast<float>(static_cast<int>(prevPos.x)),static_cast<float>(static_cast<int>(prevPos.y)) };
			Vec2f position2{ static_cast<float>(position1.x + 1),static_cast<float>(position1.y) };
			Vec2f position3{ static_cast<float>(position1.x + 1),static_cast<float>(position1.y + 1) };
			Vec2f position4{ static_cast<float>(position1.x),static_cast<float>(position1.y + 1) };
			Vec2f distance1 = (position1 - prevPos).normalize();
			Vec2f distance2 = (position2 - prevPos).normalize();
			Vec2f distance3 = (position3 - prevPos).normalize();
			Vec2f distance4 = (position4 - prevPos).normalize();


			//bilinear interpolation to find old density
			//                   0,0        1,0     1,1      0,1 
			//f(x,y) = (1-x)(1-y)f1 + x(1-y)f2 + xyf3 + (1-x)yf4
		
			density[index(x, y)] = ((1.0f- distance1.x)*(1.0f- distance1.y)*density0[index(position1.x, position1.y)]) +
				(distance2.x*(1.0f- distance2.y)*density0[index(position2.x, position2.y)]) +
				(distance3.x* distance3.y*density0[index(position3.x, position3.y)]) +
				((1.0f- distance4.x)* distance4.y*density0[index(position4.x, position4.y)]);
			if (x == 255 && y>254) {
				//std::cout << density[index(x, y)] << '\n';
			}
		}
	}
	//swap
	density0 = density;


}

void Fluid::integrateBodyForces() {
	for (int i = 0; i < (N + 1) * N; i++) {
		Vx[i] += gravity.x * dt;
		Vx[i] += gravity.y * dt;

	}
}

void Fluid::project() {

}

Fluid::~Fluid() {
	delete[] density0;
	delete[] density;
	delete[] Vx;
	delete[] Vy;
	delete[] Vx0;
	delete[] Vy0;

}


