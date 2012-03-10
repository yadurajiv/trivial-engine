#include "TrivialCanvas.h"
#include <iostream>

using namespace std;

namespace Trivial {

Canvas::Canvas() {
    //ctor
    _cursorX = 0;
    _cursorY = 0;
}

void Canvas::create(const int &w, const int &h,const sf::Color& color) {
    _width = w;
    _height = h;
    _clearColor = color;

    _originX = _width/2;
    _originY = _height/2;

    clear();
}

void Canvas::_update() {
    Sprite::_update();
}

void Canvas::clear(const sf::Color& color) {
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

void Canvas::setPixel(const int &x, const int &y,const sf::Color& color) {
        if(pointOverlap(x,y)) {
            int lx = getLocalX(x);
            int ly = getLocalY(y);
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
void Canvas::line(const int &x, const int &y, const int &tx, const int &ty) {
    if(!pointOverlap(x,y) || !pointOverlap(tx,ty)) {
        cout << "Canvas::line - Error - Points lie outside drawable area.";
        return;
    }

    int lx = getLocalX(x);
    int ly = getLocalY(y);
    int tlx = getLocalX(tx);
    int tly = getLocalY(ty);
    cout << "\nly: " << ly << " ly: " << ly << " \nto tlx: " << tlx << " tly: " << tly << "\n";
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

    while(lx != tlx || ly != tly) {
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

        if(lx == tlx && ly == tly)
            break;
    }

    _texture.LoadFromImage(_image);
    SFMLsprite.SetTexture(_texture);
}

// get the safest point inside the drawable area and draw to it than crash
void Canvas::line(const float& lx1, const float& ly1, const float& lx2, const float& ly2) {
    if(!pointOverlap(lx1,ly1) || !pointOverlap(lx2,ly2)) {
        cout << "Canvas::line - Error - Points lie outside drawable area.";
        return;
    }

    float x1 = getLocalX(lx1);
    float y1 = getLocalY(ly1);
    float x2 = getLocalX(lx2);
    float y2 = getLocalY(ly2);

	float xdiff = (x2 - x1);
	float ydiff = (y2 - y1);

	if(xdiff == 0.0f && ydiff == 0.0f) {
		_image.SetPixel(x1,y1,sf::Color::Black);
		return;
	}

	if(fabs(xdiff) > fabs(ydiff)) {
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if(x1 < x2) {
			xmin = x1;
			xmax = x2;
		} else {
			xmin = x2;
			xmax = x1;
		}

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		for(float x = xmin; x <= xmax; x += 1.0f) {
			float y = y1 + ((x - x1) * slope);
			//Color color = color1 + ((color2 - color1) * ((x - x1) / xdiff));
			_image.SetPixel(x,y,sf::Color::Black);
		}
	} else {
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if(y1 < y2) {
			ymin = y1;
			ymax = y2;
		} else {
			ymin = y2;
			ymax = y1;
		}

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		for(float y = ymin; y <= ymax; y += 1.0f) {
			float x = x1 + ((y - y1) * slope);
			//Color color = color1 + ((color2 - color1) * ((y - y1) / ydiff));
			_image.SetPixel(x,y,sf::Color::Black);
		}
	}

    _texture.LoadFromImage(_image);
    SFMLsprite.SetTexture(_texture);

}

void Canvas::circle(const int &x, const int &y, const int &radius) {
    // maybe -> //if(!pointOverlap(x,y+radius) || !pointOverlap(x,y-radius) || !pointOverlap(x+radius,y) || !pointOverlap(x-radius,y) || !pointOverlap(x+radius,y+radius) || !pointOverlap(x-radius,y-radius) || !pointOverlap(x+radius,y-radius) || !pointOverlap(x-radius,y+radius)) {
    if(!pointOverlap(x,y+radius) || !pointOverlap(x,y-radius) || !pointOverlap(x+radius,y) || !pointOverlap(x-radius,y)) {
        cout << "\nno circle for you!";
        return;
    }

    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int cx = 0;
    int cy = radius;
    int x0 = getLocalX(x);
    int y0 = getLocalY(y);

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

void Canvas::ellipse(const int &w, const int &h) {

}

void Canvas::rect(const TrivialPointRect& ptrect) {
    line(ptrect.a.x,ptrect.a.y,ptrect.b.x,ptrect.b.y);
    line(ptrect.b.x,ptrect.b.y,ptrect.c.x,ptrect.c.y);
    line(ptrect.c.x,ptrect.c.y,ptrect.d.x,ptrect.d.y);
    line(ptrect.d.x,ptrect.d.y,ptrect.a.x,ptrect.a.y);
}

void Canvas::rect(const int &rx, const int &ry, const int &rw, const int &rh) {

}

}
