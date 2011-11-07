#ifndef TRIVIALANIMATION_H_INCLUDED
#define TRIVIALANIMATION_H_INCLUDED

#include "TrivialApp.h"

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
        _rows = int(_sheetWidth/_cellWidth);
        _cols = int(_sheetHeight/_cellHeight);
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
            if(_frameTimeTotal > 1/_framerate) {
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

}

#endif // TRIVIALANIMATION_H_INCLUDED
