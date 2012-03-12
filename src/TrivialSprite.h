#ifndef TRIVIALSPRITE_H_INCLUDED
#define TRIVIALSPRITE_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialSceneObject.h"

using namespace std;

namespace Trivial {

class Sprite : public SceneObject {
public:

    Sprite():_imageReady(false), _scrollEnabled(false) { };
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
    virtual void setAlpha(const int alpha = 255) {
        if(_alpha != alpha) {
            sf::Color c = SFMLsprite.GetColor();
            _alpha = c.a = alpha;
            SFMLsprite.SetColor(c);
        }
    }

    virtual int getAlpha() {
        sf::Color c = SFMLsprite.GetColor();
        _alpha = c.a;
        return _alpha;
    }

    virtual void setColor(const int r = 255, const int g = 255, const int b = 255, const int alpha=255) {
        sf::Color c = SFMLsprite.GetColor();
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = alpha;
        SFMLsprite.SetColor(c);
    }

    virtual bool pointOverlap(const float& x,const float& y, const bool& pixeltest = false) {
        if(SceneObject::pointOverlap(x,y)) {
            if(pixeltest) {
                if(pixelTest(getLocalX(x),getLocalY(y))) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    // USER MUST DO A POINT OVERLAP TEST BEFORE CALLING THIS!!
    // IF A WRONG X and Y values are given you will get a segfault!
    // alpha threshold between 0 and 1 ~_~
    // fuck this shit! i have lots of memory!
    bool pixelTest(const float& x, const float& y, const unsigned int& alphaThreshold = 0) {
        // bheri bheri expensive function
        sf::Image img = Trivial::ImageManager::Instance()->get(_imageName)->CopyToImage();
        if(x < 0 || y < 0 || x > _width || y > _height) { // doing this for some morons who will pass x and y not local x and y ~_~
            return false;
        } else {
            sf::Color col = img.GetPixel(x,y);
            if(col.a == alphaThreshold) {
                return false;
            } else {
                return true;
            }
        }
    }

    bool scrollEnable(const bool& b = true);
    void scrollImageBy(const float& x, const float& y);
    void resetImageRect();

    sf::Sprite SFMLsprite;

private:

    int _alpha;

    float _imageScrollX;
    float _imageScrollY;
    string _imageName;

    bool _imageReady;
    bool _scrollEnabled;

    sf::IntRect _textureRect;
    sf::IntRect _textureRectOriginal;

};

}

#endif // TRIVIALSPRITE_H_INCLUDED
