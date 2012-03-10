#ifndef TESTCANVAS_H_INCLUDED
#define TESTCANVAS_H_INCLUDED


using namespace std;

class testCanvas : public Trivial::Scene {
public:

    testCanvas() {

    }

    void preload() {

        myApp = Trivial::App::Instance();
        mySceneManager = Trivial::SceneManager::Instance();
        myEventManager = Trivial::EventManager::Instance();
        myImageManager = Trivial::ImageManager::Instance();
        myFontManager = Trivial::FontManager::Instance();
//        myAudioManager = Trivial::AudioManager::Instance();


        myEventManager->subscribe("escape-keydown", this);
        myEventManager->subscribe("escape-keyup", this);

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

        _canvas.create(640,480);
        add("canvas",_canvas);

        addLayer("hud", 1);
        HUDText.font("wendy");
        HUDText.text(10,5,"FPS: 000");
        HUDText.setColor(255,0,0,255);
        add("hudtext", HUDText, "hud");

        setLayerCameraDamp("hud", 0, 0);

        _canvas.moveBy(100,100);

    }

    void reset() {
        /* key state flags */
        key_escape = false;

        _mscroll = 0;

        Trivial::Helper::makePointRectAroundPoint(&_ptrect,0,0,10,10);

        defaultCamera.lookAt(0,0);

        myApp->setClearColor();

    }

    /* the event call back is called by the event manager */
    void keyBoardEventCallback(const Trivial::TrivialKeyBoardEvent &e) {

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

            screenPositionX = e.screenPosition.x;
            screenPositionY = e.screenPosition.y;

            if(e.lButton) {
                if(_canvas.pointOverlap(_mx,_my)) {
                    _mrad = Trivial::Helper::distance(0,0,_mx,_my);
                    Trivial::Helper::makePointRectAroundPoint(&_ptrect,0,0,_mrad,_mrad);
                    Trivial::Helper::rotatePointRect(&_ptrect,0,0,Trivial::Helper::getAngle(_mx,_my,0,0));
                    _canvas.line(0,0,_mx,_my);
                    _canvas.circle(0,0,_mrad);
                    _canvas.rect(_ptrect);
                }
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

        }

        if (e.eventName == "middle-buttondown-mouse") {
            cout << "\nMiddle button down lol ";

        }

        if (e.eventName == "middle-buttonup-mouse") {

        }

        if (e.eventName == "right-buttondown-mouse") {
            cout << "\nRight button down lol ";

        }

        if (e.eventName == "right-buttonup-mouse") {
            _canvas.setPixel(0,0);

        }

        fflush(stdout);
    }

    void update() {

        if(!_activated)
            return;

        float mcx = defaultCamera.X();
        float mcy = defaultCamera.Y();


       float ft = myApp->frameTime()/1000;

        ossfps.str("");
        ossfps << "FPS: " << myApp->FPS();
        ossfps << "\ncanvasX: " << _canvas.X() << " canvasY: " << _canvas.Y();
        ossfps << "\n_mx: " << _mx << " _my: " << _my;
        ossfps << "\nscrx: " << screenPositionX << " scry: " << screenPositionY;
        ossfps << "\ndx: " << (_mx - (_canvas.X()-_canvas.width()/2)) << " dy: " << (_my- (_canvas.Y()-_canvas.height()/2));
        ossfps << "\nmouse overlap canvas: " << ((_canvas.pointOverlap(_mx,_my))?" True":" False");
        HUDText.text(ossfps.str());
        flush(ossfps);

        if(key_escape) {
            key_escape = false;
            mySceneManager->setActiveScene("myScene");
        }

    }

    void deactivated() {
        _activated = false;
        cout << "\ntestCanvas deactivated" << endl;
    }

    void activated() {
        _activated = true;
        cout << "\ntestCanvas activated!" << endl;

        reset();
    }

    ~testCanvas() {
    }


private:

    Trivial::GUIText HUDText;
    Trivial::Canvas _canvas;

    Trivial::TrivialPointRect _ptrect;

    bool childSmallCol;

    float _lastTime;

    bool key_escape;

    int _mx;
    int _my;

    int _mrad;

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

#endif // TESTCANVAS_H_INCLUDED
