#ifndef BRICK_H

#define BRICK_H

#include "TrivialEngine.h"

class brick : public Trivial::Sprite
{
	private :
	pos position;
	public :
	brick();
	~brick();

	void image(const string &name);
	pos getPosition();
	void setPositionBy(pos aPosition);
	void setPosition(pos aPosition);
};

brick::brick()
{
	position.x = 0;
	position.y = 0;
}

brick::~brick()
{

}

void brick::image(const string &name)
{
	Sprite::image(name);
}

pos brick::getPosition()
{
	return position;
}

void brick::setPositionBy(pos aPosition)
{
	position.x += aPosition.x;
	position.y += aPosition.y;
	moveBy(position.x, position.y);
}

void brick::setPosition(pos aPosition)
{
	position = aPosition;
	moveTo(aPosition.x, aPosition.y);
}

#endif
