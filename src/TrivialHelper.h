#ifndef TRIVIALHELPER_H_INCLUDED
#define TRIVIALHELPER_H_INCLUDED

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "TrivialObject.h"

using namespace std;


namespace Trivial {

typedef struct {
    float x;
    float y;
} TrivialPoint;
// change to Point

typedef struct {
    float x;
    float y;
    float z;
} Point3D;

typedef struct {
    float x;
    float y;
    float width;
    float height;
} TrivialRect;
// change to Rect

typedef struct {
    TrivialPoint a;
    TrivialPoint b;
    TrivialPoint c;
    TrivialPoint d;
} TrivialPointRect;
// change to PointRect

#define PI 3.1415926535897932384626433832795

class Helper : public Object {

public:
    static Helper* Instance();


    // http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
    static short sqrt(short num) {
            short op = num;
            short res = 0;
            short one = 1 << 14; // The second-to-top bit is set: 1L<<30 for long

            // "one" starts at the highest power of four <= the argument.
            while (one > op)
                one >>= 2;

            while (one != 0) {
                if (op >= res + one) {
                    op -= res + one;
                    res = (res >> 1) + one;
                }
                else
                  res >>= 1;
                one >>= 2;
            }
            return res;
    }

    static float sqrt(float z)
    {
        union
        {
            int tmp;
            float f;
        } u;

        u.f = z;

        u.tmp -= 1 << 23; /* Subtract 2^m. */
        u.tmp >>= 1; /* Divide by 2. */
        u.tmp += 1 << 29; /* Add ((b + 1) / 2) * 2^m. */

        return u.f;
    }

