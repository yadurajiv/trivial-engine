#ifndef TRIVIALANIMATEDSPRITE_H_INCLUDED
#define TRIVIALANIMATEDSPRITE_H_INCLUDED

#include <iostream>

#include <map>
#include <string>

#include "TrivialApp.h"
#include "TrivialSprite.h"

namespace Trivial {

class Animation : public Object {
public:
    Animation(const float &sheetWidth, const float &sheetHeight, const float &cellWidth,
                        const float &cellHeight,const int &start, const int &end, const int &framerate) :
                        _sheetWidth(sheetWidth), _sheetHeight(sheetHeight),
                        _cellWidth(cellWidth), _cellHeight(cellHeight),
                        _frameStart(start), _frameEnd(end), _framerate(framerate),
                        _frameCurrent(start), _paused(true), _looped(true)
    {
        _rows = int(_sheetHeight/_cellHeight);
        _cols = int(_sheetWidth/_cellWidth);
        _countTotal = _rows * _cols;
        _count = (_frameEnd - _frameStart) + 1;
        _app = Trivial::App::Instance();
    }

    ~Animation();

    void play(const bool &looped = true) {
        _looped = looped;
        _paused = false;
        _frameTimeTotal = 0.0f;
    }

    int getRow() const {
        return int((_frameCurrent % _cols) * _cellWidth);
    }
    int getCol() const {
        return int((_frameCurrent / _cols) * _cellHeight);
    }
    int getFrame(int row, int col)  const {
        return int((row % _rows) * _cols + (col % _cols));
    }

    void pause() {
        _paused = true;
        _frameTimeTotal = 0;
    }

    void stop(int frame = 0) {
        _frameCurrent = frame;
        _paused = true;
        _frameTimeTotal = 0.0f;
    }

    void update() {

        if(!_paused) {
            if(_frameTimeTotal > 1/float(_framerate)) {
                if(_looped) {
                    if(_frameCurrent < _frameEnd) {
                        _frameCurrent++;
                    } else {
                        _frameCurrent = _frameStart;
                    }
                } else {
                    if(_frameCurrent < _frameEnd) {
                        _frameCurrent++;
                    } else {
                        _frameCurrent = _frameStart;
                        _paused = true;
                    }
                }

                _frameTimeTotal = 0.0f;
            } else {
                _frameTimeTotal += (_app->frameTime()/1000);
            }
        }
    }

protected:

    float _sheetWidth;
    float _sheetHeight;

    float _cellWidth;
    float _cellHeight;

    int _frameStart;
    int _frameEnd;

    int _framerate;

    int _frameCurrent;

    bool _paused;
    bool _looped;

    int _rows;
    int _cols;

    int _countTotal;
    int _count;

    float _frameTimeTotal;

    Trivial::App* _app;

};

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
