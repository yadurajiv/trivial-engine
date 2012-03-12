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

   	float _autoAttackCost;
   	float _autoAttackPeace;

public:
	bool isHit;
	AutoCab();
	~AutoCab();
	void image(const string &name, int X, int lane);
	void setAttackCost(float aCost);
	void setAttackPeace(float aPeace);
	float getTotalAttackCost();
	float getTotalAttackPeace();
	void update();
	void mouseEventCallBack(const Trivial::TrivialMouseEvent &e);
};

AutoCab::AutoCab()
{
	myEventManager = Trivial::EventManager::Instance();
	myEventManager->subscribe("left-buttondown-mouse", this);
	myEventManager->subscribe("left-buttonup-mouse", this);
	isHit = false;
}

void AutoCab::image(const string &name, int X, int lane)
{
	Vehicle::image(name, X, lane);
}

void AutoCab::setAttackCost(float aCost)
{
	_autoAttackCost = aCost;
}

void AutoCab::setAttackPeace(float aPeace)
{
	_autoAttackPeace = aPeace;
}

float AutoCab::getTotalAttackCost()
{
	return _autoAttackCost;
}

float AutoCab::getTotalAttackPeace()
{
	return _autoAttackPeace;
}

void AutoCab::update()
{
	_autoAttackPeace += _autoAttackPeace/500;
	_autoAttackCost += _autoAttackCost/500;
}

void AutoCab::mouseEventCallBack(const Trivial::TrivialMouseEvent &e)
{
    if(e.eventName == "left-buttondown-mouse") {
        if(pointOverlap(e.pos.x, e.pos.y,true))
        {
			isHit = true;
        }
	}
}

AutoCab::~AutoCab()
{

}
#endif
