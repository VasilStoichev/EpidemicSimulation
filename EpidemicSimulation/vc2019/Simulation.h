#pragma once
#include "PersonController.h"
#include "SIRGraph.h"

class Simulation {
private:
	PersonController controller;
	SIRGraph graph;
	unsigned maxPeople;
	unsigned startFrame;
	int count;
public:
	Simulation();

	void init(unsigned chance,unsigned duration,unsigned max,unsigned frame);
	void update();
	void draw();

};