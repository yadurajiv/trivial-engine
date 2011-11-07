#include "TrivialCamera.h"

namespace Trivial {

void Camera::_update() {
    SceneObject::_update();
}

void Camera::reset() {
    if(_ready) {
        _x = 0;
        _y = 0;
        moveTo(_x, _y);
    }
}
/**
    moves the camera to a particular position
**/
void Camera::moveTo(const float &x,const float &y) {
    if(_ready) {
        if(_x != x || _y != y) {
            _x = x;
            _y = y;
            _scene->moveLayers(_x, _y);
        }
    }
}

/**
    looks at a particular location by x and y
**/
void Camera::lookAt(const float &x, const float &y) {
    if(_ready) {
        if(_x != x - _halfWidth || _y != y - _halfHeight) {
            _x = x - _halfWidth;
            _y = y - _halfHeight;
            _scene->moveLayers(_x, _y);
        }
    }
}

void Camera::setScene(const string &name)  {
    _scene = SceneManager::Instance()->getScene(name);
    _width = _scene->width();
    _height = _scene->height();
    _halfWidth = (_width / 2);
    _halfHeight = (_height / 2);
    _ready = true;
}

}
