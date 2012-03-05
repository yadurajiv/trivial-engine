#ifndef ANIMATEDCHARACTER_H
#define ANIMATEDCHARACTER_H 

#include "TrivialEngine.h"

using namespace Trivial;

class animatedCharacter : public AnimatedSprite
{
private:
	
public:
	animatedCharacter();
	~animatedCharacter();
	
	void image(const string &name, const float &cellWidth, const float &cellHeight);
	bool addAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
	bool play(const string &name);
};

animatedCharacter::animatedCharacter()
{
	
}

animatedCharacter::~animatedCharacter()
{
	
}

void animatedCharacter::image(const string &name, const float &cellWidth, const float &cellHeight)
{
	AnimatedSprite::image(name, cellWidth, cellHeight);
}

bool animatedCharacter::addAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
{
	return AnimatedSprite::addAnimation(name, startFrame, endFrame, frameRate);
}

bool animatedCharacter::play(const string &name)
{
	return AnimatedSprite::play(name);
}
#endif