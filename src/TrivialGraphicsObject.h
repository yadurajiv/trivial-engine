#ifndef TRIVIALGRAPHICSOBJECT_H_INCLUDED
#define TRIVIALGRAPHICSOBJECT_H_INCLUDED

#include "TrivialObject.h"
#include "TrivialApp.h"

namespace Trivial {

class GraphicsObject : public Object {
public:
    GraphicsObject();
    ~GraphicsObject();

    virtual void update() {};

    virtual void _update(const bool& render = false) { if(_isActive) { update(); } };

    bool getActive() const { return _isActive; }
    void setActive(bool b) { _isActive = b; }

    bool setBlendMode(const string& mode) {
        if(mode == "multiply") {
            _renderStates.blendMode = sf::BlendMultiply;
        } else if(mode == "none") {
            _renderStates.blendMode = sf::BlendNone;
        } else if(mode =="alpha") {
            _renderStates.blendMode = sf::BlendAlpha;
        } else if(mode =="add") {
            _renderStates.blendMode = sf::BlendAdd;
        } else {
            return false;
        }

        return true;
    }

protected:

    bool _isActive;

    sf::RenderStates _renderStates;

/* be adventurous, every object now gets a pointer to the app! */
/*
    Trivial::App _app;
*/
};

}

#endif // TRIVIALGRAPHICSOBJECT_H_INCLUDED
