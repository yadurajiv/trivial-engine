#include "TrivialApp.h"
#include "TrivialSceneManager.h"
#include "TrivialEventManager.h"
#include "TrivialAudioManager.h"
#include "TrivialFontManager.h"
#include "TrivialImageManager.h"

namespace Trivial {

App* App::_pInstance;

App::App() {
    _handle = NULL;
    _width = 800;
    _height = 600;
    _colorDepth = 32;
    _windowTitle = "Trivial App";
    _autoUpdate = true;
    _quitFlag = false;
    _clearColor = sf::Color(0,0,0,255);
	getBuffer = false;
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

    /*
    Exit crash fix

    sf::Font fnt(sf::Font::GetDefaultFont());
    sf::Text txt("Test", fnt);
*/
    // set app frame rate limit here! customizable later on if need be.
    _app.SetFramerateLimit(60);

    if(_autoUpdate) {
        while(_app.IsOpen()) {
            update();
        }
    }

    return 0;
}

void App::update() {
    _ftimer.GetElapsedTime();
    _fps++;

    // freeeeedom!!
    if(_quitFlag) {
        Trivial::EventManager::Instance()->releaseResource();
        Trivial::FontManager::Instance()->releaseResources();
        Trivial::ImageManager::Instance()->releaseResources();
        Trivial::AudioManager::Instance()->releaseResources();
        _app.Close();
        return;
    }

    // NOTE: PollEvent will remove all items that are in the event queue!
    // calling PollEvent elsewhere like the event manager will not work!
    while (_app.PollEvent(_appEvent))
    {
         // Close window : exit
        if (_appEvent.Type == sf::Event::Closed) {
            this->quit();
        }

        // Some classes need to be informed of these events
        // Funny how we have to tell the eventmanager about an event.
        // Can't do this inside the eventmanager as all the events get
        // eaten up here. Tried it before doing this.
        if (_appEvent.Type == sf::Event::GainedFocus) {
            EventManager::Instance()->gainedWindowFocus();
        }

        if (_appEvent.Type == sf::Event::LostFocus) {
            EventManager::Instance()->lostWindowFocus();
        }

        EventManager::Instance()->setEvent(_appEvent); // we are polling, so use it!
    }

    EventManager::Instance()->update();

    _app.Clear(_clearColor);

    SceneManager::Instance()->update();

	if(getBuffer)
	{
		getBuffer = false;
	}

    /* display app */
    _app.Display();

    _time = _ftimer.Restart();

    _frameTime = _time.AsMilliseconds();

    _fps = (1/_frameTime)*1000;
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

bool App::configure(sf::WindowHandle windowHandle, const unsigned int &width, const unsigned int &height, const int &colorDepth, const string &windowTitle, bool autoUpdate) {
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
    if(_app.IsOpen()) {
        return _clock.GetElapsedTime().AsSeconds();
    }
    return -1;
}

}
