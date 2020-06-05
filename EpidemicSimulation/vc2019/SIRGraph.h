#pragma once
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
using namespace ci;

class SIRGraph {
private:
	std::vector<vec2> pointsRecovered;
	std::vector<vec2> pointsInfected;

	std::vector<Path2d> recoveredSections;
	std::vector<Path2d> infectedSections;
	std::vector<Path2d> susceptibleSections;

	unsigned startFrame;

	void drawAxes();
public:
	SIRGraph();
	void init(unsigned);
	void update(unsigned,unsigned,unsigned);
	void draw();
	void reset();
};