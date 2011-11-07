#include "TrivialApp.h"
#include "TrivialSceneManager.h"
#include "TrivialEventManager.h"
#include "TrivialAudioManager.h"

namespace Trivial {

App* App::_pInstance;

App::App() {
    _handle = NULL;
    _width = 800;
    _height = 600;
    _colorDepth = 32;
    _windowTitle = "Trivial App";
    _timeElapsed = 0;
    _autoUpdate = true;
    _quitFlag = false;
}

App* App::Instance()
{
   if (!_pInstance)   // Only allow one instance of class to be generated.
      _pInstance = new App;

   return _pInstance;
}

void App::render(sf::Drawable& drawable) {
    _app.Draw(drawable);
}

void App::renderView(sf::View& view) {
    _app.SetView(view);
}

int App::run() {

    if(_handle == NULL) {
        _app.Create(sf::VideoMode(_width, _height, _colorDepth), _windowTitle);
    } else {
        _autoUpdate = false;
        _app.Create(_handle);
    }

    // set app frame rate limit here! customizable later on if need be.      
    _app.SetFramerateLimit(60);

    if(_autoUpdate) {
        while(_app.IsOpened()) {
            update();
        }
    }

    return 0;
}

void App::update() {
    _fps++;

    // freeeeedom!!
    if(_quitFlag) {
        Trivial::EventManager::Instance()->releaseResource();
        Trivial::AudioManager::Instance()->releaseResources();
        _app.Close();
    }

    while (_app.PollEvent(_appEvent))
    {
         // Close window : exit
        if (_appEvent.Type == sf::Event::Closed) {
            this->quit();
        }

    }

    EventManager::Instance()->update();

    _app.Clear();

    SceneManager::Instance()->update();

    /* display app */
    _app.Display();

    _ft = _app.GetFrameTime();

    _timeElapsed += _ft;

    _fps = (1/_ft)*1000;
}

// TODO: add WindowSettings param and also sf::Style
// look at app.Create for more
// void Create(VideoMode Mode, const std::string& Title, unsigned long WindowStyle = Style::Resize | Style::Close, const WindowSettings& Params = WindowSettings());
/*
sf::WindowSettings
    DepthBits        (Depth),
    StencilBits      (Stencil),
    AntialiasingLevel(Antialiasing)
*/
/*
sf::Style::
        None       = 0,      ///< No border / title bar (this flag and all others are mutually exclusive)
        Titlebar   = 1 << 0, ///< Title bar + fixed border
        Resize     = 1 << 1, ///< Titlebar + resizable border + maximize button
        Close      = 1 << 2, ///< Titlebar + close button
        Fullscreen = 1 << 3  ///< Fullscreen mode (this flag and all others are mutually exclusive)
*/

bool App::configure(sf::WindowHandle windowHandle, const int &width, const int &height, const int &colorDepth, const string &windowTitle, bool autoUpdate) {
    _handle = windowHandle;
    _width = width;
    _height = height;
    _colorDepth = colorDepth;
    _windowTitle = windowTitle;
    _autoUpdate = autoUpdate;

    return true;
}

/** Segmentation fault **/
float App::totalTimeElapsed() const {
    if(_app.IsOpened()) {
        return _timeElapsed;
    }
    return -1;
}

}
