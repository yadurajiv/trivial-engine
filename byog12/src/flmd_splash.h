#ifndef FLMD_SPLASH_H_INCLUDED
#define FLMD_SPLASH_H_INCLUDED

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include <list>

#include "TrivialEngine.h"

#include "Map.h"
/**

**/

using namespace std;

class flmd_splash : public Trivial::Scene {
public:

    flmd_splash() {

    }

    void preload() {

        myApp = Trivial::App::Instance();
        mySceneManager = Trivial::SceneManager::Instance();
        myEventManager = Trivial::EventManager::Instance();
        myImageManager = Trivial::ImageManager::Instance();
        myFontManager = Trivial::FontManager::Instance();
        myAudioManager = Trivial::AudioManager::Instance();
		

        // subscribing to keyboard events
        myEventManager->subscribe("up-keydown", this);
        myEventManager->subscribe("up-keyup", this);

        myEventManager->subscribe("down-keydown", this);
        myEventManager->subscribe("down-keyup", this);

        myEventManager->subscribe("left-keydown", this);
        myEventManager->subscribe("left-keyup", this);

        myEventManager->subscribe("right-keydown", this);
        myEventManager->subscribe("right-keyup", this);

        myEventManager->subscribe("escape-keydown", this);
        myEventManager->subscribe("escape-keyup", this);

        myEventManager->subscribe("spacebar-keydown", this);
        myEventManager->subscribe("spacebar-keyup", this);

        myEventManager->subscribe("z-keydown", this);
        myEventManager->subscribe("z-keyup", this);

        myEventManager->subscribe("x-keydown", this);
        myEventManager->subscribe("x-keyup", this);

        myEventManager->subscribe("1-keydown", this);
        myEventManager->subscribe("1-keyup", this);

        myEventManager->subscribe("2-keydown", this);
        myEventManager->subscribe("2-keyup", this);

        myEventManager->subscribe("3-keydown", this);
        myEventManager->subscribe("3-keyup", this);

        myEventManager->subscribe("4-keydown", this);
        myEventManager->subscribe("4-keyup", this);

        // General Mouse event test
        myEventManager->subscribe("update-mouse",this);

        // One time button stuff
        myEventManager->subscribe("buttondown-mouse", this);
        myEventManager->subscribe("buttonup-mouse", this);

        // scroll!
        myEventManager->subscribe("scroll-mouse", this);

        // Test for sub sub event functionality. Shiz's gettin trippy bro...
        myEventManager->subscribe("left-buttondown-mouse", this);
        myEventManager->subscribe("left-buttonup-mouse", this);
        myEventManager->subscribe("right-buttonup-mouse", this);
        myEventManager->subscribe("right-buttondown-mouse", this);
        myEventManager->subscribe("middle-buttonup-mouse", this);
        myEventManager->subscribe("middle-buttondown-mouse", this);

		myImageManager->add("testmap", "data/test.jpeg");

		aMap.loadMapImage("testmap");
		
		myImageManager->add("forest", "data/forest.png");
		myImageManager->add("dirt", "data/dirt.png");

		aMap.replaceRGBWithImage(221, 219, 72, "forest");
		aMap.replaceRGBWithImage(4, 183, 57, "dirt");
				
		aMap.loadMap();
		
		add("Map", aMap);
		
		// Trivial::Sprite aSprite;
		// 		aSprite.image("forest");
		// 		aSprite.moveTo(8,8);
		// 		add("aSprite",aSprite);
		
		//aMap.moveTo(400,300);


        /* loading a font */
        cout << "Loading a font! >> " << myFontManager->add("wendy","data/WENDY.TTF") << "\n";

        HUDText.font("wendy");
        HUDText.text(10,5,"FPS: 000");
        add("hudtext", HUDText);


    }

    void reset() {
        /* key state flags */
        key_up = false;
        key_down = false;
        key_left = false;
        key_right = false;
        key_escape = false;
        key_z = false;
        key_1 = false;
        key_2 = false;
        key_3 = false;
        key_4 = false;
        key_space = false;

        _mscroll = 0;

    }

