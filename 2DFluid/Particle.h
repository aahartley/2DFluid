#pragma once
#include "Vec2.h"
#include "Constants.h"

class Particle {
public:
	Particle();
	Particle(float mass, Vec2f pos);
	~Particle();
	Vec2f acc;
	Vec2f vel;
	Vec2f pos;

	float mass;

	void integrate(float dt);

};