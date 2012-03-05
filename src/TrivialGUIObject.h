#ifndef TRIVIALGUIOBJECT_H_INCLUDED
#define TRIVIALGUIOBJECT_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialSceneObject.h"

namespace Trivial {

class GUIObject : public SceneObject {
public:

    GUIObject();
    ~GUIObject();

    virtual void update() { };

    virtual void _update() {
		//To update the update Function of Parent Class.
		SceneObject::_update();
		update(); 
	};

protected:

private:

};

}

#endif // TRIVIALGUIOBJECT_H_INCLUDED
