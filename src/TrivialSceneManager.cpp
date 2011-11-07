#include <iostream>

#include "TrivialSceneManager.h"

namespace Trivial {


SceneManager* SceneManager::_pInstance;

SceneManager::SceneManager() {
    _currentScene = "";
}

SceneManager::~SceneManager() {
    /** safely removing objects from scene **/
    map<string, Scene*>::iterator it;
    for ( it=_scenes.begin() ; it != _scenes.end(); it++ ) {
        delete (*it).second;
    }
}

SceneManager* SceneManager::Instance() {
   if (!_pInstance)   // Only allow one instance of class to be generated.
      _pInstance = new SceneManager;

   return _pInstance;
}

void SceneManager::update() {
    if (_currentScene != "")
        _scenes[_currentScene]->_update();
}

bool SceneManager::addScene(const string &sceneName, Scene* scene, bool keepPersistent, bool forceInit) {
    if(_scenes.count(sceneName) > 0) {
        std::cout << "\nERROR: Scene Already added!\n";
        return false;
    }

    scene->setPersistance(keepPersistent);

    _scenes[sceneName] = scene;

    if(forceInit) {
        scene->_init();
    } else {
        //scene->setReady(false);
    }

    return true;
}

bool SceneManager::setActiveScene(const string &sceneName) {
    if(_scenes.count(sceneName) == 0) {
        std::cout << "\nERROR: Scene not found! Continuing with currently active scene.\n";
        return false;
    }

    if (_currentScene != "") {
        _scenes[_currentScene]->setActive(false);
        _scenes[_currentScene]->deactivated();
    }

    if(!_scenes[sceneName]->ready()) { // if the scene has not been inited before, then init it
        _scenes[sceneName]->_init();
    } else if(!_scenes[sceneName]->getPersistance()) { // if the scene is persistant then don't reinit
        _scenes[sceneName]->_init();
    }

    _currentScene = sceneName;

    _scenes[_currentScene]->setActive(true);
    _scenes[_currentScene]->activated();

    return true;
}

bool SceneManager::removeScene(const string &sceneName) {
    if(_scenes.count(sceneName) == 0)
        return false;

    map<string, Scene*>::iterator it = _scenes.find(sceneName);
    if (it != _scenes.end())
    {
        _scenes.erase(it);
        return true;
    }

    return false;
}

Scene* SceneManager::getScene(const string &name) {
    if(_scenes.count(name) == 0) {
        cout << "\nERROR: " << name << " was not found in the scene list\n";
        return NULL;
    }

    return _scenes[name];
}

}
