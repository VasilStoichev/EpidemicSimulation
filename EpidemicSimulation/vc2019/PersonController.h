#pragma once
#include "Person.h"

const float REPEL_RADIUS = 600.0f;
const float INFECTION_RADIUS = 2600.0f;

struct CountByGroup {
	unsigned susceptible;
	unsigned infected;
	unsigned recovered;

	CountByGroup();
};

class PersonController {
private:
	std::list<Person*> people;
	unsigned personCount;

	CountByGroup SIRcount;
	float infectionChance;
	unsigned infectionDuration;

	void repelPeople();
public:
	PersonController();
	~PersonController();

	void addPeople(unsigned, unsigned);
	void init(float, unsigned);
	void update();
	void draw();
	void reset();
	CountByGroup getCount();
};