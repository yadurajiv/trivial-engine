#ifndef TRIVIALSCENEOBJECT_H_INCLUDED
#define TRIVIALSCENEOBJECT_H_INCLUDED

#include <string>

// Box2D for removal
// #include "TrivialBox2D.h"
#include "TrivialHelper.h"
#include "TrivialGraphicsObject.h"
#include "TrivialGroup.h"

using namespace std;

namespace Trivial {

class SceneObject : public Group {
public:
    SceneObject();
    ~SceneObject();

    float updateMotion();

    virtual void update() { };
    virtual void _update() {
        Group::_update();
        updateMotion();
        update(); // does this need to be called, it wasn't here.. mm..
    }; // notice that unlike a GraphicsObject it does not check to see if one is active

    void _initPhysics();

    // Box2D for removal
    // virtual void updatePhysics() { };
    // void _updatePhysics();

    void affectChildren(bool b) {
        _affectChildren = b;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->affectChildren(b);
            }
        }
    }

    bool isAffectChildren() {
        return _affectChildren;
    }

    virtual void moveTo( const float &x,  const float &y) {
        _x = x;
        _y = y;
    };
    virtual void moveBy( const float &x,  const float &y) {
        _x += x;
        _y += y;
    };
    virtual void rotate(const float &angle) {
        _angle = angle;
    };
    virtual void rotateBy(const float &angle) {
        _angle += angle;
    };

    virtual float X() const { return _x; };
    virtual float Y() const { return _y; };

    virtual float width() const { return _width; };
    virtual float height() const { return _height; };

    virtual float radius() const { return _radius; };

    void show();
    void hide();
    bool isVisible() const;

    void setLayer(const string &name) { layerName = name; };
    string getLayer() const { return layerName; };

    // Box2D for removal
    // TrivialBox2DObject* getPhysicsObject() { return &_physics; };

    void setVelocity(const float &x, const float &y) {
        _velocity.x = x;
        _velocity.y = y;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->setVelocity(x, y);
            }
        }
    }

    void setDrag(const float &dx, const float &dy) {
        _drag.x = dx;
        _drag.y = dy;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->setDrag(dx, dy);
            }
        }
    }

    void setAngularDrag(const float &d) {
        _angularDrag = d;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->setAngularDrag(d);
            }
        }
    }

    void setAcceleration(const float &ax, const float &ay) {
        _acceleration.x = ax;
        _acceleration.y = ay;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->setAcceleration(ax, ay);
            }
        }
    }

    void setMaxVelocity(const float &vx, const float &vy) {
        _maxVelocity.x = vx;
        _maxVelocity.y = vy;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->setMaxVelocity(vx, vy);
            }
        }
    }

    void setAngularAcceleration(const float &a) {
        _angularAcceleration = a;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->setAngularAcceleration(a);
            }
        }
    }

    void setMaxAngular(const float &a) {
        _maxAngular = a;

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                static_cast<SceneObject*>((*it).second)->setMaxAngular(a);
            }
        }
    }

    bool pointOverlap(float x, float y) {
        if(Trivial::Helper::pointInRect(x,y,_x,_y,_width,_height)) {
            return true;
        }
        return false;
    }

    virtual bool overlaps(SceneObject &o) {
        if(Trivial::Helper::sphereCollision(_x,_y,_radius,o.X(),o.Y(),o.radius())) {
            float w2 = _width/2;
            float h2 = _height/2;
            float ox = o.X();
            float oy = o.Y();
            float ow2 = o.width()/2;
            float oh2 = o.height()/2;

            if(Trivial::Helper::AABBAABB(_x - w2, _y - h2, _x + w2, _y + h2, ox - ow2, oy - oh2, ox + ow2, oy + oh2)) {
                return true;
            }
        } else {
            return false;
        }
        return false;
    }

    static float computeVelocity(float Velocity, float Acceleration = 0, float Drag = 0, float Max = 10000);

protected:

    string layerName;

    string _id;

    float _x;
    float _y;

    float _width;
    float _height;

    float _radius;

    bool _movable;
    sf::Vector2f _velocity;
    sf::Vector2f _maxVelocity;

    float _mass;

    float _elasticity;

    sf::Vector2f _acceleration;

    sf::Vector2f _drag;
    float _angularDrag;

    float _angle;

    float _angularVelocity;
    float _angularAcceleration;

    float _maxAngular;

    bool _visible;

    // Box2D for removal
    // bool _hasBox2DPhysics;
    //TrivialBox2DObject _physics;

    bool _affectChildren;

};

}

#endif // TRIVIALGRAPHICSOBJECT_H_INCLUDED
