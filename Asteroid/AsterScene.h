
#ifndef MYSCENE_H_INCLUDED
#define MYSCENE_H_INCLUDED
#define pi 360
#define ARRAY_SIZE 30

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include <math.h>

#include "TrivialEngine.h"

#include "pause.h"
//#include "mouseDrawing.h"
// #include "quadTreeTest.h"


using namespace std;

class AsterScene : public Trivial::Scene {
public:

    AsterScene() {
        x = 400;i =0;
        y = 300;
        fx = 400;
        fy = 300;
    }

    void preload() {
        cout << "ONE TIME PRELOAD!\n";

        myApp = Trivial::App::Instance();
        mySceneManager = Trivial::SceneManager::Instance();
        myEventManager = Trivial::EventManager::Instance();
        myImageManager = Trivial::ImageManager::Instance();
        myFontManager = Trivial::FontManager::Instance();
//        myAudioManager = Trivial::AudioManager::Instance();

        // subscribing to keyboard events
        myEventManager->subscribe("w-keydown", this);
        myEventManager->subscribe("w-keyup", this);

        myEventManager->subscribe("s-keydown", this);
        myEventManager->subscribe("s-keyup", this);

        myEventManager->subscribe("a-keydown", this);
        myEventManager->subscribe("a-keyup", this);

        myEventManager->subscribe("d-keydown", this);
        myEventManager->subscribe("d-keyup", this);

        myEventManager->subscribe("escape-keydown", this);
        myEventManager->subscribe("escape-keyup", this);

        // General Mouse event test
        myEventManager->subscribe("update-mouse",this);

        // One time button stuff
        myEventManager->subscribe("buttondown-mouse", this);
        myEventManager->subscribe("buttonup-mouse", this);

        // scroll!
      //  myEventManager->subscribe("scroll-mouse", this);

        // Test for sub sub event functionality. Shiz's gettin trippy bro...
        myEventManager->subscribe("left-buttondown-mouse", this);
        myEventManager->subscribe("left-buttonup-mouse", this);
        myEventManager->subscribe("right-buttonup-mouse", this);
        myEventManager->subscribe("right-buttondown-mouse", this);

        //
        // // Just for lulz
        // myEventManager->subscribe("foo-bar-okey-middle-buttondown-mouse", this);


        /* add a couple of images to the image manager */

        cout << "Loading tank >> " << myImageManager->add("tankImage","data/tank.png") << "\n";

       // cout << "Loading starfield>> " << myImageManager->add("starfield","data/starfield.jpg") << "\n";
        cout << "Loading asteroid>> " << myImageManager->add("asteroid","data/asteroid.png") << "\n";
        cout << "Loading fire >> " << myImageManager->add("fireImage","data/fire.png") << "\n";

        cout << "Loading Spitesheet explosion.png >> " << myImageManager->add("explosion","data/explosion.png") << "\n";

        /** adding explosion **/
        // add the image to the sprite, pass in single cell width and height
        //explosion.image("explosion",64,64);
        // add animation, name, start frame, end frame, framerate
        //explosion.addAnimation("boom",0,24,24);
        // play is set to false by default so play!
      //  explosion.play("boom");
        // regular stuff
        //explosion.moveTo(300,300);
      //  cout << "\nadding explosion - " << add("explosion", explosion);

        tankSprite.image("tankImage");
        tankSprite.moveTo(x,y);
        add("tank", tankSprite);



    }