    /* the event call back is called by the event manager */
    void keyBoardEventCallback(const Trivial::TrivialKeyBoardEvent &e) {
        /* un/setting flags to be used later */

        // if a key is pressed and never released when the scene is inactive, then the
        // keyup event never registers..
        /*
        if(!_activated)
            return;
        */

        if (e.eventName == "up-keydown") {
            key_up = true;
        }
        if (e.eventName == "up-keyup") {
            key_up = false;
        }

        if (e.eventName == "down-keydown") {
            key_down = true;
        }
        if (e.eventName == "down-keyup") {
            key_down = false;
        }

        if (e.eventName == "left-keydown") {
            key_left = true;
        }
        if (e.eventName == "left-keyup") {
            key_left = false;
        }

        if (e.eventName == "right-keydown") {
            key_right = true;
        }
        if (e.eventName == "right-keyup") {
            key_right = false;
        }

        if (e.eventName == "escape-keydown" && _activated) {
            key_escape = true;
        }

        if (e.eventName == "escape-keyup" && _activated) {
            key_escape = false;
        }

        if (e.eventName == "spacebar-keydown") {
            key_space = true;
        }

        if (e.eventName == "spacebar-keyup") {
            key_space = false;
        }

        if (e.eventName == "z-keydown") {
            key_z = true;
        }

        if (e.eventName == "z-keyup") {
            key_z = false;
        }

        if (e.eventName == "x-keydown") {
            key_x = true;
        }

        if (e.eventName == "x-keyup") {
            key_x = false;
        }

        if (e.eventName == "1-keydown") {
            key_1 = true;
        }

        if (e.eventName == "1-keyup") {
            key_1 = false;
        }

        if (e.eventName == "2-keydown") {
            key_2 = true;
        }

        if (e.eventName == "2-keyup") {
            key_2 = false;
        }

        if (e.eventName == "3-keydown") {
            key_3 = true;
        }

        if (e.eventName == "3-keyup") {
            key_3 = false;
        }

        if (e.eventName == "4-keydown") {
            key_4 = true;
        }

        if (e.eventName == "4-keyup") {
            key_4 = false;
        }

    }

    void mouseEventCallBack(const Trivial::TrivialMouseEvent &e) {

        if(!_activated)
            return;

        if(e.eventName == "update-mouse") {
            // Test for the general mouse update. This is an event in case any
            // aspect of the mouse changes.
            // e.pos and e.screenPosition are the same for now!!
            // so add the camera position to get world position
            _mx = e.pos.x + defaultCamera.X();
            _my = e.pos.y + defaultCamera.Y();

            screenPositionX = e.screenPosition.x;
            screenPositionY = e.screenPosition.y;

            if(e.lButton) {
            }

            if(e.rButton) {
            }

            if(e.mButton) {
            }

            if(e.x1Button) {
            }

            if(e.x2Button) {
            }
        }

        if (e.eventName == "scroll-mouse") {

        }

        if (e.eventName == "buttondown-mouse") {
            // This is when the mouse button goes down. This is called once
            // for that button. Motivation behind this was so I get an event
            // only for the click. The mouse event struct will anyway have
            // all the details about the mouse position etc.
        }

        if (e.eventName == "buttonup-mouse") {
            // Same as the button down
        }

        if (e.eventName == "left-buttondown-mouse") {

        }

        if (e.eventName == "left-buttonup-mouse") {

        }

        if (e.eventName == "middle-buttondown-mouse") {

        }

        if (e.eventName == "middle-buttonup-mouse") {

        }

        if (e.eventName == "right-buttondown-mouse") {

        }

        if (e.eventName == "right-buttonup-mouse") {

        }

        fflush(stdout);
    }

    void update() {

        if(!_activated)
            return;

        float ft = myApp->frameTime()/1000;

        ossfps.str("");
        ossfps << "FPS: " << myApp->FPS();
        HUDText.text(ossfps.str());
        flush(ossfps);

        if(key_left) {
			defaultCamera.lookAt(defaultCamera.X() - 5, defaultCamera.Y());
        }

        if(key_right) {
			defaultCamera.lookAt(defaultCamera.X() + 5, defaultCamera.Y());
        }

        if(key_up) {
			defaultCamera.lookAt(defaultCamera.X(), defaultCamera.Y() - 5);
        }

        if(key_down) {
			defaultCamera.lookAt(defaultCamera.X(), defaultCamera.Y() + 5);
        }

        if(key_escape) {
            key_escape = false;
            myApp->quit();
        }

        if(key_1) {
            key_1 = false;
        }

        if(key_2) {
            key_2 = false;
        }

        if(key_3) {
            key_3 = false;
        }

        if(key_4) {
            key_4 = false;
        }

        if(key_up || key_down || key_left || key_right) {
        }

        if(key_space) {
            key_space = false;
        }

        if(key_z) {
            key_z = false;
        }

        if(key_x) {
            key_x = false;

        }

    }

    void deactivated() {
        _activated = false;
    }

    void activated() {
        _activated = true;

        reset();
    }

    ~flmd_splash() {
    }


private:
    Trivial::GUIText HUDText;

	Map aMap;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool key_escape;
    bool key_z;
    bool key_x;
    bool key_1;
    bool key_2;
    bool key_3;
    bool key_4;
    bool key_space;

    int _mx;
    int _my;

    int screenPositionX;
    int screenPositionY;

    bool _activated;

    int _mscroll;

    /* fps output string stream */
    ostringstream ossfps;

    /**
        moved inside class since sfml has its own global variables and they might
        not be initialized before main, which causes a segfault.
        http://www.sfml-dev.org/forum/viewtopic.php?p=29824#29824
    **/
    Trivial::App *myApp;
    Trivial::SceneManager *mySceneManager;
    Trivial::EventManager *myEventManager;
    Trivial::ImageManager *myImageManager;
    Trivial::FontManager *myFontManager;
    Trivial::AudioManager *myAudioManager;

};

#endif // FLMD_SPLASH_H_INCLUDED
