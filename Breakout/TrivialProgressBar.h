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
	int _maxSpriteSize;
	bool _repeatX;
	bool _direction;
	float _percentValue;
public:
	ProgressBar();
	void init(const string &bgSprite, const string &repeatSprite, bool repeatX, bool direction);
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

void ProgressBar::init(const string &bgSprite, const string &repeatSprite, bool repeatX = true, bool positiveDirection = true)
{
	_backgroundSprite.image(bgSprite);
	_aRepeatSprite.image(repeatSprite);
	add("_ProgressBar_backgroundSprite", _backgroundSprite);
	_backgroundSprite.moveTo(X(),Y());
	affectChildren();
	
	_repeatX = repeatX;
	_direction = positiveDirection;
	_repeatSpritePtr = 0;
	
	_maxSpriteSize = 0;
	if(_repeatX){
		_maxSpriteSize = _backgroundSprite.width()/_aRepeatSprite.width();
	}
	else
	{
		_maxSpriteSize = _backgroundSprite.height()/_aRepeatSprite.height();
	}
	_repeatSprite = new Trivial::Sprite [_maxSpriteSize];
				

	for(_repeatSpritePtr=0; _repeatSpritePtr < _maxSpriteSize;  _repeatSpritePtr++)
	{
		stringstream append;
		_repeatSprite[_repeatSpritePtr].image(repeatSprite);
		append<<"_ProgressBar_repeatSprite"<<_repeatSpritePtr;
		add(append.str().c_str(), _repeatSprite[_repeatSpritePtr]);
		if(_repeatX)
		{
			if(_direction)
			{
				_repeatSprite[_repeatSpritePtr].moveTo(X() + _repeatSprite[_repeatSpritePtr].width()*_repeatSpritePtr - _backgroundSprite.width()/2, Y());	
			}
			else
			{
				_repeatSprite[_repeatSpritePtr].moveTo(X() - _repeatSprite[_repeatSpritePtr].width()*_repeatSpritePtr + _backgroundSprite.width()/2, Y());
			}
		}
		else
		{
			if(_direction)
			{
				_repeatSprite[_repeatSpritePtr].moveTo(X(), Y() + _repeatSprite[_repeatSpritePtr].height()*_repeatSpritePtr - _backgroundSprite.height()/2);
			}
			else
			{
				_repeatSprite[_repeatSpritePtr].moveTo(X(), Y() - _repeatSprite[_repeatSpritePtr].height()*_repeatSpritePtr + _backgroundSprite.height()/2);
			}
		}
		
	}

}

void ProgressBar::_update()
{
	float floatSize = ((_maxSpriteSize-1) * _percentValue) / 100;
	int intSize = (int)floatSize + 1;
	
	if(intSize < _repeatSpritePtr-1)
	{
		for(int i=_repeatSpritePtr-1; i>0 && i>intSize; i--)
		{
			stringstream append;
			append<<"_ProgressBar_repeatSprite"<<i;
			remove(append.str().c_str());
			_repeatSpritePtr--;
		}
	}
	else
	{
		for(int i=_repeatSpritePtr-1; i<intSize && i<_maxSpriteSize; i++)
		{
			stringstream append;
			append<<"_ProgressBar_repeatSprite"<<i;
			add(append.str().c_str(), _repeatSprite[i]);
			_repeatSpritePtr++;
		}
	}
	
	GUIObject::_update();
	update();
}

void ProgressBar::setPercentValue(float aValue)
{
	if(aValue >= 0 && aValue <= 100)
		_percentValue = aValue;
}

ProgressBar::~ProgressBar()
{
	remove("_ProgressBar_backgroundSprite");
	remove("_ProgressBar_repeatSprite");
	delete _repeatSprite;
}
#endif