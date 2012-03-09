#ifndef TRIVIALGUITEXT_H_INCLUDED
#define TRIVIALGUITEXT_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialGUIObject.h"


using namespace std;

namespace Trivial {

class GUIText : public GUIObject {
public:

    GUIText(): _data("") {
        _text.SetCharacterSize(20);
        _text.SetStyle(sf::Text::Regular);
        _text.SetOrigin(0,0);
    };
    ~GUIText() { };

    virtual void update() { };

    virtual void _update();

    virtual void moveTo( const float &x,  const float &y) {
        _text.SetOrigin(0,0);
        _x = x;
        _y = y;
        _text.SetPosition(_x,_y);
    };
    virtual void rotate(const float &angle) {
        _angle = angle;
        _text.Rotate(_angle);
    };

    void font(const string &name);

    void text(const string &data);
    void text(const float &x, const float &y, const string &data);
    virtual void setAlpha(const int alpha = 255) {
        if(_alpha != alpha) {
            sf::Color c = _text.GetColor();
            _alpha = c.a = alpha;
            _text.SetColor(c);
        }
    }

    virtual int getAlpha() {
        sf::Color c = _text.GetColor();
        _alpha = c.a;
        return _alpha;
    }

    virtual void setColor(const int r = 255, const int g = 255, const int b = 255, const int alpha=255) {
        sf::Color c = _text.GetColor();
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = alpha;
        _text.SetColor(c);
    }

private:
    string _data;

    sf::Text _text;

    int _alpha;

};

}


#endif // TRIVIALGUITEXT_H_INCLUDED
