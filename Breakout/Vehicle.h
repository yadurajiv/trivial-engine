#ifndef VEHICLE_H
#define VEHICLE_H 

#include "TrivialEngine.h"

using namespace std;


class Vehicle : public Trivial::Sprite
{
private:
	int velocity;
public:
	Vehicle();
	~Vehicle();
	
	void setVelocity(int aVelocity);
	int getVelocity();
	void image(const string &name, int X, int lane);
	
	virtual void update();
	
};

Vehicle::Vehicle()
{
	velocity = 0;
}

void Vehicle::setVelocity(int aVelocity)
{
	velocity = aVelocity;
	setMaxVelocity(velocity, 0);
}

int Vehicle::getVelocity()
{
	return velocity;
}

void Vehicle::image(const string &name, int X, int lane)
{
	Sprite::image(name);
	int Y;
	if(lane == 0)
		Y = 250;
	else
		if(lane == 2)
			Y = 450;
		else
			Y = 350;

	moveTo(X, Y);
	setAcceleration(-1,0);
	setMaxVelocity(velocity,0);
}

void Vehicle::update()
{

}

Vehicle::~Vehicle()
{
	
}

#endif