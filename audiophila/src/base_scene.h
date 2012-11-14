#ifndef BASE_SCENE_H_INCLUDED
#define BASE_SCENE_H_INCLUDED

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include <list>

#include <array>

#include "TrivialEngine.h"

/**

**/

using namespace std;

class base_scene : public Trivial::Scene {
public:

    base_scene() {

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


        cout << "Loading music file >> ";
        myAudioManager->add("bgmusic","data/test.ogg", false); // Spatialization only works on mono sounds!!
        //myAudioManager->add("bgmusic","../test/data/maenamMono.ogg", false); // Spatialization only works on mono sounds!!
        myAudioManager->setSoundPosition("bgmusic",300,300); // positioned with the explosion sprite
        myAudioManager->setSoundAttenuation("bgmusic",10); // fall off
        myAudioManager->setSoundDistance("bgmusic",600); // minimum distance till the sound is heard
        cout << myAudioManager->play("bgmusic") << "\n"; // play loaded music
        myAudioManager->loop("bgmusic",true);

        microSampleRate = myAudioManager->getSampleRate("bgmusic") / 1000;
        bgmSamples = myAudioManager->getSamples("bgmusic");

        /* loading a font */
        cout << "Loading a font! >> " << myFontManager->add("wendy","data/WENDY.TTF") << "\n";

        cout << "adding a layer: " << addLayer("hud",1) << "\n";
        cout << "adding a layer: " << addLayer("meh",-1) << "\n";

        HUDText.font("wendy");
        HUDText.text(10,5,"FPS: 000");
        add("hudtext", HUDText,"hud");

        myImageManager->add("bg","../test/data/blob.png");

        setLayerCameraDamp("hud",0,0);

        myImageManager->createTexture("dot",1,1,sf::Color::White);
        myImageManager->createTexture("box",1,300,sf::Color::Cyan);

        stringstream box;
        string eqs;

        for(int j=0;j<800;j++) {
            box.str("");
            eq4[j].image("box");
            eq4[j].moveTo(j,300);
            eq4[j].setAlpha(64);
            eq4[j].setBlendMode( "add");
            box << "eqx" << j;
            eqs = box.str();
            add(eqs,eq4[j],"meh");
        }

        for(int i=0;i<800;i++) {
            eq[i].image("dot");
            eq[i].moveTo(i+0.5f,300);
            eq[i].setAlpha(64);
            //eq[i].setBlendMode( "add");
            eq[i].setColor(255,256 * i / 800,255,255);
            box.str("");
            box << "eq" << i;
            eqs = box.str();
            add(eqs,eq[i]);
        }

        bg.image("bg");
        bg.moveTo(400,300);
        bg.setAngularAcceleration(20);
        bg.setAlpha(64);
        bg.setBlendMode("add");
        add("bg",bg);


        std::stringstream test;
        test << "\"Random\"";
        std::string xbox(test.str());
        xbox.erase(std::remove(xbox.begin(), xbox.end(), '\"'), xbox.end());
        cout << test.str() << endl;
        cout << xbox;


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

        defaultCamera.lookAt(400,300);

        myApp->setClearColor(8,31,70,255);

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
            if(myAudioManager->playing("bgmusic")) {
                myAudioManager->pause("bgmusic");
            } else {
                myAudioManager->play("bgmusic");
            }
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
        ossfps << "\nClick to pause/resume";
//        ossfps << "\n\n" << myAudioManager->getSamples("bgmusic")[int(it*myAudioManager->getSlider("bgmusic"))];
        HUDText.text(ossfps.str());
        flush(ossfps);

        //int j = 0;

		for(unsigned i=0; i<800; i++) {
			int p = myAudioManager->getSlider("bgmusic") * microSampleRate;
			unsigned h = ((bgmSamples[p+i] * 600) / 66000)+300;
			//unsigned k = ((bgmSamples[p+i] * 200) / 66000)+800;
			if(h<600) {
				eq[i].moveTo(i, h);
				eq4[i].setY(h);
            }
            //if(i%200) {
              //  if(j<4) {

                //    j=j+1;
                //}
            //}
		}

        if(key_left) {
        }

        if(key_right) {
        }

        if(key_up) {
        }

        if(key_down) {
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

    ~base_scene() {
    }


private:
    Trivial::GUIText HUDText;

    array<Trivial::Sprite, 800> eq;

    array<Trivial::Sprite, 800> eq4;

    Trivial::Sprite bg;

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

    int it;
    float microSampleRate;

    const Int16* bgmSamples;

};

#endif // FLMD_SPLASH_H_INCLUDED
