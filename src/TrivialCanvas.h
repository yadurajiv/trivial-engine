#ifndef TRIVIALCANVAS_H
#define TRIVIALCANVAS_H

#include <SFML/Graphics.hpp>

#include "TrivialSprite.h"

using namespace std;

namespace Trivial {

class Canvas : public Trivial::Sprite {
    public:
        Canvas();
        virtual ~Canvas(){};

        virtual void update() { };

        virtual void _update(const bool& render = false);

        void create(const int &width, const int &height, const sf::Color& color = sf::Color(255, 255, 255));

        void clear(const sf::Color& color = sf::Color(255, 255, 255));

        void setPixel(const int &x, const int &y,const sf::Color& color = sf::Color(0,0,0));
        void line(const int &x, const int &y, const int &tx, const int &ty);
        void line(const float& x1, const float& y1, const float& x2, const float& y2);
        void circle(const int &x, const int &y, const int &radius);
        void ellipse(const int &w, const int &h);
        void rect(const TrivialPointRect& ptrect);
        void rect(const int &rx, const int &ry, const int &rw, const int &rh);
/*
        line(x,y,tx,ty)
        ellipse(w,h)
        rect(rx,ry,rw,rh)

        and helper functions like

        clear()
        getImage()
        getSprite()
        saveToFile()
        */
    protected:
    private:
        int _cursorX;
        int _cursorY;

        sf::Image _image;
        sf::Texture _texture;

        bool _updateTexture;

        sf::Color _clearColor;

        bool _ready;
};

}

#endif // TRIVIALCANVAS_H
