#ifndef MYSCENE_H_INCLUDED
#define MYSCENE_H_INCLUDED

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include "TrivialEngine.h"

using namespace std;

class myScene : public Trivial::Scene {
public:

    myScene() {

    }

    void init() {

        cout << "myScene init()\n";

        myApp = Trivial::App::Instance();
        mySceneManager = Trivial::SceneManager::Instance();
        myEventManager = Trivial::EventManager::Instance();
        myImageManager = Trivial::ImageManager::Instance();
        myFontManager = Trivial::FontManager::Instance();
//        myAudioManager = Trivial::AudioManager::Instance();

        //enableBox2DPhysics();

        /* key state flags */
        key_up = false;
        key_down = false;
        key_left = false;
        key_right = false;
        key_escape = false;
        key_z = false;

        _mscroll = 0;

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

        myEventManager->subscribe("z-keydown", this);
        myEventManager->subscribe("z-keyup", this);

        myEventManager->subscribe("x-keydown", this);
        myEventManager->subscribe("x-keyup", this);

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

        //
        // // Just for lulz
        // myEventManager->subscribe("foo-bar-okey-middle-buttondown-mouse", this);


        /* add a couple of images to the image manager */

        cout << "Loading testImage.jpg >> " << myImageManager->add("testImage","data/testImage.jpg") << "\n";

        cout << "Loading starfield.jpg >> " << myImageManager->add("starfield","data/starfield.jpg") << "\n";
        cout << "Loading child.png >> " << myImageManager->add("child","data/child.png") << "\n";
        cout << "Loading childSmall.png >> " << myImageManager->add("childSmall","data/childSmall.png") << "\n";

        cout << "Loading Spitesheet explosion.png >> " << myImageManager->add("explosion","data/explosion.png") << "\n";

        /* loading a font */
        cout << "Loading a font! >> " << myFontManager->add("wendy","data/WENDY.TTF") << "\n";
        cout << "Loading a font! >> " << myFontManager->add("dejavu","data/DEJAVUSANS.TTF") << "\n";

/*
        cout << "Initializing Audio!\n";
        myAudioManager->setVolume(50); // set the volume to 50
        cout << "Done!\n";
*/

        // Sound still has issues, look in the TrivialAudio class
        /*
        cout << "Loading music file >> ";
        myAudioManager->add("bgmusic","data/maenamMono.ogg", true); // Spatialization only works on mono sounds!!
        myAudioManager->setSoundPosition("bgmusic",300,300); // positioned with the explosion sprite
        myAudioManager->setSoundAttenuation("bgmusic",10); // fall off
        myAudioManager->setSoundDistance("bgmusic",100); // minimum distance till the sound is heard
        cout << myAudioManager->play("bgmusic") << "\n"; // play loaded music
        */

        /** adding explosion **/
        // add the image to the sprite, pass in single cell width and height
        explosion.image("explosion",64,64);
        // add animation, name, start frame, end frame, framerate
        explosion.addAnimation("boom",0,24,24);
        // play is set to false by default so play!
        explosion.play("boom");
        // regular stuff
        explosion.moveTo(300,300);
        add("explosion", explosion);

        child.image("child");
        child.moveBy(50,50);

        /* add the image to the sprite */
        testSprite.image("testImage");
        /* move the sprite to xy(0,0) */
        testSprite.moveTo(0,0);

        cout << "adding child object to testSprite >> " << testSprite.add("xchild", child) << endl;
/*
        testSprite.setAngularAcceleration(10);
        testSprite.setVelocity(60,0);
        testSprite.setMaxVelocity(100,0);
        testSprite.setMaxAngular(100);
*/
        //testSprite.getPhysicsObject()->setBoxShape(testSprite.X(), testSprite.Y(), testSprite.width(), testSprite.height());
        //testSprite.getPhysicsObject()->setDynamic();

        /* add the sprite to the scene */
        add("atestImage", testSprite);

        childSmall.image("childSmall");
        childSmall.moveTo(100,400);
        childSmall.setAngularAcceleration(120);
        childSmall.setVelocity(0,120);
        childSmall.setMaxVelocity(0,200);
        childSmall.setMaxAngular(100);
        add("xchildSmall",childSmall);


        /* adding text - removed since GUI Text was removed */
        msg.font("wendy");
        msg.text(400,400,"woah!\nTrivial Engine is Trivial.");
        add("msg",msg);

        addLayer("hud", 1);

        HUDText.font("wendy");
        HUDText.text(10,5,"FPS: 000");
        add("hudtext", HUDText, "hud");

        moreText.font("dejavu");
        moreText.text(400,450,"some more text in another font bleh ~_~");
        add("moreText", moreText);
        moreText.rotate(40);

        /* add a new layer to the scene with a lower zindex than the "default" layer */
        addLayer("bgLayer", -1);

        /* add a sprite to another */
        starfield.image("starfield");
        /* add the starfield to the new layer */
        add("starfield", starfield,"bgLayer");

        /* set a lag for the bgLayer if the camera where to move */
        setLayerCameraDamp("bgLayer", 0.5, 0.5);
        setLayerCameraDamp("hud", 0, 0);

        // look at object needs to be rewritten or given to scene
        defaultCamera.lookAt(300, 300);

        cout << "\ndefCamX: " << defaultCamera.width();
        cout << "\ndefCamY: " << defaultCamera.height();


//        myAudioManager->earPosition(camera.getCenterX(), camera.getCenterY());

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

    }

