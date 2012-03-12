#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H 

#include "TrivialGUIObject.h"
#include "TrivialSprite.h"
#include "TrivialAnimatedSprite.h"
#include <sstream>

using namespace std;

class ProgressBar : public Trivial::GUIObject
{
private:
	Trivial::Sprite _backgroundSprite;
	Trivial::Sprite *_repeatSprite;
	Trivial::Sprite _aRepeatSprite;
	int _repeatSpritePtr;
	bool _repeatX;
	float _percentValue;
public:
	ProgressBar();
	void init(const string &bgSprite, const string &repeatSprite, bool repeatX);
	~ProgressBar();
	void setPercentValue(float aValue);
	virtual void update(){}
	virtual void _update();
	
	
};

ProgressBar::ProgressBar()
{
	_repeatSpritePtr = 0;
	_percentValue = 100;
}

void ProgressBar::init(const string &bgSprite, const string &repeatSprite, bool repeatX = true)
{
	_backgroundSprite.image(bgSprite);
	_aRepeatSprite.image(repeatSprite);
	add("_ProgressBar_backgroundSprite", _backgroundSprite);
	_backgroundSprite.moveTo(X(),Y());
	affectChildren();
	
	_repeatX = repeatX;
	_repeatSpritePtr = 0;
	
	int size = _backgroundSprite.width()/_aRepeatSprite.width();
	_repeatSprite = new Trivial::Sprite [size];
				
	if(_repeatX)
	{	
		for(_repeatSpritePtr=0; _repeatSpritePtr < size;  _repeatSpritePtr++)
		{
			stringstream append;
			_repeatSprite[_repeatSpritePtr].image(repeatSprite);
			append<<"_ProgressBar_repeatSprite"<<_repeatSpritePtr;
			add(append.str().c_str(), _repeatSprite[_repeatSpritePtr]);
			_repeatSprite[_repeatSpritePtr].moveTo(X() + _repeatSprite[_repeatSpritePtr].width()*_repeatSpritePtr - _backgroundSprite.width()/2, Y());	
		}
		
	}
	else
	{
		//_repeatSprite.moveTo(X(), Y() - _backgroundSprite.height()/2);
	}
}

void ProgressBar::_update()
{
	
	float floatSize = (_repeatSpritePtr * _percentValue) / 100;
	int intSize = (int)floatSize;
	
	for(int i=_repeatSpritePtr; i>0 && i>intSize-1; i--)
	{
		stringstream append;
		append<<"_ProgressBar_repeatSprite"<<i;
		remove(append.str().c_str());
	}
	
	GUIObject::_update();
	update();
}

void ProgressBar::setPercentValue(float aValue)
{
	_percentValue = aValue;
}

ProgressBar::~ProgressBar()
{
	remove("_ProgressBar_backgroundSprite");
	remove("_ProgressBar_repeatSprite");
	delete _repeatSprite;
}
#endif