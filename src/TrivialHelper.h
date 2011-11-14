#ifndef TRIVIALHELPER_H_INCLUDED
#define TRIVIALHELPER_H_INCLUDED

#include "TrivialObject.h"

using namespace std;


namespace Trivial {

typedef struct {
    float x;
    float y;
} TrivialPoint;

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

    static bool pointInRect(float ptx, float pty, float rx, float ry, float w, float h) {
        if(ptx > rx && ptx < (rx + w) && pty > ry && pty < (ry + h)) {
            return true;
        }
        return false;
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
