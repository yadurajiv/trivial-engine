#ifndef TRIVIALCAMERA_H_INCLUDED
#define TRIVIALCAMERA_H_INCLUDED

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"

#include "TrivialSceneObject.h"

using namespace std;

namespace Trivial {

class Camera : public SceneObject {
public:
    Camera():_zoom(1),_zoomFactor(1) { };
    ~Camera() { };

    void init(const unsigned int &width, const unsigned int &height);

    virtual void update() { };

    // update each frame.. used for follow and lerp et al.
    void _update();

    void moveTo(const float &x, const float &y);
    void lookAt(const float &x, const float &y);
    /*
    bool lookAt(const string &name) {
        SceneObject* o = _scene->get(name);
        if(o != NULL) {
            lookAt(o->X(), o->Y());
            return true;
        }

        return false;
    };
    */

    float getCenterX() const { return _x + _halfWidth; }
    float getCenterY() const { return _y + _halfHeight; }

    void setZoom(const float &percent = 100) {
        /*
         simple, 100 = 1; 150 = 1.5; 50 = 0.5
         but if we were to set the zoom to 1.5 it would show 150% of the screen
         rather than zoom to 150% so we need to convert 150 to 0.5
         I sure hope this works ~_~ *sigh*
        */
        _zoomFactor = abs(1 - (percent-100)/100);
        _zoom =  percent/100;
    }

    float getZoom() const {
        return _zoom *100;
    }

    float getZoomFactor() const {
        return _zoomFactor;
    }

    // shake will stop your camera from moving!
    void shake(const float &duration=1, const float &intensity = 0.05) {
        _shakeTimer = 0;
        _shakeIntensity = intensity;
        _shakeDuration = duration;
        _shakePostX = _x;
        _shakePostY = _y;
        _doShake = true;

        /// dispatch a shake start event
    }

    //void rotate(float angle);

    //void follow(SceneObject& o, float lerp);
    //void follow(SceneObject& o);

    void reset();

    //void setScene(const string &name);


protected:
    //Scene* _scene;

/* half your own width */
    float _halfWidth;
    float _halfHeight;

    bool _ready;

    float _zoom;
    float _zoomFactor;

    float _shakeIntensity;
    float _shakeDuration;
    float _shakeTimer;
    float _shakePostX;
    float _shakePostY;
    bool _doShake;

    sf::Vector2i _mousePosition;

    // SceneObject* _followThis;

};

}

#endif // TRIVIALCAMERA_H_INCLUDED
