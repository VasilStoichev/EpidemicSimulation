#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"


using namespace ci;

const float PERSON_RADIUS = 7.0f;
const float MIN_SPEED = 2.0f;
const float MAX_SPEED = 2.5f;

enum SIRGroup {
	Susceptible,
	Infected,
	Recovered
};

class Person {
private:
	vec2 location;
	vec2 velocity;
	vec2 acceleration;

	float radius;
	SIRGroup state;
	unsigned infectedSince;
	float speedVariation;

	void correctOutOfBounds();
	void correctSpeed();
public:
	Person(vec2, SIRGroup);

	void update();
	void draw();


	vec2 getLocation();
	vec2 getAcceleration();
	vec2 getVelocity();
	SIRGroup getState();
	unsigned getInfectedSince();

	void setLocation(vec2);
	void setAcceleration(vec2);
	void setVelocity(vec2);
	void setState(SIRGroup);
};