    void mouseEventCallBack(const Trivial::TrivialMouseEvent &e) {

        if(!_activated)
            return;

        if(e.eventName == "update-mouse") {
            // Test for the general mouse update. This is an event in case any
            // aspect of the mouse changes.
            _mx = e.pos.x;
            _my = e.pos.y;

            screenPositionX = e.screenPosition.x;
            screenPositionY = e.screenPosition.y;

            if(e.lButton) {
                cout << "\nLeft Button is Down!";
            }

            if(e.rButton) {
                cout << "\nRight Button is Down!";
            }

            if(e.mButton) {
                cout << "\nMiddle Button is Down!";
            }

            if(e.x1Button) {
                cout << "\nX1 Button is Down!";
            }

            if(e.x2Button) {
                cout << "\nX2 Button is Down!";
            }
        }

        if (e.eventName == "scroll-mouse") {
            cout << "\nDead Sea Scrolls! - " << 100 * (1 - float(e.scroll)/2);
            defaultCamera.setZoom(100 * (1 - float(e.scroll)/2));
        }

        if (e.eventName == "buttondown-mouse") {
            // This is when the mouse button goes down. This is called once
            // for that button. Motivation behind this was so I get an event
            // only for the click. The mouse event struct will anyway have
            // all the details about the mouse position etc.
            cout << "\nSup mawn";
        }

        if (e.eventName == "buttonup-mouse") {
            // Same as the button down
            cout << "\nBai mawn";
        }

        if (e.eventName == "left-buttondown-mouse") {
            cout << "\nLeft button down lol ";

        }

        if (e.eventName == "left-buttonup-mouse") {
            cout << "\nLeft button up lol - SHAKE!!";
            defaultCamera.shake();

        }

        if (e.eventName == "middle-buttondown-mouse") {
            cout << "\nMiddle button down lol ";

        }

        if (e.eventName == "middle-buttonup-mouse") {
            cout << "\nMiddle button up lol ";
            defaultCamera.setZoom();

        }

        if (e.eventName == "right-buttondown-mouse") {
            cout << "\nRight button down lol ";

        }

        if (e.eventName == "right-buttonup-mouse") {
            cout << "\nRight button up lol ";

        }

        fflush(stdout);
    }

