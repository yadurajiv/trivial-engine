#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include "TrivialEngine.h"

/** game scenes here! **/
#include "src/flmd_splash.h"

/** scenes **/

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

    Trivial::App *myApp = Trivial::App::Instance();
    Trivial::SceneManager *mySceneManager = Trivial::SceneManager::Instance();

    /* add scene to scene manager */
   mySceneManager->addScene("flmd_splash", new flmd_splash, true);

    /* tell the event manager which the current active scene is */
    mySceneManager->setActiveScene("flmd_splash");

    /* configure your app, get it ready */
    myApp->configure(NULL, 800, 600, 32, "FLMD");
    /* run it! */
    myApp->run();

    return 0;
}
