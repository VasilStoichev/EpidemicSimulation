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
	void setup() override;
	void button();
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;

};


void EpidemicSimulationApp::button()
{
	init = 1;
	started = 1;
}
void EpidemicSimulationApp::setup()
{
	mDuration = 1;
	mChance = 1;
	started = false;
	init = 0;
	mMaxPeople = 150;
	frame = 0;
	setWindowSize(1280, 720);
	setFrameRate(30);
	//params
	mParams = params::InterfaceGl::create(getWindow(), "Params", toPixels(ivec2(300, 400)));
	mParams->addParam("Decease duration(s)", &mDuration).min(1).max(20).step(1);
	mParams->addParam("Spread Chance(%)", &mChance).min(1).max(100).step(5);
	mParams->addParam("Number of people", &mMaxPeople).min(0).max(300).step(10);
	mParams->addSeparator();
	mParams->addButton("Click Here to Start", std::bind(&EpidemicSimulationApp::button, this));
}

void EpidemicSimulationApp::mouseDown( MouseEvent event )
{
}

void EpidemicSimulationApp::update()
{
	if (started)
	{

		if (((frame + getElapsedFrames()) % 30 == 0 && getElapsedFrames() < frame + 600) || init)
		{
			if (init)
			{
				mParams->hide();
				mParams->clear();
				this->frame = getElapsedFrames();
				sim.init(mChance,mDuration,mMaxPeople,this->frame);
				init = 0;
			}
		}
		sim.update();
	}
}

void EpidemicSimulationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
	mParams->draw();
	if (started && getElapsedFrames() > frame)sim.draw();
	
}

CINDER_APP( EpidemicSimulationApp, RendererGl )
