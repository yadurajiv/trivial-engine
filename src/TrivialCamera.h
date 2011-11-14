#ifndef TRIVIALCAMERA_H_INCLUDED
#define TRIVIALCAMERA_H_INCLUDED

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "TrivialApp.h"
#include "TrivialSceneManager.h"
#include "TrivialSceneObject.h"

using namespace std;

namespace Trivial {

class Camera : public SceneObject {
public:
    Camera() { };
    ~Camera() { };

    virtual void update() { };

    // update each frame.. used for follow and lerp et al.
    void _update();

    void moveTo(const float &x, const float &y);
    void lookAt(const float &x, const float &y);
    bool lookAt(const string &name) {
        SceneObject* o = _scene->get(name);
        if(o != NULL) {
            lookAt(o->X(), o->Y());
            return true;
        }

        return false;
    };

    float getCenterX() const { return _x + _halfWidth; }
    float getCenterY() const { return _y + _halfHeight; }

    int getMouseX() {
        _mousePosition = Trivial::App::Instance()->getMousePositionRel();
        _mousePosition.x+=_x;
        return _mousePosition.x;
    }

    int getMouseY() {
        _mousePosition = Trivial::App::Instance()->getMousePositionRel();
        _mousePosition.y+=_y;
        return _mousePosition.y;
    }

    //void rotate(float angle);

    //void follow(SceneObject& o, float lerp);
    //void follow(SceneObject& o);

    void reset();

    void setScene(const string &name);


protected:
    Scene* _scene;

/* half your own width */
    float _halfWidth;
    float _halfHeight;

    bool _ready;

    sf::Vector2i _mousePosition;

    // SceneObject* _followThis;

};

}

#endif // TRIVIALCAMERA_H_INCLUDED
