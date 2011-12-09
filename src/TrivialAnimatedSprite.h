#ifndef TRIVIALANIMATEDSPRITE_H_INCLUDED
#define TRIVIALANIMATEDSPRITE_H_INCLUDED

#include <iostream>

#include <map>
#include <string>

#include "TrivialSprite.h"
#include "TrivialAnimation.h"

namespace Trivial {

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite() { };
    ~AnimatedSprite() { };

    virtual void update() { };

    virtual void _update();

    void image(const string &name, const float &cellWidth, const float &cellHeight);

    bool addAnimation(const string &name, const int &startFrame, const int &endFrame, const int &framerate);

    virtual float width() const { return _cellWidth; };
    virtual float height() const { return _cellHeight; };

    virtual float textureWidth() const { return _width; };
    virtual float textureHeight() const { return _height; };

    //bool removeAnimation(string name);

    bool play(const string &name);

    //void pause(string name);


protected:

    float _cellWidth;
    float _cellHeight;

    int _rowCount;
    int _colCount;

    map<string, Animation*> _animations;

    string _currentAnimation;

    sf::IntRect _cell;

    bool _ready;

};

}

#endif // TRIVIALANIMATEDSPRITE_H_INCLUDED
