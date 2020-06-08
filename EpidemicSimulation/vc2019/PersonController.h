#pragma once
#include "Person.h"

const float REPEL_RADIUS = 600.0f;


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
	float maskEffect;
	unsigned infectionDuration;
	unsigned spreadInterval;

	std::string simType;
	float infectionRadius;



	void repelPeople();
	void spread();
public:
	PersonController();
	~PersonController();

	void addExam();
	void addPeople(unsigned, unsigned,unsigned);
	void init(float infectionChance, unsigned infectionDuration, unsigned spreadInterval, float maskEffect,float infectionRadius, std::string simType);
	void update();
	void draw();
	void reset();
	CountByGroup getCount();
	unsigned getPersonCount();
};