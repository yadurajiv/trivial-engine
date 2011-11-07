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

    virtual void _update() { if(_isActive) { update(); } };

    bool getActive() const { return _isActive; }
    void setActive(bool b) { _isActive = b; }

protected:

    bool _isActive;

/* be adventurous, every object now gets a pointer to the app! */
/*
    Trivial::App _app;
*/
};

}

#endif // TRIVIALGRAPHICSOBJECT_H_INCLUDED
