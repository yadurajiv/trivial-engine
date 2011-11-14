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
    bool configure(sf::WindowHandle windowHandle = NULL, const int &width = 800, const int &height = 600, const int &colorDepth = 32, const string &windowTitle = "Trivial App", bool autoUpdate = true);

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

    sf::Vector2i getMousePositionRel() {
        _lastMousePositionRelative = sf::Mouse::GetPosition(_app);
        return _lastMousePositionRelative;
    }

    int getMouseXRel() {
        getMousePositionRel();
        return _lastMousePositionRelative.x;
    }

    int getMouseYRel() {
        getMousePositionRel();
        return _lastMousePositionRelative.y;
    }

    void setMousePositionRel(sf::Vector2i &pos) {
        setMouseXYToScreen(pos.x, pos.y);
    }

    void setMouseXYToScreen(int x, int y) {
        _lastMousePositionRelative.x = x;
        _lastMousePositionRelative.y = y;
        sf::Mouse::SetPosition(_lastMousePositionRelative, _app);
    }

    sf::Vector2i getMousePositionDesk() {
        _lastMousePosition = sf::Mouse::GetPosition();
        return _lastMousePosition;
    }

    int getMouseXDesk() {
        getMousePositionDesk();
        return _lastMousePosition.x;
    }

    int getMouseYDesk() {
        getMousePositionDesk();
        return _lastMousePosition.y;
    }

    void setMousePositionDesk(sf::Vector2i &pos) {
        setMouseXYDesk(pos.x, pos.y);
    }

    void setMouseXYDesk(int x, int y) {
        _lastMousePosition.x = x;
        _lastMousePosition.y = y;
        sf::Mouse::SetPosition(_lastMousePosition);
    }

    void quit() { _quitFlag = true; };

private:
    App();  // Private so that it can  not be called

    App(App const&){};             // copy constructor is private
    App& operator=(App const&){};  // assignment operator is private

    static App* _pInstance;

    int _height;
    int _width;
    int _colorDepth;
    string _windowTitle;
    bool _autoUpdate;

    sf::Vector2i _lastMousePosition;
    sf::Vector2i _lastMousePositionRelative;

    sf::RenderWindow _app;
    sf::Event _appEvent;
    sf::WindowHandle _handle;

    float _ft;
    float _timeElapsed;
    float _fps;
    float _fpsTime;

    bool _quitFlag;
};


}

#endif // TRIVIALAPP_H_INCLUDED