    void update() {

        if(!_activated)
            return;


        float mcx = defaultCamera.X();
        float mcy = defaultCamera.Y();

        //float mcx = testSprite.X();
        //float mcy = testSprite.Y();

        float ft = myApp->frameTime()/1000;

        ossfps.str("");
        ossfps << "FPS: " << myApp->FPS();
        ossfps << "\n";
        ossfps << "Cam X: " << floor(mcx) << "  Cam Y: " << floor(mcy);
        ossfps << "\n";
        ossfps << "Cam Center-X: " << floor(defaultCamera.getCenterX()) << "  Cam Center-Y: " << floor(defaultCamera.getCenterY());
        ossfps << "\nEscape key to pause, space to continue";
        ossfps << "\nsmallChild.overlaps(testSprite) is " << (childSmallCol?"True":"False");
        ossfps << "\nEscape key to pause, space to continue\nZ key to fade and stop music! (5 seconds)\nX key to fade in and start music! (5 seconds)";
        ossfps << "\nMouse X: " << _mx;
        ossfps << "\nMouse Y: " << _my;
        ossfps << "\nScreen X: " << screenPositionX;
        ossfps << "\nScreen Y: " << screenPositionY;
        ossfps << "\nZoom : " << defaultCamera.getZoom();
        HUDText.text(ossfps.str());
        flush(ossfps);

        if(key_left) {
            mcx = mcx - 60 * ft;
        }

        if(key_right) {
            mcx = mcx + 60 * ft;
        }

        if(key_up) {
            mcy = mcy - 60 * ft;
        }

        if(key_down) {
            mcy = mcy + 60 * ft;
        }

        if(key_escape) {
            key_escape = false;
            mySceneManager->setActiveScene("pause");
        }

        if(key_up || key_down || key_left || key_right) {
            defaultCamera.moveTo(mcx, mcy);
            //testSprite.moveTo(mcx,mcy);
//            myAudioManager->earPosition(defaultCamera.getCenterX(), defaultCamera.getCenterY());
        }


        if(key_z) {
            key_z = false;
            std::cout << "\nz key pressed - Audio code commented out";
            /*
            if(myAudioManager->playing("bgmusic")) {
                std::cout << "\nsound is playing, trying to fadeOut in 5000ms";
                myAudioManager->fadeOut("bgmusic",5000);
            }
            */
        }

        if(key_x) {
            key_x = false;
            std::cout << "\nx key pressed - Audio code commented out";
            /*
            if(myAudioManager->playing("bgmusic") == false) {
                std::cout << "\nsound is *NOT* playing, trying to fadeIn and play in 5000ms";
                myAudioManager->fadeIn("bgmusic",5000);
            }
            */
        }

/*
        if(testSprite.X() > 500) {
            testSprite.setVelocity(-40,0);
        }

        if(testSprite.X() < 0) {
            testSprite.setVelocity(40,0);
        }
*/
        if(childSmall.Y() > 500) {
            childSmall.setVelocity(0,-120);
        }

        if(childSmall.Y() < 0) {
            childSmall.setVelocity(0,120);
        }

        if(childSmall.overlaps(testSprite)) {
            childSmallCol = true;
        } else {
            childSmallCol = false;
        }

        if (explosion.pointOverlap(_mx,_my)) {
            explosion.setColor(100,12,10,255);
        } else {
            //explosion.setAlpha();
            explosion.setColor(255,255,255,255);
        }

    }

    void deactivated() {
        _activated = false;
        cout << "\nmyScene deactivated" << endl;
    }

    void activated() {
        _activated = true;
        cout << "\nmyScene activated!" << endl;
    }

    ~myScene() {
    }


private:
    Trivial::Sprite testSprite;
    Trivial::Sprite starfield;
    Trivial::Sprite child;
    Trivial::Sprite childSmall;
    Trivial::AnimatedSprite explosion;
    Trivial::GUIText msg;
    Trivial::GUIText HUDText;
    Trivial::GUIText moreText;

    bool childSmallCol;

    float _lastTime;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool key_escape;
    bool key_z;
    bool key_x;

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
//    Trivial::AudioManager *myAudioManager;

};

#endif // MYSCENE_H_INCLUDED
