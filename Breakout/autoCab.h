#ifndef AUTOCAB_H
#define AUTOCAB_H

#include <string>

#include "TrivialEngine.h"
#include "Vehicle.h"

using namespace std;

class AutoCab : public Vehicle
{
private:
	Trivial::EventManager *myEventManager;

    string _autoType;
    int _autoAttackCost;
    int _autoAttackPeace;
    int _autoSpeed;
    int _autoDirection;


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
	myEventManager->subscribe("left-buttondown-mouse", this);
	myEventManager->subscribe("left-buttonup-mouse", this);
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
    if(e.eventName == "left-buttondown-mouse") {
        if(pointOverlap(e.pos.x, e.pos.y,true))
        {
            cout << "\nwhat the fuck X: " << getLocalX(e.pos.x);
        }
	}
}

AutoCab::~AutoCab()
{

}
#endif
