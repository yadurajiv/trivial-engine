#ifndef PADDLE_H
#define PADDLE_H

#include "TrivialEngine.h"

class paddle : public Trivial::Sprite
{
private:
	Trivial::EventManager *myEventManager;
	bool key_up;
    bool key_left;
    bool key_right;
	pos position;

public:
	paddle();
	~paddle();

	void update();

	void image(const string &name);
	void keyBoardEventCallback(const Trivial::TrivialKeyBoardEvent &e);
	bool getKeyUpState();
	bool getKeyLeftState();
	bool getKeyRightState();
	void setPosition(pos aPosition);
	pos getPosition();
	void setPositionBy(pos aPosition);

};

paddle::paddle()
{
	myEventManager = Trivial::EventManager::Instance();
	myEventManager->subscribe("up-keydown", this);
    myEventManager->subscribe("up-keyup", this);

	myEventManager->subscribe("left-keydown", this);
    myEventManager->subscribe("left-keyup", this);

    myEventManager->subscribe("right-keydown", this);
    myEventManager->subscribe("right-keyup", this);
}

paddle::~paddle()
{

}

void paddle::image(const string &name)
{
	Sprite::image(name);
}

void paddle::keyBoardEventCallback(const Trivial::TrivialKeyBoardEvent &e)
{
	if (e.eventName == "up-keydown") {
        key_up = true;
    }
    if (e.eventName == "up-keyup") {
        key_up = false;
    }

    if (e.eventName == "left-keydown") {
        key_left = true;
    }
    if (e.eventName == "left-keyup") {
        key_left = false;
    }

    if (e.eventName == "right-keydown") {
        key_right = true;
    }
    if (e.eventName == "right-keyup") {
        key_right = false;
    }
}

bool paddle::getKeyUpState()
{
	return key_up;
}

bool paddle::getKeyRightState()
{
	return key_right;
}

bool paddle::getKeyLeftState()
{
	return key_left;
}

void paddle::setPositionBy(pos aPosition)
{
	position.x += aPosition.x;
	position.y += aPosition.y;
	moveBy(aPosition.x, aPosition.y);
}

void paddle::setPosition(pos aPosition)
{
	position = aPosition;
	moveTo(position.x, position.y);
}

pos paddle::getPosition()
{
	return position;
}

void paddle::update() {
    if(key_left) {
        if(getPosition().x >= 35)
		{
			pos tempPos;
			tempPos.x = -10;
			tempPos.y = 0;
			setPositionBy(tempPos);
		}
    }

    if(key_right) {
		if(getPosition().x <= 765)
		{
			pos tempPos;
			tempPos.x = 10;
			tempPos.y = 0;
			setPositionBy(tempPos);
		}
    }

}

#endif
