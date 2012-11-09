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
    /**
        Returns the instance of the current Trivial::App
    */
    static App* Instance();

    /**
        This usually is the second call to the app class right after configure.
        This creates the main application window(a child window, if a parent handle
        is passed via configure) and runs the main loop. Upon completion it returns 0

        @see configure
    */
    int run();

    /**
        This function is called before run. You set most of your primary options here.

        @param windowHandle - is the handle of the parent window, if you want to run trivial as a child to a window(eg: an editor)
        @param width - is the width of the window to be created
        @param height - is the height of the window to be created
        @param colorDepth - the bit depth of the current render surface, usually same ask the desktop if your app is not fullscreen
        @param windowTitle - the title of the current window
        @param fullscreen - set true to start the application in fullscreen mode
        @param autoUpdate - is true by default, setting this to false will not run the main loop and return right after the window is created after you call run, this is useful when you want to manually call the update function

        @see run
    */
    bool configure(sf::WindowHandle windowHandle = NULL, const unsigned int &width = 800, const unsigned int &height = 600, const int &colorDepth = 32, const string &windowTitle = "Trivial App", bool fullscreen = false, bool autoUpdate = true);

    /**
        The main render function to draw any sfml sprite onto the current render surface. Mostly always used internally.

        @param sprite - is any SFML Drawable
    */
    void render(sf::Drawable& sprite);

    /**
        renderView sets the current view to the given SFML view. Mostly always used internally.

        @param view - is an SFML View
    */
    void renderView(sf::View& view);

    /**
        The update function, usually called in the main loop in run. This can also be called manually if you are doing manual updates.
    */
    void update();

    /**
        Total elapsed time since the app started
    */
    float totalTimeElapsed() const;

    /**
        Time per frame in Milliseconds
    */
    float frameTime() const { return _frameTime; }

    /**
        Current Framerate, frame per second.
    */
    float FPS() const { return _fps; }

    /**
        This funciton returns the current window's position and dimensions as an SFML FloatRect
    */
    sf::FloatRect getWindowRect() const { return sf::FloatRect(0, 0, _width, _height); };

    /**
        Gets you the current window's width.
    */
    float width() const { return _width; };

    /**
        Gets you the current window's height.
    */
    float height() const { return _height; };

    /**
        Sets an internal _quitFlag to true which safely quits the application
    */
    void quit() { _quitFlag = true; };

    /**
        This function gets you the current color that is used to clear the screen before each frame is redrawn

        @see setClearColor
    */
    sf::Color getClearColor() { return _clearColor; }

    /**
        This function lets you set the color that is used to clear the screen before each frame is redrawn

        @param r - is the red value of the color, between 0 and 255
        @param g - is the green value of the color, between 0 and 255
        @param b - is the blue value of the color, between 0 and 255
        @param a - is the alpha value of the color, between 0 and 255

        @see getClearColor
    */
    void setClearColor(unsigned int r=0, unsigned int g=0, unsigned int b=0, unsigned int a=255) { _clearColor = sf::Color(r,g,b,a); }

    /**
        This function returns the current SFML RenderWindow. Mostly always used internally.
    */
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

    unsigned long _windowStyle;

    // read information on ContextSettings.hpp for more on why this is not used.
    sf::ContextSettings _contextSettings;

    sf::Color _clearColor;

    sf::Clock _clock;
    sf::Clock _ftimer;
    sf::Time _time;
    float _frameTime;
    float _fps;

    bool _quitFlag;
};


}

#endif // TRIVIALAPP_H_INCLUDED
