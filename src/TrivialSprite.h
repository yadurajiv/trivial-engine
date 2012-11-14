#ifndef TRIVIALSPRITE_H_INCLUDED
#define TRIVIALSPRITE_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialSceneObject.h"

#include "TrivialImageManager.h"

using namespace std;

namespace Trivial {

class Sprite : public SceneObject {
public:

    Sprite():_imageReady(false), _scrollEnabled(false), _scaleX(1), _scaleY(1), _fadeOut(false), _fadeIn(false) {
        // setColor(255,255,255,255);
        _alpha = getAlpha();
        _app = Trivial::App::Instance();

        _timeChanged = 0;
    };

    ~Sprite() { };

    virtual void update() { };

    virtual void _update(const bool& render = false);

    /** loads images from the image manager and updates sprite **/
    void image(const string &name);

    virtual void moveTo( const float &x, const float &y, const float &z = 0);
    virtual void moveBy( const float &x, const float &y, const float &z = 0);
    virtual void rotate(const float &angle);
    virtual void rotateBy(const float &angle);

    void fadeOut(float t);
    void fadeIn(float t, int alpha = 0);

    virtual void setAlpha(const int alpha = 255) {
        if(_alpha != alpha) {
            sf::Color c = SFMLsprite.getColor();
            _alpha = c.a = alpha;
            SFMLsprite.setColor(c);
        }
    }

    virtual int getAlpha() {
        sf::Color c = SFMLsprite.getColor();
        _alpha = c.a;
        return _alpha;
    }

    virtual void setColor(const int r = 255, const int g = 255, const int b = 255, const int alpha=255) {
        sf::Color c = SFMLsprite.getColor();
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = alpha;
        SFMLsprite.setColor(c);
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
        sf::Image img = Trivial::ImageManager::Instance()->get(_imageName)->copyToImage();
        if(x < 0 || y < 0 || x > _width || y > _height) { // doing this for some morons who will pass x and y not local x and y ~_~
            return false;
        } else {
            sf::Color col = img.getPixel(x/_scaleX,y/_scaleY);
            if(col.a <= alphaThreshold) {
                return false;
            } else {
                return true;
            }
        }
    }

    bool scrollEnable(const bool& b = true);
    void scrollImageBy(const float& x, const float& y);
    void resetImageRect();

	void setScale(const float& x = 1, const float& y = 1) {
		_scaleX = x;
		_scaleY = y;
		SFMLsprite.setScale(x,y);
		_width *= x;
		_height *= y;
		_originX = _width/2;
		_originY = _height/2;
	}

    sf::Sprite SFMLsprite;

private:

    int _alpha;

	float _scaleX;
	float _scaleY;

    float _imageScrollX;
    float _imageScrollY;
    string _imageName;

    bool _imageReady;
    bool _scrollEnabled;

    bool _fadeOut;
    bool _fadeIn;

    float _timeStep;
    float _alphaStep;
    float _timeEnd;
    float _timeChanged;

    Trivial::App* _app;

    sf::IntRect _textureRect;
    sf::IntRect _textureRectOriginal;

};

}

#endif // TRIVIALSPRITE_H_INCLUDED
