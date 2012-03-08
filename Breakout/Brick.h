#ifndef BRICK_H

#define BRICK_H

#include "TrivialEngine.h"

#include "helpers.h"

class brick : public Trivial::Sprite
{
	private :
	pos position;
	public :
	brick() {
		position.x = 0;
        position.y = 0;
	}
	~brick() { }

    void image(const string &name) {
        Sprite::image(name);
    }

    pos getPosition() {
        return position;
    }

    void setPositionBy(pos aPosition) {
        position.x += aPosition.x;
        position.y += aPosition.y;
        moveBy(position.x, position.y);
    }

    void setPosition(pos aPosition) {
        position = aPosition;
        moveTo(aPosition.x, aPosition.y);
    }
};

#endif
