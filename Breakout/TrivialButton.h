#ifndef BUTTON_H
#define BUTTON_H

#include "TrivialEngine.h"

using namespace Trivial;

class Button : public AnimatedSprite
{
private:
	bool isMaskAvailable;
public:
	Button();
	~Button();
	
	void buttonWithSprite(const string &name);
	void buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight);
	void buttonAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
	void buttonAnimationPlay(const string &name);
	void setIsMask(bool bValue);
	
};

Button::Button()
{
	isMaskAvailable = false;
}

Button::~Button()
{
	
}

void Button::buttonWithSprite(const string &name)
{
	Sprite::image(name);
}

void Button::buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight)
{
	AnimatedSprite::image(name, colWidth, colHeight);
}

void Button::buttonAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
{
	AnimatedSprite::addAnimation(name, startFrame, endFrame, frameRate);
}

void Button::buttonAnimationPlay(const string &name)
{
	AnimatedSprite::play(name);
}

void Button::setIsMask(bool bValue)
{
	isMaskAvailable = bValue;
}

#endif