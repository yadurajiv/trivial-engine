#ifndef TRIVIALSCENEOBJECT_H_INCLUDED
#define TRIVIALSCENEOBJECT_H_INCLUDED

#include <string>

// Box2D for removal
// #include "TrivialBox2D.h"
#include "TrivialHelper.h"
#include "TrivialGraphicsObject.h"

using namespace std;

namespace Trivial {

class SceneObject : public GraphicsObject {
public:
    SceneObject();
    ~SceneObject();

    float updateMotion();

    virtual void update() { }
    virtual void _update(const bool& render = false) {

        map<string, GraphicsObject*>::iterator it;

        for ( it=_items.begin() ; it != _items.end(); it++ ) {
            (*it).second->_update();
        }

        updateMotion();
        update(); // does this need to be called, it wasn't here.. mm..
    } // notice that unlike a GraphicsObject it does not check to see if one is active

    void _initPhysics();

    // Box2D for removal
    // virtual void updatePhysics() { };
    // void _updatePhysics();

    void affectChildren(bool b=true) {
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

        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                float item_x = static_cast<SceneObject*>((*it).second)->X();
                float item_y = static_cast<SceneObject*>((*it).second)->Y();
                static_cast<SceneObject*>((*it).second)->moveTo( (x+(_x - item_x)), (y+(_y - item_y)));
                // cout << "\n this should work X - " << (x+(_x - item_x));
            }
        }

        _x = x;
        _y = y;
    }

    virtual void moveBy( const float &x,  const float &y) {
/*
        if(_affectChildren) {
            map<string, GraphicsObject*>::iterator it;
            for ( it=_items.begin() ; it != _items.end(); it++ ) {
                float item_x = static_cast<SceneObject*>((*it).second)->X();
                float item_y = static_cast<SceneObject*>((*it).second)->Y();
                static_cast<SceneObject*>((*it).second)->moveTo( (x+item_x), (y+item_y));
            }
        }
*/
        _x += x;
        _y += y;
    }

    virtual void rotate(const float &angle) {
        _angle = angle;

        _updatePointRect();
    }

    virtual void rotateBy(const float &angle) {
        _angle += angle;

        _updatePointRect();
    }

    virtual float getRotation() const {
        return _angle;
    }

    virtual float getLocalX(const float& x);
    virtual float getLocalY(const float& y);

    virtual float X() const { return _x; }
    virtual float Y() const { return _y; }

    virtual float getOriginX() const { return _originX; }
    virtual float getOriginY() const { return _originY; }

// still questionable as to how this will affect TrivialCanvas
/*
    virtual void setOrigin(const float &x,const float &y) {
        _originX = x;
        _originY = y;
    }
*/

    virtual float width() const { return _width; }
    virtual float height() const { return _height; }

    virtual float width(const float &w) { return _width = w;}
    virtual float height(const float &h) { return _height = h;}

    virtual float radius() const { return _radius; };
    virtual float setRadius(const float &r) { return _radius = r; }

    void show();
    void hide();
    bool isVisible() const;

    void setLayer(const string &layerName) { _layerName = layerName; };
    string getLayer() const { return _layerName; };

    void setName(const string &name) { _name = name; };
    string getName() const { return _name; };

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
        _maxAngular = a;

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

    virtual bool pointOverlap(float x, float y) {
        if(Trivial::Helper::pointInRect(x,y,_prect.a.x,_prect.a.y,_prect.b.x,_prect.b.y,_prect.c.x,_prect.c.y,_prect.d.x,_prect.d.y) ) {
            return true;
        }
        return false;
    }

    virtual bool overlaps(SceneObject &o) {
        float h2 = height()/2;
        float w2 = width()/2;
        if(Trivial::Helper::sphereCollision(_x-w2,_y-h2,_radius,o.X(),o.Y(),o.radius())) {
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

    virtual bool add(const string &name, GraphicsObject &o);
    virtual bool remove(const string &name);

    TrivialRect getRect() {
        _updateRect();
        return _rect;
    }

    TrivialPointRect getPointRect() const { return _prect; }

    string getParentScene() const {
        return _parentScene;
    }

protected:

    void _updateRect() {
        _rect.x = _x - _originX;
        _rect.y = _y - _originY;
        _rect.width = _width;
        _rect.height = _height;
    }

    void _updatePointRect() {
        // should be rotating around _originX and _originY
        // _originX and _originY should be _x - _width/2
        _prect.a = Trivial::Helper::rotatePoint(_x - _originX, _y - _originY, _x, _y, _angle);
        _prect.b = Trivial::Helper::rotatePoint(_x + _originX, _y - _originY, _x, _y, _angle);
        _prect.c = Trivial::Helper::rotatePoint(_x + _originX, _y + _originY, _x, _y, _angle);
        _prect.d = Trivial::Helper::rotatePoint(_x - _originX, _y + _originY, _x, _y, _angle);
    }

    std::map<string, GraphicsObject*> _items;

    string _layerName;

    string _name;

    float _x;
    float _y;

    float _width;
    float _height;

    TrivialRect _rect;
    TrivialPointRect _prect;

    float _originX;
    float _originY;

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

    string _parentScene;

    friend class Scene;

};

}

#endif // TRIVIALGRAPHICSOBJECT_H_INCLUDED
