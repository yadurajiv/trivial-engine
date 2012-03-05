#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include "TrivialEngine.h"

/** game scenes here! **/
#include "myScene.h"

#ifdef WIN32
    #ifndef _CONSOLE
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    #else
        int main(int argc, char *argv[])
    #endif
#else
    int main(int argc, char *argv[])
#endif
{

    /**
        moved to main since sfml has its own global variables and they might
        not be initialized before main, which causes a segfault.
        http://www.sfml-dev.org/forum/viewtopic.php?p=29824#29824
    **/
    Trivial::App *myApp = Trivial::App::Instance();
    Trivial::SceneManager *mySceneManager = Trivial::SceneManager::Instance();

    /* add scene to scene manager */
   mySceneManager->addScene("myScene", new myScene, true);

    /* tell the event manager which the current active scene is */
    mySceneManager->setActiveScene("myScene");


    /* configure your app, get it ready */
    myApp->configure(NULL, 800, 600, 32, "myApp");
    /* run it! */
    myApp->run();

    return 0;
}
