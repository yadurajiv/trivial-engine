#ifndef BUTTON_H
#define BUTTON_H

#include "TrivialEngine.h"

using namespace Trivial;

class Button : public GUIObject
{
private:
	bool isMaskAvailable;
	Trivial::Sprite _button;
	AnimatedSprite _animatedButton;
public:
	Button();
	~Button();
	
	void buttonWithSprite(const string &name);
	void buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight);
	void buttonAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
	void buttonAnimationPlay(const string &name);
	void setIsMask(bool bValue);
	virtual void _update();
	virtual void update();
	
};

Button::Button()
{
	isMaskAvailable = false;
}

Button::~Button()
{
	
}

void Button::_update()
{
	GUIObject::_update();
}

void Button::update()
{
	GUIObject::update();
}

void Button::buttonWithSprite(const string &name)
{
	_button.image(name);
	cout<<add("TrivialButton",_button);
}

void Button::buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight)
{
	_animatedButton.image(name, colWidth, colHeight);
}

void Button::buttonAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
{
	_animatedButton.addAnimation(name, startFrame, endFrame, frameRate);
}

void Button::buttonAnimationPlay(const string &name)
{
	_animatedButton.play(name);
}

void Button::setIsMask(bool bValue)
{
	isMaskAvailable = bValue;
}

#endif