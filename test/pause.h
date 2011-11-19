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
        key_spacebar = false;

        myEventManager->subscribe("spacebar-keyup", this);
        myEventManager->subscribe("spacebar-keydown", this);

        addLayer("hud", 1);
        HUDText.font("wendy");
        HUDText.text(10,5,"PAUSED!! Hit [Spacebar] to continue");
        add("hudtext", HUDText, "hud");

        /* set the camera to the current scene */
        //camera.setScene("pause");

    }

    /* the event call back is called by the event manager */
    void keyBoardEventCallback(const string &eventName) {

        /* un/setting flags to be used later */

        if (eventName == "spacebar-keydown") {
            key_spacebar = true;
        }

        if (eventName == "spacebar-keyup") {
            key_spacebar = false;
        }
    }

    void update() {

        if(key_spacebar) {
            key_spacebar = false;
            mySceneManager->setActiveScene("myScene");
        }

    }

    void deactivated() {
        cout << "\npause deactivated" << endl;
    }

    void activated() {
        cout << "\npause activated!" << endl;
    }

    ~pauseScene() {
    }


private:

    Trivial::GUIText HUDText;


    // Trivial::Camera camera;

    bool key_spacebar;

    Trivial::App *myApp;
    Trivial::SceneManager *mySceneManager;
    Trivial::EventManager *myEventManager;


};

#endif // PAUSE_H_INCLUDED
