#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include "TrivialEngine.h"

using namespace std;

class pauseScene : public Trivial::Scene {
public:

    pauseScene() {

    }

    void init() {

        mySceneManager = Trivial::SceneManager::Instance();
        myEventManager = Trivial::EventManager::Instance();


        //enableBox2DPhysics();

        /* key state flags */
        key_escape = false;

        myEventManager->subscribe("escape-keyup", this);
        myEventManager->subscribe("escape-keydown", this);

        addLayer("hud", 1);
        HUDText.font("wendy");
        HUDText.text(10,5,"PAUSED!! Hit [Esc] to continue");
        add("hudtext", HUDText, "hud");

        /* set the camera to the current scene */
        //camera.setScene("pause");

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

    void update() {
        if(!_activated)
            return;

        if(key_escape) {
            key_escape = false;
            mySceneManager->setActiveScene("myScene");
        }

    }

    void deactivated() {
        _activated = false;
        cout << "\npause deactivated" << endl;
    }

    void activated() {
        _activated = true;
        cout << "\npause activated!" << endl;
    }

    ~pauseScene() {
    }


private:

    Trivial::GUIText HUDText;


    // Trivial::Camera camera;

    bool key_escape;

    Trivial::App *myApp;
    Trivial::SceneManager *mySceneManager;
    Trivial::EventManager *myEventManager;

    bool _activated;


};

#endif // PAUSE_H_INCLUDED
