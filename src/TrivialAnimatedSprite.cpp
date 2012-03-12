#include <iostream>

#include "TrivialImageManager.h"
#include "TrivialAnimatedSprite.h"

namespace Trivial {

void AnimatedSprite::image(const string &name, const float &cellWidth, const float &cellHeight) {
    Sprite::image(name);
    SFMLsprite.SetTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
    _cellWidth = cellWidth;
    _cellHeight = cellHeight;
    SFMLsprite.SetOrigin(cellWidth/2,cellHeight/2); // SetOrigin removed and now its SetOrigin again..
    _cell = SFMLsprite.GetTextureRect();

    _ready = true;
}

bool AnimatedSprite::addAnimation(const string &name, const int &startFrame, const int &endFrame, const int &framerate) {
    if(!_ready)
        return false;

    //check if it is there
    _animations[name] = new Animation(_width,_height,_cellWidth, _cellHeight, startFrame, endFrame, framerate);

    return true;
}

bool AnimatedSprite::play(const string &name) {
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
		//Might need an error handling class to tell the user the return false case is because of which reason.
		return false;
	}
    //check if it is there.
    _currentAnimation = name;
    _animations[name]->play();

    return true;
}

//try to use _textureRect instead of a seperate _cell to do animation
void AnimatedSprite::_update() {
    if(_ready) {
        if(!_currentAnimation.empty()) {
            _animations[_currentAnimation]->update();
            _cell.Left = _animations[_currentAnimation]->getRow();
            _cell.Top = _animations[_currentAnimation]->getCol();
        /*
            cout << "\nfor animation: " << _currentAnimation;
            cout << "\ncell left: "<< _cell.Left;
            cout << "\ncell top: " << _cell.Top;
            cout << "\n";
            */
        }
        SFMLsprite.SetTextureRect(_cell);
    }

    Sprite::_update();
}

}
