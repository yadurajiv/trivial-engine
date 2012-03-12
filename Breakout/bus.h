#ifndef BUS_H
#define BUS_H 

#include "TrivialEngine.h"
#include "Vehicle.h"
using namespace std;

class Bus : public Vehicle
{
private:
	
public:
	Bus();
	~Bus();
	void image(const string &name, int X, int lane);
	void update();
};

Bus::Bus()
{
	
}

void Bus::image(const string &name, int X, int lane)
{
	Vehicle::image(name, X, lane);
}

void Bus::update()
{
	
}

Bus::~Bus()
{
	
}
#endif