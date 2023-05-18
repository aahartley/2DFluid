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

	for (int y = 0; y < N;y++) {
		for (int x = 0; x < N; x++) {
			if (x <= 2 || y <= 2 || x >= N - 3 || y >= N - 3) {
				density[index(x, y)] = 0;
				density0[index(x, y)] = 0;
		
			}
			else {
				density[index(x, y)] = 0;
				density0[index(x, y)] = 1000;
			}
		}
	}
	//solenoidal velocity field
	for (int y = 0; y < N+1; y++) {
		for (int x = 0; x < N+1; x++) {
			//include wall of vel for the end of densitty cell
			if (x <= 3 || y <= 3 || x >= (N+1)-4  || y >= (N+1)-4 ) {
				//boundary walls 
				Vx[index(x,y)] = 0;
				Vy[index(x,y)] = 0;
			}
			else {
				Vx[index(x, y)] = -50; Vx0[index(x, y)] = -50;
				Vy[index(x, y)] = 30; Vy0[index(x, y)] = 30;
			}
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
	//ignore boundary walls [0-2,509-511]
	//[3-508]

	for (int y = 3; y < N - 3; y++) {
		for (int x = 3; x < N - 3; x++) {
			if (x == 3 ||y==3|| x == N - 4 || y == N - 4) {
				int a = 0;
				int b = 0;
				if (y == 3 || x==3) {
					if (y == N - 4)a++;
					if (x == N - 4)b++;
					//std::cout << y << ' ' << x << ' ' << Vx[index(x+b, y)] << ' ' << Vy[index(x, y+a )] << '\n';
				}
			
				//std::cout << y << ' ' << x << ' ' << Vx[index(x, y)] << ' ' << Vy[index(x, y + a)] << '\n';

			}
		}
	}

	for (int y = 3; y < N-3; y++) {
		for (int x = 3; x < N - 3; x++) {



			//position we want to find new density for
			Vec2f position{ static_cast<float>(x),static_cast<float>(y) };



			//euler to find prevPos
			float prevPosX, prevPosY;
			if (x == 508) {
				prevPosX = position.x - Vx[index(x + 1, y)] * dt;
			}
			else {
				prevPosX = position.x - Vx[index(x, y)] * dt;
			}

			if (y == 508) {
				prevPosY = position.y - Vy[index(x, y + 1)] * dt;

			}
			else {
				prevPosY = position.y - Vy[index(x, y)] * dt;
			}
			if (y >= 506 && density[index(x, y)] < 1000.0f)
			{ //&& density[index(x,y)]>=1000.0f) 
				//std::cout << prevPosY << '\n';
				int a = 0;
				if (y == 508)a++;
				//std::cout << Vy[index(x, y+a)] << '\n';
			}
			if (prevPosX < 3)prevPosX = 3;
			if (prevPosY < 3) prevPosY = 3;
			if (prevPosX > 508)prevPosX = 508;
			if (prevPosY >508) prevPosY = 508;

			Vec2f prevPos(prevPosX,prevPosY );
			if (prevPosX < 3 || prevPosY < 3 || prevPosX >508 || prevPosY>508)continue;
			//std::cout << x << ' ' << prevPos.x << '\n';
			//indexes of the 4 densities to interpolate with to find density of prevPos
			//converting to int to give  me top left point
			Vec2f position1{ static_cast<float>(static_cast<int>(prevPos.x)),static_cast<float>(static_cast<int>(prevPos.y)) };
			Vec2f position2{ static_cast<float>(position1.x + 1),static_cast<float>(position1.y) };
			Vec2f position3{ static_cast<float>(position1.x + 1),static_cast<float>(position1.y + 1) };
			Vec2f position4{ static_cast<float>(position1.x),static_cast<float>(position1.y + 1) };
		
			//convert prevPos between 0-1

			//Vec2f prevPosN = prevPos.normal();


			float xxx = (position1.x + 1) - position1.x;
			float xx = (prevPos.x - position1.x) / xxx;
			float yyy = (position1.y + 1) - position1.y;
			float yy = (prevPos.y - position1.y) / yyy;

			Vec2f distance(xx, yy);
			//std::cout << xx + yy << '\n';
			//std::cout << prevPosN.x << '\n';

			//bilinear interpolation to find old density
			//                   0,0        1,0     1,1      0,1 
			//f(x,y) = (1-x)(1-y)f1 + x(1-y)f2 + xyf3 + (1-x)yf4
			if (prevPos.x == position.x && prevPos.y == position.y) {
				//if(x==3 && y==3)	std::cout << density0[index(3, 3)] << '\n';
				density[index(x, y)] = density0[index(x, y)];
			}
			//if (prevPos.y >= 400) { density[index(x, y)] = density0[index(prevPos.x, prevPos.y)]; //std::cout << '1' << '\n';
			//}

			//else if(prevPos.x==3 || prevPos.y ==3||prevPos.x==508||prevPos.y==508)				density[index(x, y)] = density0[index(x, y)];

			else{
				//std::cout << '2' << '\n';
				density[index(x, y)] = ((1.0f - distance.x) * (1.0f - distance.y) * density0[index(position4.x, position4.y)]) +
					(distance.x * (1.0f - distance.y) * density0[index(position3.x, position3.y)]) +
					(distance.x * distance.y * density0[index(position2.x, position2.y)]) +
					((1.0f - distance.x) * distance.y * density0[index(position1.x, position1.y)]);
	/*			density[index(x, y)] = ((1.0f - distance.x) * (1.0f - distance.y) * density0[index(position1.x, position1.y)]) +
					(distance.x * (1.0f - distance.y) * density0[index(position4.x, position4.y)]) +
					(distance.x * distance.y * density0[index(position3.x, position3.y)]) +
					((1.0f - distance.x) * distance.y * density0[index(position2.x, position2.y)]);*/
					//swap
				totalD += density[index(x, y)];

			}
			if (density[index(x, y)] >= 1000.1f && x<20) {
				//std::cout << y << ' ' << x <<  ' '<<density[index(x, y)] << "\n";
			}

		}
	}
	//swap
	std::cout << totalD << '\n';
	totalD = 0;
	float* tmp = density0;
	density0 = density;
	density = tmp;
	//memcpy(density0, density, sizeof(density0));
	//for (int y = 3; y < N - 3; y++) {
	//	for (int x = 3; x < N - 3; x++) {
	//		density0[index(x, y)] = density[index(x, y)];
	//	}
	//}
	if (density[index(4, 4)] >= 1000.0f) {
	/*	std::cout << density[index(4, 4)] << '\n';
		std::cout << density0[index(4, 4)] << '\n';

		std::cout << "end\n";*/

	}
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


