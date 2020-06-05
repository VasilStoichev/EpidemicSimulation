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
	unsigned frame;
	bool started;
	bool init;
	bool firstUse;
	void setup() override;
	void button();
	void reset();
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
	mParams->setOptions("Click Here to Reset", "visible=false");
	mParams->setOptions("Click Here to Start", "visible=true");
	this->sim.reset();
	started = 0;
	frame = 0;
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
	setWindowSize(1280, 720);
	setFrameRate(30);
	//params
	mParams = params::InterfaceGl::create(getWindow(), "Params", toPixels(ivec2(300, 350)),ColorA(0.3f, 0.3f, 0.3f, 1.0f));
	mParams->addParam("Decease duration(s)", &mDuration).min(1).max(20).step(1);
	mParams->addParam("Spread Chance(%)", &mChance).min(1).max(100).step(5);
	mParams->addParam("Number of people", &mMaxPeople).min(0).max(300).step(10);
	mParams->addSeparator();
	mParams->addButton("Click Here to Start", std::bind(&EpidemicSimulationApp::button, this));
	mParams->addButton("Click Here to Reset", std::bind(&EpidemicSimulationApp::reset, this));
	mParams->setOptions("Click Here to Reset", "visible=false");
	
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
				//mParams->clear();
				this->frame = getElapsedFrames();
				sim.init(mChance,mDuration,mMaxPeople,this->frame);
				init = 0;
			}
			if (getElapsedFrames() - frame > 900) mParams->maximize();
		sim.update();
	}
}

void EpidemicSimulationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	
	if (started && getElapsedFrames() > frame)sim.draw();
	mParams->draw();
}

CINDER_APP( EpidemicSimulationApp, RendererGl )
