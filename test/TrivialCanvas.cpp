#include "TrivialCanvas.h"

TrivialCanvas::TrivialCanvas() {
    //ctor
    _cursorX = 0;
    _cursorY = 0;
}

void TrivialCanvas::create(const int &w, const int &h,const Color& color) {
    _width = w;
    _height = h;
    _clearColor = color;

    clear();
}

void TrivialCanvas::_update() {
    Trivial::Sprite::_update();
}

void TrivialCanvas::clear(const Color& color) {
    _image.Create(_width, _height,_clearColor);
    _texture.LoadFromImage(_image);
    SFMLsprite.SetTexture(_texture);
    _width = _texture.GetWidth();
    _height = _texture.GetHeight();
    SFMLsprite.SetOrigin(_width/2,_height/2); // SetOrigin to SetCenter back to SetOrigin lol XD
    if(_width > _height) {
        _radius = _width/2;
    } else {
        _radius = _height/2;
    }
}

void TrivialCanvas::setPixel(const int &x, const int &y,const Color& color) {
        if(pointOverlap(x,y)) {
            int lx = x - (_x - _width/2);
            int ly = y - (_y - _height/2);
            _image.SetPixel(lx,ly,color);
            _texture.LoadFromImage(_image);
            SFMLsprite.SetTexture(_texture);
        } else {
            cout << "\noutside the zone biatch!";
        }

}

/**
    Bresenham's line algorithm
    http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
**/
void TrivialCanvas::line(const int &x, const int &y, const int &tx, const int &ty) {
    if(!pointOverlap(x,y) || !pointOverlap(tx,ty))
        return;

    int lx = x - (_x - _width/2);
    int ly = y - (_y - _height/2);
    int tlx = tx - (_x - _width/2);
    int tly = ty - (_y - _height/2);

    int dx = abs(lx-tlx);
    int dy = abs(ly-tly);
    int sx;
    int sy;

    if(lx < tlx) {
        sx = 1;
    } else {
        sx = -1;
    }

    if(ly < tly) {
        sy = 1;
    } else {
        sy = -1;
    }

    int err = dx-dy;
    int e2;

    while(lx != tlx && ly != tly) {
        _image.SetPixel(lx,ly,sf::Color::Black);
        e2 = 2*err;
        if(e2 > -dy) {
            err -= dy;
            lx += sx;
        }
        if(e2 < dx) {
            err += dx;
            ly += sy;
        }
    }

    _texture.LoadFromImage(_image);
    SFMLsprite.SetTexture(_texture);
}

void TrivialCanvas::circle(const int &x, const int &y, const int &radius) {
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int cx = 0;
    int cy = radius;
    int x0 = x - (_x - _width/2);
    int y0 = y - (_y - _height/2);

    if(!pointOverlap(x,y+radius) || !pointOverlap(x,y-radius) || !pointOverlap(x+radius,y) || !pointOverlap(x-radius,y)) {
        cout << "\nno circle for you!";
        return;
    }

    _image.SetPixel(x0, y0 + radius,sf::Color::Black);
    _image.SetPixel(x0, y0 - radius,sf::Color::Black);
    _image.SetPixel(x0 + radius, y0,sf::Color::Black);
    _image.SetPixel(x0 - radius, y0,sf::Color::Black);

    while(cx < cy) {
        if(f >= 0) {
            cy--;
            ddF_y += 2;
            f += ddF_y;
        }
        cx++;
        ddF_x += 2;
        f += ddF_x;
        _image.SetPixel(x0 + cx, y0 + cy,sf::Color::Black);
        _image.SetPixel(x0 - cx, y0 + cy,sf::Color::Black);
        _image.SetPixel(x0 + cx, y0 - cy,sf::Color::Black);
        _image.SetPixel(x0 - cx, y0 - cy,sf::Color::Black);
        _image.SetPixel(x0 + cy, y0 + cx,sf::Color::Black);
        _image.SetPixel(x0 - cy, y0 + cx,sf::Color::Black);
        _image.SetPixel(x0 + cy, y0 - cx,sf::Color::Black);
        _image.SetPixel(x0 - cy, y0 - cx,sf::Color::Black);
    }

    _texture.LoadFromImage(_image);
    SFMLsprite.SetTexture(_texture);
}

void TrivialCanvas::ellipse(const int &w, const int &h) {

}

void TrivialCanvas::rect(const int &rx, const int &ry, const int &rw, const int &rh) {

}
