#include "SIRGraph.h"

SIRGraph::SIRGraph()
{
	this->pointsInfected.push_back(vec2(40.0f, 670.0f));
	this->pointsRecovered.push_back(vec2(40.0f, 670.0f));
	this->startFrame = 0;
}

void SIRGraph::init(unsigned _frame)
{
	this->startFrame = _frame;
}

void SIRGraph::update(unsigned infected,unsigned recovered,unsigned total)
{
	float x = 40.0f + 1.0f * (ci::app::getElapsedFrames() - this->startFrame);
	float yR = 670 - (recovered / (float)total) * 250.0f;
	float yI = yR - (infected / (float)total) * 250.0f;

	
	Path2d r;
	r.moveTo(pointsRecovered.back().x, 670.0);
	r.lineTo(pointsRecovered.back());
	r.lineTo(vec2(x, yR));
	r.lineTo(vec2(x, 670.0));
	r.lineTo(pointsRecovered.back().x, 670.0);
	this->recoveredSections.push_back(r);

	Path2d i;
	i.moveTo(pointsRecovered.back());
	i.lineTo(pointsInfected.back());
	i.lineTo(vec2(x, yI));
	i.lineTo(vec2(x, yR));
	i.lineTo(pointsRecovered.back());
	this->infectedSections.push_back(i);

	Path2d s;
	s.moveTo(pointsInfected.back());
	s.lineTo(vec2(pointsInfected.back().x, 410.0f));
	s.lineTo(vec2(x, 410.0f));
	s.lineTo(vec2(x, yI));
	s.lineTo(pointsInfected.back());
	this->susceptibleSections.push_back(s);

	pointsRecovered.push_back(vec2(x, yR));
	pointsInfected.push_back(vec2(x, yI));
}

void SIRGraph::draw()
{
	gl::lineWidth(3);
	gl::color(Color(0.4f, 0.4f, 0.4f));
	for (auto p : this->recoveredSections)
	{
		gl::drawSolid(p);
	}
	gl::color(Color(1, 0, 0));
	for (auto p : this->infectedSections)
	{
		gl::drawSolid(p);
	}
	gl::color(Color(1, 1, 1));
	for (auto p : this->susceptibleSections)
	{
		gl::drawSolid(p);
	}
	gl::lineWidth(1);
}
