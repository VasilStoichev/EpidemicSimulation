#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "../vc2019/Simulation.h"
#include "cinder/params/Params.h"
#include "cinder/app/Platform.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class EpidemicSimulationApp : public App {
 public:
	Simulation sim;
	params::InterfaceGlRef mParams;
	unsigned mDuration;
	unsigned mMaxPeople;
	unsigned mChance;
	unsigned mMasked;
	unsigned mMaskEffect;
	unsigned mRadius;
	unsigned mInterval;
	unsigned frame;
	std::vector<std::string> simTypes;
	int typeSelection;

	bool started;
	bool init;
	bool firstUse;
	void setup() override;
	void button();
	void reset();
	void typeSelected();


	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

};


void EpidemicSimulationApp::button()
{
	mParams->setOptions("Click Here to Reset", "visible=true");
	mParams->setOptions("Click Here to Start", "visible=false");
	init = 1;
	started = 1;
}
void EpidemicSimulationApp::reset()
{
	/*mParams->setOptions("Click Here to Reset", "visible=false");
	mParams->setOptions("Click Here to Start", "visible=true");*/
	mParams->clear();
	mParams->addParam("Simulation type", simTypes, &typeSelection);
	mParams->addSeparator();
	mParams->addButton("Select", std::bind(&EpidemicSimulationApp::typeSelected, this));
	
	this->sim.reset();
	started = 0;
	frame = 0;
}
void EpidemicSimulationApp::typeSelected()
{
	std::string selected = simTypes[typeSelection];
	mParams->clear();
	mParams->addParam("Decease duration(s)", &mDuration).min(0).max(20).step(1);
	mParams->addParam("Spread Chance(%)", &mChance).min(1).max(100).step(5);
	mParams->addParam("Spread Interval(s)", &mInterval).min(1).max(40).step(1);
	if (selected == "Corridor")
	{
		mParams->addParam("Number of people", &mMaxPeople).min(1).max(200).step(10);
		mParams->addSeparator();
		mParams->addParam("People with masks(%)", &mMasked).min(0).max(100).step(5);
		mParams->addParam("Mask effectiveness(%)", &mMaskEffect).min(0).max(100).step(5);
		mParams->addParam("Spread radius", &mRadius).min(0).max(100).step(5);
	}
	else if (selected == "Exam")
	{

	}
	
	mParams->addSeparator();
	mParams->addButton("Click Here to Start", std::bind(&EpidemicSimulationApp::button, this));
	mParams->addButton("Click Here to Reset", std::bind(&EpidemicSimulationApp::reset, this));
	mParams->setOptions("Click Here to Reset", "visible=false");
	mParams->addText("Duration = 0 for no recovery");
}
void EpidemicSimulationApp::setup()
{
	mDuration = 1;
	mChance = 1;
	started = false;
	firstUse = true;
	init = 0;
	mMaxPeople = 150;
	frame = 0;
	mMasked = 0;
	mMaskEffect = 0;
	mRadius = 50;
	mInterval = 1;
	setWindowSize(1280, 720);
	setFrameRate(30);
	//params
	mParams = params::InterfaceGl::create(getWindow(), "Params", toPixels(ivec2(300, 350)),ColorA(0.3f, 0.3f, 0.3f, 1.0f));
	simTypes = { "Corridor","Exam" };
	typeSelection = 0;
	mParams->addParam("Simulation type", simTypes, &typeSelection);
	mParams->addSeparator();
	mParams->addButton("Select", std::bind(&EpidemicSimulationApp::typeSelected, this));
	mParams->addSeparator();
	mParams->addText("Corridor-people moving left to right");
	mParams->addText("Exam-static simulation with people in rows");
	
}

void EpidemicSimulationApp::mouseDown( MouseEvent event )
{
}

void EpidemicSimulationApp::update()
{
	if (started)
	{

			if (init)
			{
				mParams->minimize();
				this->frame = getElapsedFrames();
				sim.init(mChance,mDuration,mMaxPeople,this->frame,mMasked,mMaskEffect,mRadius,mInterval,simTypes[typeSelection]);
				init = 0;
			}
			if (getElapsedFrames() - frame > 1500) mParams->maximize();
		sim.update();
	}
	setWindowSize(1280, 720);
}

void EpidemicSimulationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	
	if (started && getElapsedFrames() > frame)sim.draw();
	mParams->draw();
}

CINDER_APP( EpidemicSimulationApp, RendererGl )
