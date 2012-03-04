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
    
    // Trivial::TrivialTileMap *map;

    pauseScene() {

    }

    void preload() {
        cout << "\nPause preload";

        myApp = Trivial::App::Instance();
        mySceneManager = Trivial::SceneManager::Instance();
        myEventManager = Trivial::EventManager::Instance();
        myImageManager = Trivial::ImageManager::Instance();

        myEventManager->subscribe("escape-keyup", this);
        myEventManager->subscribe("escape-keydown", this);

        addLayer("hud", 1);
        HUDText.font("wendy");
        HUDText.text(10,5,"PAUSED!! Hit [Esc] to continue");
        cout << "\nadding pause scene hudtext - " << add("hudtext", HUDText, "hud");

        myImageManager->add("pauseText","data/pausetext.png");

        pauseText.image("pauseText");
        pauseText.moveTo(width()/2, height()/2);
        add("pauseText", pauseText);
        
        // map = new Trivial::TrivialTileMap("testperf.tmx");
        
    }

    void reset() {
        key_escape = false;

        myApp->setClearColor(100,0,0,255);

        defaultCamera.moveTo(0, 0);
        defaultCamera.lookAt(400, 300);

        cout << "\nPAUSE SCENE cam x " << defaultCamera.X();

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


        cout << "\nPAUSE SCENE cam x " << defaultCamera.X();

        if(key_escape) {
            key_escape = false;
            mySceneManager->setActiveScene("myScene");

            cout << "ACTIVATING MAI SCENE!!!" << endl;

        }
    
        // map->Draw(*myApp->getSFMLRenderWindow(), *_layers["default"]);
    }

    void deactivated() {
        _activated = false;
        cout << "\npause deactivated" << endl;
    }

    void activated() {
        _activated = true;
        cout << "\npause activated!" << endl;

        reset();
    }

    ~pauseScene() {
    }


private:

    Trivial::GUIText HUDText;
    Trivial::Sprite pauseText;

    // Trivial::Camera camera;

    bool key_escape;

    Trivial::App *myApp;
    Trivial::SceneManager *mySceneManager;
    Trivial::EventManager *myEventManager;
    Trivial::ImageManager *myImageManager;

    bool _activated;


};

#endif // PAUSE_H_INCLUDED
