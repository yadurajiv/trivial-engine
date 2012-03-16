
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
#include "asteroids.h"
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

        //Adding image resources
        myImageManager->add("tankImage","data/tank.png");
        myImageManager->add("asteroid","data/asteroid.png");
        myImageManager->add("fireImage","data/fire.png");
        myImageManager->add("explosion","data/explosion.png");

        //Loading tank Image
        tankSprite.image("tankImage");
        tankSprite.moveTo(x,y);
        add("tank", tankSprite);

        //Loading Ansteroid Image
        for(int n=0;n<20;n++){

           // cout<<"hdasjdsjahdjkasdkjsahjkdhasjk";
            stringstream s2;
            s2<<"ast"<<n;
            astSprite[n].image("asteroid", n%4);
            add(s2.str().c_str(), astSprite[n]);
        }
     //
    }

    void reset() {

        /* key state flags */
        key_up = false;
        key_down = false;
        key_left = false;
        key_right = false;
        key_escape = false;

        // look at object needs to be rewritten or given to scene
        defaultCamera.lookAt(400,300);

        myApp->setClearColor();
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

            }

            if(e.rButton) {

            }
        }

        if (e.eventName == "buttondown-mouse") {

        }

        if (e.eventName == "buttonup-mouse") {

        }

        if (e.eventName == "left-buttondown-mouse") {

                cout << "\nLeft button down lol ";
                i++;
                cout<<"ayesss"<<i;
                cout << "\nLeft Button is Down!";
                dist_x[i] = 300 * sin(rot1);
                //cout<<"aaaaa"<<dist_x[i];
                dist_y[i] = -300 * cos(rot1);
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

        //Adding movements to tank
        if(key_left) {

            x = x - 60 * ft;
            tankSprite.moveTo(x,y);
        }

        if(key_right) {

             x = x + 100 * ft;
             tankSprite.moveTo(x,y);
        }

        if(key_up) {

             y = y - 60 * ft;
            tankSprite.moveTo(x,y);
        }

        if(key_down) {

              y = y + 100 * ft;
              tankSprite.moveTo(x,y);
        }

        if(key_escape) {
            key_escape = false;
            mySceneManager->addScene("pause", new pauseScene);
            mySceneManager->setActiveScene("pause");
        }

        //For loop for bullet
            //For loop for astSprite

        for(int y1=0;y1<30;y1++){
            for(int x1=0; x1<20; x1++)
            {
                if(astSprite[x1].pointOverlap(fireSprite[y1].X(), fireSprite[y1].Y(), true))
                {
                    astSprite[x1].setIsActive(false);
                }
            }
            if(fireSprite[y1].Y() > 0) {

                fireSprite[y1].setVelocity(dist_x[y1],dist_y[y1]);

            }
        }

        /*for(int a1=0;a1<10;a1++){

            if(astSprite[a1].X() > 0) {

                astSprite[a1].setVelocity(dist_ax[a1],dist_ay[a1]);
            }
        }*/

    }

    void deactivated() {
        _activated = false;
    }

    void activated() {
        _activated = true;
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
    asteroids astSprite[20];

    bool childSmallCol;

    float _lastTime;

    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;
    bool key_escape;

    int _mx;
    int _my;
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
    int n;
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
