#include "Simulation.h"

Simulation::Simulation()
{
	this->maxPeople = 0;
	this->count = 0;
}

void Simulation::init(unsigned chance, unsigned duration, unsigned max, unsigned frame)
{
	controller.init(chance / 100.0f, duration);
	graph.init(frame);
	this->maxPeople = max;
	this->startFrame = frame;
}

void Simulation::update()
{
	if (app::getElapsedFrames() % 30 == 0)
	{
		CountByGroup groups = controller.getCount();
		graph.update(groups.infected,groups.recovered,maxPeople);
		if (app::getElapsedFrames() < this->startFrame + 600)
		{
			count++;
			controller.addPeople(maxPeople / 20, count == 3);
		}
	}
	controller.update();
}

void Simulation::draw()
{
	controller.draw();
	graph.draw();
}
