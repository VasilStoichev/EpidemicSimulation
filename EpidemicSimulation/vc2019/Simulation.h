#pragma once
#include "PersonController.h"
#include "SIRGraph.h"

class Simulation {
private:
	PersonController controller;
	SIRGraph graph;
	std::string type;

	unsigned maxPeople;
	float masked;
	unsigned startFrame;
	int count;
public:
	Simulation();

	void init(unsigned chance,unsigned duration,unsigned max,unsigned frame,unsigned masked, unsigned maskEffect,unsigned radius,unsigned interval,std::string type);
	void update();
	void draw();
	void reset();
};