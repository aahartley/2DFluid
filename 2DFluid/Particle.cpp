#include "Particle.h"

Particle::Particle() {};
Particle::Particle(float mass, Vec2f pos) :mass(mass), pos(pos) {
	acc = Vec2f{ 0.0f,0.0f};
	vel = Vec2f{ 0.0f,0.0f };
}
Particle::~Particle() {};

void Particle::integrate(float dt) {
	Vec2f forces = (gravity *mass) ;

	acc += (forces*(1 / mass));
	vel += acc * dt;
	pos += vel * dt;
}