#include <iostream>

#include "TrivialApp.h"
#include "TrivialSprite.h"
#include "TrivialImageManager.h"

using namespace std;

namespace Trivial {

void Sprite::image(const string &name) {
    // SetImage becomes SetTexture
    _imageName = name;

    SFMLsprite.setTexture(*(ImageManager::Instance()->get(_imageName)), true); // second param bool removed
    sf::Vector2u s = ImageManager::Instance()->get(_imageName)->getSize();
    _width = s.x;
    _height = s.y;
    _textureRectOriginal = SFMLsprite.getTextureRect();
     _textureRect = _textureRectOriginal;

    // SetCenter removed
    _originX = _width/2;
    _originY = _height/2;
    SFMLsprite.setOrigin(_originX,_originY); // SetOrigin to SetCenter back to SetOrigin lol XD
    if(_width > _height) {
        _radius = _width/2;
    } else {
        _radius = _height/2;
    }

    _updateRect();
    _updatePointRect();

    _imageReady = true;
}

void Sprite::fadeOut(float t) {
    if(!_fadeOut && !_fadeIn && _alpha > 0 && t > 0) {

        _fadeOut = true;
        _fadeIn = false;

        _timeEnd = t*1000; // convert to milliseconds
        _timeStep = (_timeEnd/_alpha);
        _timeChanged = 0;

        cout << "\nFade out started!";
    }
}

void Sprite::fadeIn(float t, int alpha) {
    if(!_fadeOut && !_fadeIn && t > 0) {

        setAlpha(alpha);

        show();

        _fadeIn = true;
        _fadeOut = false;

        _timeEnd = t*1000; // convert to milliseconds
        _timeStep = (_timeEnd/255);
        _timeChanged = 0;

        cout << "\nFade in started!";
    }
}

void Sprite::_update(const bool& render) {

    SceneObject::_update();

    if(_fadeOut) {
        if(_alpha <= 0) {
            _fadeOut = false;
            hide();
            cout << "\nFade out complete!";
        } else {
            _timeChanged += _app->frameTime();
            cout << "\ntimeChanged: " << (_timeChanged >= _timeStep);
            if(_alpha > 0 && _timeChanged >= _timeStep) {
                setAlpha(_alpha - (_timeChanged/_timeStep));
                _timeChanged = 0;
            }
        }
    }

    //cout << "\nfadein is " << _fadeIn;
    if(_fadeIn) {
        if(_alpha >= 255) {
            _fadeIn = false;
            cout << "\nFade In complete!";
        } else {
            cout << "\nalpha: " << _alpha;
            _timeChanged += _app->frameTime();
            if(_alpha < 255 && _timeChanged >= _timeStep) {
                setAlpha(_alpha + (_timeChanged/_timeStep));
                _timeChanged = 0;
            }
        }
    }

    if(render && _visible) {
        App::Instance()->render(SFMLsprite, _renderStates);
    }
}

void Sprite::moveTo( const float &x, const float &y, const float &z) {
    SceneObject::moveTo(x, y, z);
    this->SFMLsprite.setPosition(_x, _y);
}

void Sprite::moveBy( const float &x, const float &y, const float &z) {
    SceneObject::moveBy(x, y, z);
    this->SFMLsprite.setPosition(_x, _y);
}

void Sprite::rotate(const float &angle) {
    SceneObject::rotate(angle);
    this->SFMLsprite.setRotation(_angle);
}

void Sprite::rotateBy(const float &angle) {
    SceneObject::rotateBy(angle);
    this->SFMLsprite.setRotation(_angle);
}

bool Sprite::scrollEnable(const bool& b) {
    ImageManager::Instance()->get(_imageName)->setRepeated(b);
    return _scrollEnabled = b;
}

void Sprite::scrollImageBy(const float& x, const float& y) {
    if(!_imageReady && !_scrollEnabled)
        return;

    _textureRect.left += x;
    _textureRect.top += y;
    SFMLsprite.setTextureRect(_textureRect);

}

void Sprite::resetImageRect() {
    _textureRect = _textureRectOriginal;
    SFMLsprite.setTextureRect(_textureRect);
}

}
