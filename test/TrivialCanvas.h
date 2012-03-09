#ifndef TRIVIALCANVAS_H
#define TRIVIALCANVAS_H

#include "TrivialEngine.h"

class TrivialCanvas : public Trivial::Sprite {
    public:
        TrivialCanvas();
        virtual ~TrivialCanvas(){};

        virtual void update() { };

        virtual void _update();

        void create(const int &width, const int &height, const Color& color = Color(255, 255, 255));

        void clear(const Color& color = Color(255, 255, 255));

        void setPixel(const int &x, const int &y,const Color& color = Color(0,0,0));
        void line(const int &x, const int &y, const int &tx, const int &ty);
        void circle(const int &x, const int &y, const int &radius);
        void ellipse(const int &w, const int &h);
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

        sf::Color _clearColor;

        bool _ready;
};

#endif // TRIVIALCANVAS_H
