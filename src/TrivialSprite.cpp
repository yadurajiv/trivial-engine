#include <iostream>

#include "TrivialApp.h"
#include "TrivialSprite.h"
#include "TrivialImageManager.h"

using namespace std;

namespace Trivial {

void Sprite::image(const string &name) {
    // SetImage becomes SetTexture
    _imageName = name;

    SFMLsprite.SetTexture(*(ImageManager::Instance()->get(_imageName))); // second param bool removed
    _width = ImageManager::Instance()->get(_imageName)->GetWidth();
    _height = ImageManager::Instance()->get(_imageName)->GetHeight();
    _textureRectOriginal = SFMLsprite.GetTextureRect();
     _textureRect = _textureRectOriginal;

    // SetCenter removed
    _originX = _width/2;
    _originY = _height/2;
    SFMLsprite.SetOrigin(_originX,_originY); // SetOrigin to SetCenter back to SetOrigin lol XD
    if(_width > _height) {
        _radius = _width/2;
    } else {
        _radius = _height/2;
    }

    _updateRect();
    _updatePointRect();

    _imageReady = true;
}

void Sprite::_update(const bool& render) {

    SceneObject::_update();

    if(render) {
        App::Instance()->render(SFMLsprite);
    }
}

void Sprite::moveTo( const float &x, const float &y) {
    SceneObject::moveTo(x, y);
    this->SFMLsprite.SetPosition(_x, _y);
}

void Sprite::moveBy( const float &x, const float &y) {
    SceneObject::moveBy(x, y);
    this->SFMLsprite.SetPosition(_x, _y);
}

void Sprite::rotate(const float &angle) {
    SceneObject::rotate(angle);
    this->SFMLsprite.SetRotation(_angle);
}

void Sprite::rotateBy(const float &angle) {
    SceneObject::rotateBy(angle);
    this->SFMLsprite.SetRotation(_angle);
}

bool Sprite::scrollEnable(const bool& b) {
    ImageManager::Instance()->get(_imageName)->SetRepeated(b);
    return _scrollEnabled = b;
}

void Sprite::scrollImageBy(const float& x, const float& y) {
    if(!_imageReady && !_scrollEnabled)
        return;

    _textureRect.Left += x;
    _textureRect.Top += y;
    SFMLsprite.SetTextureRect(_textureRect);

}

void Sprite::resetImageRect() {
    _textureRect = _textureRectOriginal;
    SFMLsprite.SetTextureRect(_textureRect);
}

}
