#include "Simulation.h"

Simulation::Simulation()
{
	this->maxPeople = 0;
	this->count = 0;
}

void Simulation::init(unsigned chance, unsigned duration, unsigned max, unsigned frame, unsigned _masked, unsigned maskEffect,unsigned radius,unsigned interval, std::string _type)
{
	controller.init(chance / 100.0f, duration, interval, maskEffect/100.0f,radius,_type);
	graph.init(frame);
	this->maxPeople = _type == "Exam" ? 144 : max;
	this->startFrame = frame;
	this->type = _type;
	this->masked = _masked / 100.0f;
}

void Simulation::update()
{
	if (app::getElapsedFrames() % 30 == 0)
	{
	

		if (type == "Exam" && count == 0)
		{
			controller.addExam();
			count++;
		}
		if (type == "Corridor" && app::getElapsedFrames() < this->startFrame + 600)
		{
			count++;
			unsigned toAdd = maxPeople / 20;
			controller.addPeople(toAdd, count == 3,toAdd * this->masked);
		}
		CountByGroup groups = controller.getCount();
		graph.update(groups.infected, groups.recovered, maxPeople);
	}
	controller.update();
}

void Simulation::draw()
{
	controller.draw();
	graph.draw();
}

void Simulation::reset()
{
	this->controller.reset();
	this->graph.reset();
	this->startFrame = 0;
	this->count = 0;
}
