#include <iostream>

#include "TrivialApp.h"
#include "TrivialSprite.h"
#include "TrivialImageManager.h"

using namespace std;

namespace Trivial {

void Sprite::image(const string &name) {
    // SetImage becomes SetTexture
    SFMLsprite.SetTexture(*(ImageManager::Instance()->get(name))); // second param bool removed
    _width = SFMLsprite.GetSize().x;
    _height = SFMLsprite.GetSize().y;
    // SetCenter removed
    SFMLsprite.SetOrigin(_width/2,_height/2); // SetOrigin to SetCenter back to SetOrigin lol XD
    if(_width > _height) {
        _radius = _width/2;
    } else {
        _radius = _height/2;
    }
}

void Sprite::_update() {

    SceneObject::_update();

    App::Instance()->render(SFMLsprite);
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

}
