// Box2D for removal
/*
#include "TrivialBox2D.h"

namespace Trivial {

void TrivialBox2DObject::_init(b2World* _world) {
    init();

    if(_hasInit) {
        _body = _world->CreateBody(&_bodyDef);

        // Add the fixture to the body.
        _body->CreateFixture(&_fixtureDef); // TODO: SIGSEGV T_T in debug
    }
}

void TrivialBox2DObject::setCircleShape(float x, float y, float radius) {
    _circleShape.m_radius = radius;
    _fixtureDef.shape = &_circleShape;
    _bodyDef.position.Set(x, y);

    _hasInit = true;
}

void TrivialBox2DObject::setBoxShape(float x, float y, float width, float height) {
    _polygonShape.SetAsBox(width/PHYSICS_RATIO, height/PHYSICS_RATIO);
    _fixtureDef.shape = &_polygonShape;
    _bodyDef.position.Set(x/PHYSICS_RATIO, y/PHYSICS_RATIO);

    _hasInit = true;
}

}
*/
