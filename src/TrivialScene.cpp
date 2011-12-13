#include <stdio.h>
#include <iostream>

#include <typeinfo>

#include "TrivialScene.h"
#include "TrivialApp.h"

namespace Trivial {

Scene::~Scene() {

    /** safely removing objects from scene **/
    map<string, SceneObject*>::iterator it;
    for ( it=_objects.begin() ; it != _objects.end(); it++ ) {
        delete (*it).second;
    }
}

void Scene::_update() {
    // Box2D for removal
    /*
    if (_hasBox2DPhysics) {
        _world->_update();
    }
    */

    // updating default camera; replaced later with a list of active cameras
    defaultCamera._update();

    _cameraMoveX = defaultCamera.X();
    _cameraMoveY = defaultCamera.Y();

    // if there is a change in the zoom factor then get the new zoom factor
    if(_defaultCameraZoom != defaultCamera.getZoomFactor()) {
        _defaultCameraZoom = defaultCamera.getZoomFactor();
        _doZoom = true;
    }

    map<int, string>::iterator it;

    for ( it=_layerIndexes.begin() ; it != _layerIndexes.end(); it++ ) {
        float moveFactorX = (_cameraMoveX * _cameraDamps[it->second].first) + width()/2;
        float moveFactorY = (_cameraMoveY * _cameraDamps[it->second].second) + height()/2;
        _layers[it->second]->SetCenter(moveFactorX,moveFactorY);

        // zoom can be a factor for each layer, but ignored here
        // zoom layers which has no damping!(eg. Hud dam x and y are 0)
        if(_doZoom && (_cameraDamps[it->second].first != 0 && _cameraDamps[it->second].second !=0)) {
            // reset view to 100% otherwise, your zoom is going to be relative!
            _layers[it->second]->SetSize(width(),height());
            _layers[it->second]->Zoom(_defaultCameraZoom);
        }

        App::Instance()->renderView(*(_layers[it->second]));

        updateObjectsByLayerName(it->second);
    }

    // if we zoomed then not again.
    _doZoom = false;

    update();
}

void Scene::updateObjectsByLayerName(const string &layerName) {
    map<string, SceneObject*>::iterator it;

    for ( it=_objects.begin() ; it != _objects.end(); it++ ) {
        if (it->second->getLayer() == layerName) {
            it->second->_update();

            // Box2D for removal
            /*
            if (_hasBox2DPhysics && it->second->getPhysicsObject()->hasInit()) {
                it->second->_updatePhysics();
            }
            */
        }
    }

}

void Scene::_init() {
    // Box2D for removal
    // _hasBox2DPhysics = false;
    addLayer("default", 0);

    defaultCamera.init(Trivial::App::Instance()->GetWidth(),Trivial::App::Instance()->GetHeight());

    _cameraMoveX = 0;
    _cameraMoveY = 0;

    init();
    _hasInited = true;
}

void Scene::moveLayers(const float &x, const float &y) {
    _cameraMoveX = x;
    _cameraMoveY = y;
}

void Scene::setLayerPosition(const string &name, const float &x, const float &y) {
    //_layers[name]->Set
}

/*void Scene::setCamera(Camera& camera) {
    _camera = &camera;
    //_camera->setScene(this);
}*/

bool Scene::setLayerCameraDamp(const string &name, const float &xFactor, const float &yFactor) {
    // If layer not found, return
    if (_layers.count(name) == 0) {
        return false;
    }

    _cameraDamps[name] = make_pair(xFactor,yFactor);

    return true;
}


bool Scene::add(const string &objectName,  SceneObject &object, const string &layer) {
    // If an object with this name already exisits, return
    if(_objects.count(objectName) > 0) {
        return false;
    }

    // If layer not found, return
    if (_layers.count(layer) == 0) {
        return false;
    }
    // Box2D for removal
    /*
    if (_hasBox2DPhysics) {

        if (object.getPhysicsObject()->hasInit()) {
            _world->add(object.getPhysicsObject());
        }
    }
    */

    object.setLayer(layer);
    object.setName(objectName);

    _objects[objectName] = &object;

    return true;
}

bool Scene::remove(const string &objectName) {
    if(_objects.count(objectName) == 0)
        return false;

    map<string, SceneObject*>::iterator it = _objects.find(objectName);
    if (it != _objects.end())
    {
        _objects.erase(it);
        return true;
    }

    return false;

}

bool Scene::addLayer(const string &name, const int &index) {
   // If a layer with this name already exisits, return
    if(_layers.count(name) > 0) {
        return false;
    }

    // layer index already exists
    if(_layerIndexes.count(index) > 0) {
        std::cout << "\nERROR: Layer \'" << _layerIndexes[index] << "\' uses this index. Cannot have two layers with the same index.";
        return false;
    }

    _layers[name] = new sf::View(App::Instance()->getWindowRect());
    _layerIndexes[index] = name;
    setLayerCameraDamp(name,1,1);

    return true;
}

bool Scene::removeLayer(const string &name) {
    if(_layers.count(name) == 0)
        return false;

    map<string, sf::View*>::iterator it = _layers.find(name);
    if (it != _layers.end())
    {
        _layers.erase(it);
    } else {
        // throw error
    }

    map<int, string>::iterator indexit;
    for ( indexit=_layerIndexes.begin() ; indexit != _layerIndexes.end(); indexit++ ) {
        if(indexit->second == name) {
            _layerIndexes.erase(indexit);
            break;
        } else {
            // T_T this should not happen!
            // assert some shit nao!!
        }
    }

    return true;
}

}

