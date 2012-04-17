#include <iostream>

#include "TrivialImageManager.h"
#include "TrivialAnimatedSprite.h"

namespace Trivial {

void AnimatedSprite::image(const string &name, const float &cellWidth, const float &cellHeight) {
    Sprite::image(name);
    SFMLsprite.setTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
    _cellWidth = cellWidth;
    _cellHeight = cellHeight;
    SFMLsprite.setOrigin(cellWidth/2,cellHeight/2); // SetOrigin removed and now its SetOrigin again..
    _cell = SFMLsprite.getTextureRect();

    _ready = true;
}

bool AnimatedSprite::addAnimation(const string &name, const int &startFrame, const int &endFrame, const int &framerate) {
    if(!_ready)
        return false;

    //check if it is there
    _animations[name] = new Animation(_width,_height,_cellWidth, _cellHeight, startFrame, endFrame, framerate);

    return true;
}

bool AnimatedSprite::play(const string& name,const bool& looped) {
    return gotoAndPlay(name, 0, looped);
}

bool AnimatedSprite::gotoAndPlay(const string& name, const int& frame, const bool& looped) {
    //To Check if the Animation is loaded or Not. Returns false for Animation not loaded.
	//Try using addAnimation or There is a problem with your spriteSheet.
	if(!_ready)
	{
		//Might need an error handling class to tell the user the return false case is because of which reason.
		return false;
	}

	//To Check if Animation exists or not. Returns false for Animation not existing.
	if(_animations[name] <= 0)
	{
        if(name == "") {
            if(_animations[_currentAnimation] > 0) {
                _animations[_currentAnimation]->play(looped, frame);
                return true;
            }
        }

		//Might need an error handling class to tell the user the return false case is because of which reason.
		return false;
	} else {
	    _animations[name]->play(looped, frame);
	    _currentAnimation = name;
	}

    return true;
}

bool AnimatedSprite::stop(const string &name) {
    return gotoAndStop(name, 0);
}

bool AnimatedSprite::gotoAndStop(const string &name, const int& frame) {
    //To Check if the Animation is loaded or Not. Returns false for Animation not loaded.
	//Try using addAnimation or There is a problem with your spriteSheet.
	if(!_ready)
	{
		//Might need an error handling class to tell the user the return false case is because of which reason.
		return false;
	}

	//To Check if Animation exists or not. Returns false for Animation not existing.
	if(_animations[name] <= 0)
	{
        if(name == "") {
            if(_animations[_currentAnimation] > 0) {
                _animations[_currentAnimation]->stop(frame);
                return true;
            }
        }

		//Might need an error handling class to tell the user the return false case is because of which reason.
		return false;
	} else {
	    _animations[name]->stop(frame);
	}


    return true;
}

//try to use _textureRect instead of a seperate _cell to do animation
void AnimatedSprite::_update(const bool& render) {
    if(_ready) {
        if(!_currentAnimation.empty()) {
            _animations[_currentAnimation]->update();
            _cell.left = _animations[_currentAnimation]->getRow();
            _cell.top = _animations[_currentAnimation]->getCol();
        /*
            cout << "\nfor animation: " << _currentAnimation;
            cout << "\ncell left: "<< _cell.Left;
            cout << "\ncell top: " << _cell.Top;
            cout << "\n";
            */
        }
        SFMLsprite.setTextureRect(_cell);
    }

    Sprite::_update(render);
}

}