    static float distanceSq(const float &x1, const float &y1, const float &x2, const float &y2) {
        return (((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
    }

    static float distance(const float &x1, const float &y1, const float &x2, const float &y2) {
        return sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
    }

    static bool sphereCollision(float x1, float y1, float r1, float x2, float y2, float r2) {
        return (distanceSq(x1,y1,x2,y2) <= ((r1+r2)*(r1+r2)));
    }

    static bool AABBAABB(float axMin, float ayMin, float axMax, float ayMax, float bxMin, float byMin, float bxMax, float byMax) {
        if (axMax < bxMin || axMin > bxMax) return false;
        if (ayMax < byMin || ayMin > byMax) return false;
        return true;
    }

    static bool pointInRegularRect(float ptx, float pty, float rx, float ry, float w, float h) {
        if(ptx > rx && ptx < (rx + w) && pty > ry && pty < (ry + h)) {
            return true;
        }
        return false;
    }

/**
Thanks to Emanuele Feronato's awesome article
http://www.emanueleferonato.com/2012/03/09/algorithm-to-determine-if-a-point-is-inside-a-square-with-mathematics-no-hit-test-involved/
**/
    static int triangleArea(const float &ax, const float &ay,const float &bx,const float &by,const float &cx,const float &cy) {
        return (cx*by-bx*cy)-(cx*ay-ax*cy)+(bx*ay-ax*by);
    }

/**
Thanks to Emanuele Feronato's awesome article
http://www.emanueleferonato.com/2012/03/09/algorithm-to-determine-if-a-point-is-inside-a-square-with-mathematics-no-hit-test-involved/
**/
    static bool pointInRect(const TrivialPoint& pt, const TrivialPoint& a, const TrivialPoint& b, const TrivialPoint& c, const TrivialPoint& d) {
        if (triangleArea(a.x,a.y,b.x,b.y,pt.x,pt.y)>0 || triangleArea(b.x,b.y,c.x,c.y,pt.x,pt.y)>0 || triangleArea(c.x,c.y,d.x,d.y,pt.x,pt.y)>0 || triangleArea(d.x,d.y,a.x,a.y,pt.x,pt.y)>0) {
            return false;
        }
        return true;
    }

    static bool pointInRect(const float& ptx, const float& pty, const float& ax, const float& ay, const float& bx, const float& by, const float& cx, const float& cy, const float& dx, const float& dy) {
        if (triangleArea(ax,ay,bx,by,ptx,pty)>0 || triangleArea(bx,by,cx,cy,ptx,pty)>0 || triangleArea(cx,cy,dx,dy,ptx,pty)>0 || triangleArea(dx,dy,ax,ay,ptx,pty)>0) {
            return false;
        }
        return true;
    }

    static TrivialPoint rotatePoint(const float& ptx, const float& pty, const float& originx, const float& originy, const int& theta) {
        TrivialPoint p;
        float radians = theta * (PI / 180.0f);
        p.x = (cos(radians) * (ptx - originx) - sin(radians) * (pty - originy)) + originx;
        p.y = (sin(radians) * (ptx - originx) + cos(radians) * (pty - originy)) + originy;
        return p;
    }

    static bool pointInRect(const float& ptx, const float& pty, const TrivialPointRect& ptrect) {
        return pointInRect(ptx,pty,ptrect.a.x,ptrect.a.y,ptrect.b.x,ptrect.b.y,ptrect.c.x,ptrect.c.y,ptrect.d.x,ptrect.d.y);
    }

    static bool pointInRect(const TrivialPoint& pt, const TrivialPointRect& ptrect) {
        return pointInRect(pt.x,pt.y,ptrect.a.x,ptrect.a.y,ptrect.b.x,ptrect.b.y,ptrect.c.x,ptrect.c.y,ptrect.d.x,ptrect.d.y);
    }

    static float getAngle(const float& pt1x, const float& pt1y, const float& pt2x, const float& pt2y) {
			return atan2(pt2x - pt1x,pt1y - pt2y) * 180 / PI;
    }

    static float abs(float x) {
        return (x < 0) ? -x : x;
    }

    static void makePointRect(TrivialPointRect* prect, const float& x, const float& y, const float& w, const float& h) {
        prect->a.x = x;
        prect->a.y = y;
        prect->b.x = x + w;
        prect->b.y = y;
        prect->c.x = x + w;
        prect->c.y = y + h;
        prect->d.x = x;
        prect->d.y = y + h;
    }

    static void makePointRectAroundPoint(TrivialPointRect* prect, const float& x, const float& y, const float& w, const float& h) {
        prect->a.x = x - w/2;
        prect->a.y = y - w/2;
        prect->b.x = x + w/2;
        prect->b.y = y - w/2;
        prect->c.x = x + w/2;
        prect->c.y = y + h/2;
        prect->d.x = x - w/2;
        prect->d.y = y + h/2;
    }

    static void rotatePointRect(TrivialPointRect* prect,const float& originx, const float& originy, const float& angle) {
        prect->a = Trivial::Helper::rotatePoint(prect->a.x, prect->a.y, originx, originy, angle);
        prect->b = Trivial::Helper::rotatePoint(prect->b.x, prect->b.y, originx, originy, angle);
        prect->c = Trivial::Helper::rotatePoint(prect->c.x, prect->c.y, originx, originy, angle);
        prect->d = Trivial::Helper::rotatePoint(prect->d.x, prect->d.y, originx, originy, angle);
    }

    static void UintToRGBA(const unsigned int& uicolor, int* r, int* g, int* b, int* a) {
            *r = (uicolor >> 16) & 0xFF;
			*g = (uicolor >> 8) & 0xFF;
			*b = uicolor & 0xFF;
			*a = int((uicolor >> 24) & 0xFF) / 255;
    }

    static unsigned int RGBAtoUint(const int& r, const int& g, const int& b, const int& a) {
        return (((a>1)?a:(a * 255)) & 0xFF) << 24 | (r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF);
    }

    static int random(int seed) {
        return ((69621 * int(seed * 0x7FFFFFFF)) % 0x7FFFFFFF) / 0x7FFFFFFF;
    }

    static int randomRange(const int& min=0, const int& max=100) {
        return floor(rand() % (max - min - 1)) + min;
    }

private:
    Helper();  // Private so that it can  not be called
    ~Helper();

    Helper(Helper const&){};             // copy constructor is private
    Helper& operator=(Helper const&){};  // assignment operator is private

    static Helper* _pInstance;


};

}

#endif // TRIVIALHELPER_H_INCLUDED
