#ifndef TRIVIALAPP_H_INCLUDED
#define TRIVIALAPP_H_INCLUDED

#include <iostream>

#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialObject.h"

using namespace std;

namespace Trivial {


class App : public Object {

public:
    static App* Instance();

    int run();

    // TODO: Do config shite here
    bool configure(sf::WindowHandle windowHandle = NULL, const unsigned int &width = 800, const unsigned int &height = 600, const int &colorDepth = 32, const string &windowTitle = "Trivial App", bool autoUpdate = true);

    void render(sf::Drawable& sprite);

    void renderView(sf::View& view);

    void update();

    // total elapsed time
    float totalTimeElapsed() const;

    // time per frame
    float frameTime() const { return _app.GetFrameTime(); }

    float FPS() const { return _fps; }

    sf::FloatRect getWindowRect() const { return sf::FloatRect(0, 0, _width, _height); };

    float GetWidth() const { return _width; };
    float GetHeight() const { return _height; };

    void quit() { _quitFlag = true; };

    // trivial color?
    sf::Color getClearColor() { return _clearColor; }
    void setClearColor(unsigned int r=0, unsigned int g=0, unsigned int b=0, unsigned int a=255) { _clearColor = sf::Color(r,g,b,a); }

    sf::RenderWindow* getSFMLRenderWindow() {
        return &_app;
    }

private:
    App();  // Private so that it can  not be called

    App(App const&){};             // copy constructor is private
    App& operator=(App const&){};  // assignment operator is private

    static App* _pInstance;

    unsigned int _height;
    unsigned int _width;
    int _colorDepth;
    string _windowTitle;
    bool _autoUpdate;

    sf::RenderWindow _app;
    sf::Event _appEvent;
    sf::WindowHandle _handle;

    sf::Color _clearColor;

    float _ft;
    float _timeElapsed;
    float _fps;
    float _fpsTime;

    bool _quitFlag;
};


}

#endif // TRIVIALAPP_H_INCLUDED
