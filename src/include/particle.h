#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H

#include "sprite.h"

class Particle : public Sprite
{
public:
	Particle();
	Particle( Image * image, double velx, double vely, double angularVel, double lifetime, bool autofade );
	virtual ~Particle() {}

	virtual double GetLifetime() const { return lifetime; };

	virtual void Update( double elapsed );

	void SetAngVel( double angvel ) { angularVelocity = angvel; }

private:
	double velocityx, velocityy;
	double angularVelocity;
	double lifetime;
	double initialLifetime;
	bool autofade;
};

#endif