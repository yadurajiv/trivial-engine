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
	int _distanceTravelled;
	int _dropAt;
	bool _occupied;
	int _type;
	bool _moveToCenter;
	int _moveToCenterDistance;

public:
	bool isHit;
	AutoCab();
	~AutoCab();
	void image(const string &name, int X, int lane);
	void setDropAt(int aValue);
	void setAttackCost(float aCost);
	void setAttackPeace(float aPeace);
	float getTotalAttackCost();
	float getTotalAttackPeace();
	bool getOccupiedState();
	void update();
	void mouseEventCallBack(const Trivial::TrivialMouseEvent &e);
	void resetDistance();
	void setMoveToCenter(bool aValue = true);
};

AutoCab::AutoCab()
{
	myEventManager = Trivial::EventManager::Instance();
	myEventManager->subscribe("left-buttondown-mouse", this);
	myEventManager->subscribe("left-buttonup-mouse", this);
	isHit = false;
	_distanceTravelled = 0;
	_dropAt = -1;
	_occupied = false;
	_moveToCenter = false;
}

void AutoCab::resetDistance()
{
	_distanceTravelled = 0;
	_occupied = false;
	isHit = false;
}

void AutoCab::image(const string &name, int X, int lane)
{
	Vehicle::image(name, X, lane);
}

void AutoCab::setDropAt(int aValue)
{
	_dropAt = aValue;
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
	
	if(_dropAt > 0)
	{
		if(_distanceTravelled >= _dropAt)
		{
			_occupied = true;
		}
	}
	
	//Move object to center
	if(_moveToCenter)
	{
		if(X() >= 450 || X() <= 350)
		{
			if(X() > 450)
			{
				moveTo(X()-1, Y());
			}
			else
			{
				moveTo(X()+1, Y());
			}
		}
		else
		{
			_moveToCenter = false;
		}
	}
	
	_distanceTravelled++;
}

bool AutoCab::getOccupiedState()
{
	return _occupied;
}

void AutoCab::mouseEventCallBack(const Trivial::TrivialMouseEvent &e)
{
	if(!_occupied){
    	if(e.eventName == "left-buttondown-mouse") {
        	if(pointOverlap(e.pos.x, e.pos.y,true))
        	{
				isHit = true;
        	}
		}
	}
}

void AutoCab::setMoveToCenter(bool aValue)
{
	_moveToCenter = aValue;
}

AutoCab::~AutoCab()
{

}
#endif
