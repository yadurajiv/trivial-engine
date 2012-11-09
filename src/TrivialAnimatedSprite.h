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

    void play(const bool &looped = true,int frame = 0) {
        _frameCurrent = frame;
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
    /**
        constructor for the class.
    */
    AnimatedSprite() { };

    /**
        destructor for the class.
    */
    ~AnimatedSprite() { };

    /**
        The main update function of the class that is supposed to be overridden
    */
    virtual void update() { };

    /**
        Used internally for updates
    */
    virtual void _update(const bool& render = false);

    /**
        Set the image to be used by this sprite

        @param name - The name of the image that was loaded by the ImageManager
        @param cellWidth - The width of one cell in the sprite sheet
        @param cellHeight - The height of one cell in the sprite sheet
    */
    void image(const string &name, const float &cellWidth, const float &cellHeight);

    /**
        This funciton is used to create a named animation sequence. For example in your
        sprite sheet frames 0 1 2 3 4 5 6 is a walk cycle, you can create and store an
        animation by calling addAnimation("walk",0,5,12); assuming your animation has to run at 12fps

        @param name - The name of the animation used later by play and stop functions
        @param startFrame - The first frame number in the sequence of frames to be used
        @param endFrame - The last frame where the animation ends
        @param framerate - The framerate at which the animation needs to be played back

        @see play
        @see gotoAndPlay
        @see stop
        @see gotoAndStop
    */
    bool addAnimation(const string &name, const int &startFrame, const int &endFrame, const int &framerate);

    /*
        animated sprites return cellHeight and cellWidth, should they be setting
        cellHeight and cellWidth instead of _width and _height?
    */
    /*
    using Sprite::width;
    using Sprite::height;
    */
    /**
        Returns the width of the Animated sprite.

        @see height
        @see textureWidth
        @see textureHeight
    */
    virtual float width() const { return _cellWidth; };

    /**
        Returns the height of the Animated sprite.

        @see width
        @see textureWidth
        @see textureHeight
    */
    virtual float height() const { return _cellHeight; };

    /**
        Returns the width of the sprite texture used.

        @see width
        @see height
        @see textureHeight
    */
    virtual float textureWidth() const { return _width; };

    /**
        Returns the height of the sprite texture used.

        @see width
        @see height
        @see textureWidth
    */
    virtual float textureHeight() const { return _height; };

    //bool removeAnimation(string name);

    /**
        This function plays a given named animation sequence

        @param name - Name of the animation created
        @param looped - Should the animation be looped or not
    */
    bool play(const string& name = "", const bool& looped = true);

    /**
        This function moves the play head to a particular frame in a named animation sequence and plays

        @param name - Name of the animation created
        @param frame - The frame number to jump to before playing
        @param looped - Should the animation be looped or not
    */
    bool gotoAndPlay(const string& name = "", const int& frame = 0, const bool& looped = true);

    /**
        This function stops a given named animation sequence

        @param name - Name of the animation created
        @param looped - Should the animation be looped or not
    */
    bool stop(const string &name = "");

    /**
        This function moves the play head to a particular frame in a named animation sequence and stops

        @param name - Name of the animation created
        @param frame - The frame number to jump to before stopping
        @param looped - Should the animation be looped or not
    */
    bool gotoAndStop(const string& name = "", const int& frame = 0);


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
