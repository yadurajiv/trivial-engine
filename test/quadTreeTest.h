#ifndef QUADTREETEST_H_INCLUDED
#define QUADTREETEST_H_INCLUDED


#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include "TrivialEngine.h"

using namespace std;

class quadTreeTest : public Trivial::Scene {
public:

    quadTreeTest() {

    }

    void preload() {
        cout << "\nQuad Tree test preload";

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

        //cout << "\nQuad Tree test init!";

        /* key state flags */
        key_escape = false;
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

    }

    void update() {
        if(!_activated)
            return;

        cout << "\ncam x " << defaultCamera.X();

        ossHUD.str("");
        ossHUD << "FPS: " << myApp->FPS();
        ossHUD << "\nMouse X: " << _mx;
        ossHUD << "\nMouse Y: " << _my;
        HUDText.text(ossHUD.str());
        flush(ossHUD);

        if(key_escape) {
            key_escape = false;
            mySceneManager->setActiveScene("myScene");
        }


    }

    void deactivated() {
        _activated = false;
        cout << "\nmouseDrawing deactivated" << endl;
    }

    void activated() {
        _activated = true;
        cout << "\nmouseDrawing activated!" << endl;
    }

    ~quadTreeTest() {
    }


private:

    Trivial::GUIText HUDText;


    // Trivial::Camera camera;

    bool key_escape;

    Trivial::App *myApp;
    Trivial::SceneManager *mySceneManager;
    Trivial::EventManager *myEventManager;

    bool _activated;

    float _mx;
    float _my;

    ostringstream ossHUD;
};

#endif // QUADTREETEST_H_INCLUDED
