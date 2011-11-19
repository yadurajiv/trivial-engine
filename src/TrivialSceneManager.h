#ifndef TRIVIALSCENEMANAGER_H_INCLUDED
#define TRIVIALSCENEMANAGER_H_INCLUDED

#include <string>
#include <map>

#include "TrivialObject.h"
#include "TrivialScene.h"

using namespace std;

namespace Trivial {


class SceneManager : public Object {

public:
    static SceneManager* Instance();

    bool addScene(const string &sceneName, Scene* scene, bool keepPersistent = false, bool forceInit = false);
    bool setActiveScene(const string &sceneName);
    bool removeScene(const string &sceneName);
    Scene* getScene(const string &name);

    Scene* getActiveScene();

    void update();

private:
    SceneManager();  // Private so that it can  not be called
    ~SceneManager();

    SceneManager(SceneManager const&){};             // copy constructor is private
    SceneManager& operator=(SceneManager const&){};  // assignment operator is private
    static SceneManager* _pInstance;

    string _currentScene;

    map<string, Scene*> _scenes;
};


}

#endif // TRIVIALSCENEMANAGER_H_INCLUDED
