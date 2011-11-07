#ifndef TRIVIALSPRITE_H_INCLUDED
#define TRIVIALSPRITE_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialSceneObject.h"

using namespace std;

namespace Trivial {

class Sprite : public SceneObject {
public:

    Sprite() { };
    ~Sprite() { };

    virtual void update() { };

    virtual void _update();

// Box2D for removal
/*
    void updatePhysics() {
        cout << "Hmmm" << endl;
        fflush(stdout);

        // Now print the position and angle of the body.
        b2Vec2 position = _physics.getBody()->GetPosition();
        float32 angle = _physics.getBody()->GetAngle();

        cout << position.y << endl;// position.y, angle);

        moveTo(_x, position.y*PHYSICS_RATIO);
    }
*/

    /** loads images from the image manager and updates sprite **/
    void image(const string &name);

    virtual void moveTo( const float &x, const float &y);
    virtual void moveBy( const float &x, const float &y);
    virtual void rotate(const float &angle);
    virtual void rotateBy(const float &angle);

    sf::Sprite SFMLsprite;

private:

    string _id;


};

}

#endif // TRIVIALSPRITE_H_INCLUDED
