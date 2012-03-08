#ifndef BUTTON_H
#define BUTTON_H

#include "TrivialEngine.h"
#include <sstream>

using namespace Trivial;

struct mouseState
{
	bool down;
	bool up;
	bool hover;
}mState;

class Button : public GUIObject
{
private:
	bool isMaskAvailable;
	bool isAnimated;
	Trivial::Sprite _button;
	stringstream _buttonStateImages[3];
	AnimatedSprite _animatedButton;
	EventManager *myEventManager;
public:
	Button();
	~Button();
	
	void buttonWithSprite(const string &buttonUpState, const string &buttonDownState, const string &buttonHoverState);
	void buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight);
	void buttonUpAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
	void buttonDownAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
	void buttonHoverAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
	void setIsMask(bool bValue);
	virtual void _update();
	virtual void update();
	
	void mouseEventCallBack(const TrivialMouseEvent &e);
	
	virtual void buttonDown();
	virtual void buttonUp();
	virtual void buttonHover();
	
};

Button::Button()
{
	isMaskAvailable = false;
	isAnimated = false;
	
	mState.up = true;
	mState.down = false;
	mState.hover = false;
	
	myEventManager = EventManager::Instance();
	myEventManager->subscribe("update-mouse", this);
	myEventManager->subscribe("buttondown-mouse", this);
    myEventManager->subscribe("buttonup-mouse", this);
}

Button::~Button()
{
	
}

void Button::mouseEventCallBack(const TrivialMouseEvent &e)
{
	if(_button.pointOverlap(e.pos.x, e.pos.y) || _animatedButton.pointOverlap(e.pos.x, e.pos.y))
	{
		if(e.eventName == "buttondown-mouse")
		{
			mState.up = false;
			mState.down = true;
		}
		if(e.eventName == "buttonup-mouse")
		{
			mState.down = false;
			mState.up = true;
		}
		if(e.eventName == "update-mouse")
		{
			mState.hover = true;
		}
	}
	else
	{
		mState.hover = false;
	}
}

void Button::_update()
{
	GUIObject::_update();
}

void Button::update()
{
	GUIObject::update();
	if(mState.down)
	{
		buttonDown();
	}
	if(mState.up){
		buttonUp();
	}
	if(mState.hover)
	{
		buttonHover();
	}
}

void Button::buttonWithSprite(const string &buttonUpState, const string &buttonDownState = "", const string &buttonHoverState = "")
{
	_button.image(buttonUpState);
	add("TrivialButton",_button);
	_buttonStateImages[0]<<buttonUpState;
	if(buttonDownState != "") _buttonStateImages[1]<<buttonDownState;
	else _buttonStateImages[1]<<buttonUpState;
	if(buttonHoverState != "") _buttonStateImages[2]<<buttonHoverState;
	else _buttonStateImages[2]<<buttonUpState;
	
}

void Button::buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight)
{
	_animatedButton.image(name, colWidth, colHeight);
	add("TrivialAnimatedButton",_animatedButton);
	isAnimated = true;
}

void Button::buttonUpAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
{
	_animatedButton.addAnimation(name, startFrame, endFrame, frameRate);
	_buttonStateImages[0]<<name;
	_animatedButton.play(name);
}

void Button::buttonDownAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
{
	_animatedButton.addAnimation(name, startFrame, endFrame, frameRate);
	_buttonStateImages[1]<<name;
}

void Button::buttonHoverAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
{
	_animatedButton.addAnimation(name, startFrame, endFrame, frameRate);
	_buttonStateImages[2]<<name;
}

void Button::setIsMask(bool bValue)
{
	isMaskAvailable = bValue;
}

void Button::buttonDown()
{
	if(isAnimated == false)
	{
		_button.image(_buttonStateImages[1].str().c_str());
	}
	else
	{
		_animatedButton.play(_buttonStateImages[1].str().c_str());
	}
}

void Button::buttonUp()
{
	if(isAnimated == false)
	{
		_button.image(_buttonStateImages[0].str().c_str());
	}
	else
	{
		_animatedButton.play(_buttonStateImages[0].str().c_str());
	}
	
}

void Button::buttonHover()
{
	if(isAnimated == false)
	{
		_button.image(_buttonStateImages[2].str().c_str());
	}
	else
	{
		_animatedButton.play(_buttonStateImages[2].str().c_str());
	}
}

#endif