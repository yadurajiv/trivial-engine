#ifndef ASTEROIDS_H
#define ASTEROIDS_H
#define MAXASTEROIDS 255

#include "TrivialEngine.h"
#include <math.h>

class asteroids : public Trivial::Sprite
{
private:
Trivial::EventManager *myEventManager;
int rx;
int ry;
int i;
int originX;
int originY;
bool isActive;


public:
asteroids();
~asteroids();

void update();
void image(const string &name, int side);
void setIsActive(bool aValue);
bool getIsActive();

};

asteroids::asteroids()
{
myEventManager = Trivial::EventManager::Instance();
    isActive = true;
}

asteroids::~asteroids()
{

}

void asteroids::setIsActive(bool aValue)
{
    isActive = aValue;
}

bool asteroids::getIsActive()
{
    return isActive;
}

void asteroids::image(const string &name, int side=0)
{
Sprite::image(name);
 //cout<<"iiiiiiiiiiiiiiiiiiiiii"<<i;
         rx = rand() % (100) ;
         //cout<<"rxxxxxxxxxxxx"<<rx;
         ry = rand() % (100) ;
         //cout<<"rxxxxxyyyyyyyyyyyyy"<<ry;
        //moveTo(rx, ry);
        switch(side)
        {
            case 0  :   setAcceleration(1, 1);
                        setMaxVelocity(rx, ry);
                        break;
            case 1  :   moveTo(800, Y());
                        setAcceleration(-1, 1);
                        setMaxVelocity(rx, ry);
                        break;
            case 2  :   moveTo(X(), 600);
                        setAcceleration(1, -1);
                        setMaxVelocity(rx, ry);
                        break;
            case 3  :   moveTo(800, 600);
                        setAcceleration(-1, -1);
                        setMaxVelocity(rx, ry);
                        break;
        }
        originX = X();
        originY = Y();
}


void asteroids::update() {

    if(X() > 810 || X() < -10 || Y() > 610 || Y() < -10)
    {
        moveTo(originX, originY);
    }

    if(!isActive)
    {
        moveTo(originX, originY);
        isActive = true;
    }

}

#endif
