#ifndef TRIVIALBOX2D_H_INCLUDED
#define TRIVIALBOX2D_H_INCLUDED

// Box2D for removal
/*

#include <map>
#include <stdio.h>
#include <iostream>

#include <Box2D/Box2D.h>

#include "TrivialApp.h"
#include "TrivialObject.h"

using namespace std;

namespace Trivial {

#define PHYSICS_RATIO 30.0

class TrivialBox2DObject : public Object {
public:
    TrivialBox2DObject() { };
    ~TrivialBox2DObject() { };

    virtual void init() { };

    void _init(b2World* world);

    b2Body* getBody() { return _body; };

    void setCircleShape(float x, float y, float radius);
    void setBoxShape(float x, float y, float width, float height);

    void setKinematic() { _bodyDef.type = b2_kinematicBody; };
    void setDynamic() { _bodyDef.type = b2_dynamicBody; };

    bool hasInit() { return _hasInit; };

private:
    b2Body* _body;

    b2BodyDef _bodyDef;

    b2CircleShape _circleShape;
    b2PolygonShape _polygonShape;

    b2FixtureDef _fixtureDef;

    bool _hasInit;

};

class TrivialBox2DWorld : public Object {
public:
    TrivialBox2DWorld() { };

    ~TrivialBox2DWorld() { delete _world; };

    virtual void update() { };
    virtual void init() { };

    void _init() {

        _app = Trivial::App::Instance();

        // Define the gravity vector.
        b2Vec2 gravity(0.0f, 10.0f);

        // Do we want to let bodies sleep?
        bool doSleep = true;

        _world = new b2World(gravity, doSleep);

    }

    void _update() {
        float32 timeStep = _app->frameTime();
        int32 velocityIterations = 6;
        int32 positionIterations = 2;

		_world->Step(timeStep, velocityIterations, positionIterations);

		// Clear applied body forces. We didn't apply any forces, but you
		// should know about this function.
		_world->ClearForces();
    }

    void add(TrivialBox2DObject *object) {
        object->_init(_world);
    }

private:
	b2World *_world;

	Trivial::App* _app;
};

}
*/

#endif // TRIVIALBOX2D_H_INCLUDED