    void reset() {
        /* key state flags */
        key_up = false;
        key_down = false;
        key_left = false;
        key_right = false;
        key_escape = false;

        _mscroll = 0;



        // look at object needs to be rewritten or given to scene
        defaultCamera.lookAt(400,300);

        myApp->setClearColor();

////        myAudioManager->earPosition(camera.getCenterX(), camera.getCenterY());
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

        if (e.eventName == "w-keydown") {
            key_up = true;
        }
        if (e.eventName == "w-keyup") {
            key_up = false;
        }

        if (e.eventName == "s-keydown") {
            key_down = true;
        }
        if (e.eventName == "s-keyup") {
            key_down = false;
        }

        if (e.eventName == "a-keydown") {
            key_left = true;
        }
        if (e.eventName == "a-keyup") {
            key_left = false;
        }

        if (e.eventName == "d-keydown") {
            key_right = true;
        }
        if (e.eventName == "d-keyup") {
            key_right = false;
        }

        if (e.eventName == "escape-keydown" && _activated) {
            key_escape = true;
        }

        if (e.eventName == "escape-keyup" && _activated) {
            key_escape = false;
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
            mx = e.pos.x;
            my = e.pos.y;

            screenPositionX = e.screenPosition.x;
            screenPositionY = e.screenPosition.y;

        /*Rotation of tank on mouse update */
            dx = mx - x;
            dy = y - my;
            rot1 = atan2(dx , dy);
            rot = rot1 * 57.29;
            tankSprite.rotate(rot);

            if(e.lButton) {


               // fireSprite.setVelocity(dist_x[i], dist_y);
            }

            if(e.rButton) {
                cout << "\nRight Button is Down!";
            }
        }

       // if (e.eventName == "scroll-mouse") {
         //   cout << "\nDead Sea Scrolls! - " << 100 * (1 - float(e.scroll)/2);
          //  defaultCamera.setZoom(100 * (1 - float(e.scroll)/2));
        //}

        if (e.eventName == "buttondown-mouse") {
            // This is when the mouse button goes down. This is called once
            // for that button. Motivation behind this was so I get an event
            // only for the click. The mouse event struct will anyway have
            // all the details about the mouse position etc.
          //  cout << "\nSup mawn";
        }

        if (e.eventName == "buttonup-mouse") {
            // Same as the button down
            //cout << "\nBai mawn";
        }

        if (e.eventName == "left-buttondown-mouse") {
            cout << "\nLeft button down lol ";
            i++;

                cout<<"ayesss"<<i;
                cout << "\nLeft Button is Down!";
                dist_x[i] = 250 * sin(rot1);
                //cout<<"aaaaa"<<dist_x[i];
                dist_y[i] = -250 * cos(rot1);
                stringstream s1;
                s1<<"fire"<<i;
                fireSprite[i].image("fireImage");
                fireSprite[i].moveTo(x,y);
                add(s1.str().c_str(), fireSprite[i]);
                if(i >=30){
                    i =0;
                }


        }

        if (e.eventName == "left-buttonup-mouse") {
            //cout << "\nLeft button up lol - SHAKE!!";
            //defaultCamera.shake();


        }

        if (e.eventName == "right-buttondown-mouse") {
            //cout << "\nRight button down lol ";

        }

        if (e.eventName == "right-buttonup-mouse") {
           // cout << "\nRight button up lol ";

        }

        fflush(stdout);
    }

    void update() {

        if(!_activated)
            return;

        // cout << "\nMAISCENE cam x " << defaultCamera.X()

        //float mcx = testSprite.X();
        //float mcy = testSprite.Y();

        float ft = myApp->frameTime()/1000;


        if(key_left) {
           // mcx = mcx - 60 * ft;
           x = x - 60 * ft;
            tankSprite.moveTo(x,y);


        }

        if(key_right) {
            //mcx = mcx + 60 * ft;

             x = x + 100 * ft;
              tankSprite.moveTo(x,y);

        }

        if(key_up) {
            //mcy = mcy - 60 * ft;
             y = y - 60 * ft;
              tankSprite.moveTo(x,y);
        }

        if(key_down) {
            //mcy = mcy + 60 * ft;
              y = y + 100 * ft;
              tankSprite.moveTo(x,y);
        }

        if(key_escape) {
            key_escape = false;
            mySceneManager->addScene("pause", new pauseScene);
            mySceneManager->setActiveScene("pause");
        }

        for(int y1=0;y1<=30;y1++){
            if(fireSprite[y1].Y() > 0) {
            //out <<"1111"<<i;
                fireSprite[y1].setVelocity(dist_x[y1],dist_y[y1]);
            }
        }

        rx = rand() % (100 );
        cout<< "dddddddddddddddddddddddd"<<rx;

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

        reset();
    }

    ~AsterScene() {
    }


private:
    Trivial::Sprite tankSprite;
    Trivial::Sprite starfield;
    Trivial::Sprite child;
    Trivial::Sprite fireSprite[30];
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

    int _mx;
    int _my;

    int ax;
    int amx;
    int rx;
    int ay;
    int amy;
    int ry;
    int i;
    int x;
    int y;
    int mx;
    int my;
    float dx;
    float dy;
    float rot;
    float rot1;
    float fx;
    float  fy;
    float dist_x[30];
    float dist_y[30];
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
    //Trivial::AudioManager *myAudioManager;

};

#endif // MYSCENE_H_INCLUDED
