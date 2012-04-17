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
        _text.setCharacterSize(20);
        _text.setStyle(sf::Text::Regular);
        _text.setOrigin(0,0);
        _textSize = 20;
        _textStyle = "regular";
    };
    ~GUIText() { };

    virtual void update() { };

    virtual void _update(const bool& render = false);

    virtual void moveTo( const float &x,  const float &y) {
        _text.setOrigin(0,0);
        _x = x;
        _y = y;
        _text.setPosition(_x,_y);
    };
    virtual void rotate(const float &angle) {
        _angle = angle;
        _text.rotate(_angle);
    };

    void font(const string &name);

    void text(const string &data);
    void text(const float &x, const float &y, const string &data);
    virtual void setAlpha(const int alpha = 255) {
        if(_alpha != alpha) {
            sf::Color c = _text.getColor();
            _alpha = c.a = alpha;
            _text.setColor(c);
        }
    }

    virtual int getAlpha() {
        sf::Color c = _text.getColor();
        _alpha = c.a;
        return _alpha;
    }

    virtual void setColor(const int r = 255, const int g = 255, const int b = 255, const int alpha=255) {
        sf::Color c = _text.getColor();
        c.r = r;
        c.g = g;
        c.b = b;
        c.a = alpha;
        _text.setColor(c);
    }

    unsigned int size(const unsigned int& s = 20) {
        _textSize = s;
        _text.setCharacterSize(_textSize);
        return _textSize;
    }

    unsigned int getSize() {
        return _textSize;
    }


    /*
        maybe we should to a search on the string passed into the function
        and decide what needs to be done on that, so the user can pass in
        "boldItalic" or "bold-italic" or "bold italics" or "BOLDITALICS"
        and still work
        - @yadurajiv
    */
    void style(const string& s = "regular") {
        if(s == "regular" || s == "normal") {
            _textStyle = s;
            _text.setStyle(sf::Text::Regular);
        } else if(s == "bold") {
            _textStyle = s;
            _text.setStyle(sf::Text::Bold);
        } else if(s == "bold-italic") {
            _textStyle = s;
            _text.setStyle(sf::Text::Bold | sf::Text::Italic);
        } else if(s == "italic") {
            _textStyle = s;
            _text.setStyle(sf::Text::Italic);
        }
    }

    string getStyle() {
        return _textStyle;
    }

private:
    string _data;

    sf::Text _text;

    int _alpha;

    unsigned int _textSize;
    string _textStyle;

};

}


#endif // TRIVIALGUITEXT_H_INCLUDED
