#ifndef CAR_H
#define CAR_H 

#include "TrivialEngine.h"
#include "Vehicle.h"
using namespace std;

class Car : public Vehicle
{
private:
	
public:
	Car();
	~Car();
	void image(const string &name, int X, int lane);
	void update();
};

Car::Car()
{

}

void Car::image(const string &name, int X, int lane)
{
	Vehicle::image(name, X, lane);
}

void Car::update()
{
	
}

Car::~Car()
{
	
}
#endif