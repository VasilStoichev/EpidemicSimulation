#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class EpidemicSimulationApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void EpidemicSimulationApp::setup()
{
}

void EpidemicSimulationApp::mouseDown( MouseEvent event )
{
}

void EpidemicSimulationApp::update()
{
}

void EpidemicSimulationApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( EpidemicSimulationApp, RendererGl )
