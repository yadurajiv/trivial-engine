#ifndef AUTOCAB_H
#define AUTOCAB_H 

#include "TrivialEngine.h"
#include "Vehicle.h"
using namespace std;

class AutoCab : public Vehicle
{
private:
	Trivial::EventManager *myEventManager;
	
public:
	AutoCab();
	~AutoCab();
	void image(const string &name, int X, int lane);
	void update();
	void mouseEventCallBack(const Trivial::TrivialMouseEvent &e);
};

AutoCab::AutoCab()
{
	myEventManager = Trivial::EventManager::Instance();
	myEventManager->subscribe("buttondown-mouse", this);
}

void AutoCab::image(const string &name, int X, int lane)
{
	Vehicle::image(name, X, lane);
}

void AutoCab::update()
{
	
}

void AutoCab::mouseEventCallBack(const Trivial::TrivialMouseEvent &e)
{
	if(pointOverlap(e.pos.x, e.pos.y))
	{
		
	}
}

AutoCab::~AutoCab()
{
	
}
#endif