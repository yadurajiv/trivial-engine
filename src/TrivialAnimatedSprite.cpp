#include <iostream>

#include "TrivialImageManager.h"
#include "TrivialAnimatedSprite.h"

namespace Trivial {

void AnimatedSprite::image(const string &name, const float &cellWidth, const float &cellHeight) {
    SFMLsprite.SetTexture(*(ImageManager::Instance()->get(name))); // bool second param removed
    SFMLsprite.SetTextureRect(sf::IntRect(0, 0, cellWidth, cellHeight));
    _width = ImageManager::Instance()->get(name)->GetWidth();
    _height = ImageManager::Instance()->get(name)->GetHeight();
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
    if(!_ready)
        return false;

    //check if it is there.
    _currentAnimation = name;
    _animations[name]->play();

    return true;
}

void AnimatedSprite::_update() {
    if(_ready) {
        _animations[_currentAnimation]->update();
        _cell.Left = _animations[_currentAnimation]->getRow();
        _cell.Top = _animations[_currentAnimation]->getCol();

        SFMLsprite.SetTextureRect(_cell);
        Sprite::_update();
    }
}

}
