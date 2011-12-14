#ifndef MOUSEDRAWING_H_INCLUDED
#define MOUSEDRAWING_H_INCLUDED

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include "TrivialEngine.h"

using namespace std;

class mouseDrawing : public Trivial::Scene {
public:

    mouseDrawing() {

    }

    void preload() {
        cout << "\nMouse Drawing preload";

        myApp = Trivial::App::Instance();

        mySceneManager = Trivial::SceneManager::Instance();
        myEventManager = Trivial::EventManager::Instance();

        myEventManager->subscribe("escape-keyup", this);
        myEventManager->subscribe("escape-keydown", this);

        // General Mouse event test
        myEventManager->subscribe("update-mouse",this);

        addLayer("hud", 1);
        HUDText.font("wendy");
        HUDText.text(10,5,"Hit [Esc] to continue");
        add("hudtext", HUDText, "hud");

//        cout << "\nMouse Drawing init!";

        /* key state flags */
        key_escape = false;

        _line = sf::Shape();

        myApp->setClearColor(0,0,0,255);

        _line.EnableFill(false);
        _line.EnableOutline(true);
        _line.SetOutlineThickness(4);
    }

    /* the event call back is called by the event manager */
    void keyBoardEventCallback(const Trivial::TrivialKeyBoardEvent &e) {
        if(!_activated)
            return;

        /* un/setting flags to be used later */

        if (e.eventName == "escape-keydown") {
            key_escape = true;
        }

        if (e.eventName == "escape-keyup") {
            key_escape = false;
        }
    }

    void mouseEventCallBack(const Trivial::TrivialMouseEvent &e) {
        if(!_activated)
            return;

        _mx = e.pos.x;
        _my = e.pos.y;

        if(_lastX != e.pos.x) {
            _lastX = e.pos.x;
            _draw = true;
        }

        if(_lastY != e.pos.y) {
            _lastY = e.pos.y;
            _draw = true;
        }

        if(_draw) {
            _line.AddPoint(_lastX,_lastY,sf::Color(0,0,0,0),sf::Color(255,255,255,255));

            _draw = false;
        }


    }

    void update() {
        if(!_activated)
            return;

        cout << "\ncam x " << defaultCamera.X();

        ossHUD.str("");
        ossHUD << "FPS: " << myApp->FPS();
        ossHUD << "\nMouse X: " << _mx;
        ossHUD << "\nMouse Y: " << _my;
        ossHUD << "\nVertex Count: " << _line.GetPointsCount();
        ossHUD << "\nPoly Count: " << _line.GetPointsCount()/2;
        HUDText.text(ossHUD.str());
        flush(ossHUD);

        if(key_escape) {
            key_escape = false;
            mySceneManager->setActiveScene("myScene");
        }

        // draws me a line biatch!
        //myApp->getSFMLRenderWindow()->Draw(sf::Shape::Line(0.0f,0.0f,_mx,_my,1.0f,sf::Color::Red,0.0f,sf::Color::Blue));

        myApp->getSFMLRenderWindow()->Draw(_line);

    }

    void deactivated() {
        _activated = false;
        cout << "\nmouseDrawing deactivated" << endl;
    }

    void activated() {
        _activated = true;
        cout << "\nmouseDrawing activated!" << endl;
    }

    ~mouseDrawing() {
    }


private:

    Trivial::GUIText HUDText;


    // Trivial::Camera camera;

    bool key_escape;

    Trivial::App *myApp;
    Trivial::SceneManager *mySceneManager;
    Trivial::EventManager *myEventManager;

    bool _activated;

    float _lastX;
    float _lastY;

    float _mx;
    float _my;

    ostringstream ossHUD;

    bool _draw;

    sf::Shape _line;
};

#endif // MOUSEDRAWING_H_INCLUDED
