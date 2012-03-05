#ifndef BALL_H
#define BALL_H

#include "TrivialEngine.h"

struct pos
{
	int x;
	int y;
};
class ball : public Trivial::Sprite
{
private:
	pos position;
	bool ballMotionDirection; //False for Down, True for Up
	pos lastCollidePlace;
	int relativeToPaddle;
	
public:
	ball();
	~ball();
	void image(const string &name);
	
	pos getPosition();
	void setPosition(pos aPosition);
	void setBallMotionDirection(bool val);
	bool getBallMotionDirection();
	void setLastCollidePlace(pos aPosition);
	pos getLastCollidePlace();
	void setRelativeToPaddle(int aPoint);
	int getRelativeToPaddle();
};

ball::ball(){
	position.x = 0;
	position.y = 0;
	ballMotionDirection = true;
	lastCollidePlace = position;
}

ball::~ball(){
	
}

void ball::image(const string &name)
{
	Sprite::image(name);
}

pos ball::getPosition()
{
	return position;
}

void ball::setPosition(pos aPosition)
{
	position = aPosition;
	moveTo(position.x, position.y);
}

void ball::setBallMotionDirection(bool val)
{
	ballMotionDirection = val;
}

bool ball::getBallMotionDirection()
{
	return ballMotionDirection;
}

void ball::setLastCollidePlace(pos aPosition)
{
	lastCollidePlace = aPosition;
}

pos ball::getLastCollidePlace()
{
	return lastCollidePlace;
}

void ball::setRelativeToPaddle(int aPoint)
{
	relativeToPaddle = aPoint;
}

int ball::getRelativeToPaddle()
{
	return relativeToPaddle;
}

#endif