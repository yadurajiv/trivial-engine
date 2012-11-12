#include <iostream>

#include "TrivialSceneObject.h"

namespace Trivial {

SceneObject::SceneObject() {
    _x = 0;
    _y = 0;
    _z = 0;

    _width = 0;
    _height = 0;

    _radius = 0;

    _movable = true;
    _velocity.x = 0;
    _velocity.y = 0;

    _maxVelocity.x = 0;
    _maxVelocity.y = 0;

    _mass = 0;

    _elasticity = 0;

    _acceleration.x =0;
    _acceleration.y =0;

    _drag.x = 0;
    _drag.y = 0;
    _angularDrag = 0;

    _angle = 0;

    _angularVelocity = 0;
    _angularAcceleration = 0;

    _maxAngular = 0;

    _visible = true;

    _affectChildren = true;

    _updateRect();

    _updatePointRect();
}

SceneObject::~SceneObject() {
}

float SceneObject::getLocalX(const float& globalX) {
    return globalX;
    //return globalX - (_x - _originX);
}

float SceneObject::getLocalY(const float& globalY) {
    return globalY;
    //return globalY - (_y - _originY);
}

void SceneObject::hide() {
    this->_visible = false;
}

void SceneObject::show() {
    this->_visible = true;
}

bool SceneObject::isVisible() const {
    return this->_visible;
}

float SceneObject::computeVelocity(float Velocity, float Acceleration, float Drag, float Max) {
    Trivial::App* app = Trivial::App::Instance();

        if(Acceleration != 0)
            Velocity += Acceleration * app->frameTime();
        else if(Drag != 0)
        {
            float drag = Drag * app->frameTime();
            if(Velocity - drag > 0)
                Velocity = Velocity - drag;
            else if(Velocity + drag < 0)
                Velocity += drag;
            else
                Velocity = 0;
        }
        if((Velocity != 0) && (Max != 10000))
        {
            if(Velocity > Max)
                Velocity = Max;
            else if(Velocity < -Max)
                Velocity = -Max;
        }
        return Velocity;
}

float SceneObject::updateMotion() {
    float delta = 0;
    float velocityDelta = 0;
    float xDelta = 0;
    float yDelta = 0;


    Trivial::App* app = Trivial::App::Instance();

    velocityDelta = (computeVelocity(_angularVelocity,_angularAcceleration,_angularDrag,_maxAngular) - _angularVelocity)/2;
    _angularVelocity += velocityDelta;
    _angle += _angularVelocity * (app->frameTime()/1000);
    _angularVelocity += velocityDelta;
    this->rotate(_angle);

    velocityDelta = (computeVelocity(_velocity.x,_acceleration.x,_drag.x,_maxVelocity.x) - _velocity.x)/2;
    _velocity.x += velocityDelta;
    delta = _velocity.x * (app->frameTime()/1000);
    _velocity.x += velocityDelta;
    xDelta = delta;

    velocityDelta = (computeVelocity(_velocity.y,_acceleration.y,_drag.y,_maxVelocity.y) - _velocity.y)/2;
    _velocity.y += velocityDelta;
    delta = _velocity.y * (app->frameTime()/1000);
    _velocity.y += velocityDelta;
    yDelta = delta;
    this->moveBy(xDelta,yDelta);
    _updateRect();
    _updatePointRect();

    return delta;
}

bool SceneObject::add(const string &name, GraphicsObject &o) {
    // If an object with this name already exisits, return
    if(_items.count(name) > 0) {
        return false;
    }

    _items[name] = &o;

    return true;
}

bool SceneObject::remove(const string &name) {
    if(_items.count(name) == 0)
        return false;

    map<string, GraphicsObject*>::iterator it = _items.find(name);
    if (it != _items.end())
    {
        _items.erase(it);
        return true;
    }

    return false;

}

}

