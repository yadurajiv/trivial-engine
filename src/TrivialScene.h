#ifndef TRIVIALSCENE_H_INCLUDED
#define TRIVIALSCENE_H_INCLUDED

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <SFML/Graphics.hpp>

// Box2D for removal
// #include "TrivialBox2D.h"
#include "TrivialSceneObject.h"
#include "TrivialCamera.h"

using namespace std;

namespace Trivial {

class Scene : public GraphicsObject {

public:
    Scene(): _hasInited(false) { };
    ~Scene();

    virtual void update() {};

    void _update();

    virtual void init() = 0;

    void _init();

    virtual void deactivated() {};
    virtual void activated() {};

    bool add(const string &objectName, SceneObject &object, const string &layer="default");

    SceneObject* get(const string &objectName) {
        if(_objects.count(objectName) > 0) {
            return _objects[objectName];
        } else {
            return NULL;
        }
    };
    bool remove(const string &objectName);

    bool addLayer(const string &name, const int &index);
    bool removeLayer(const string &name);

    void updateObjectsByLayerName(const string &layerName);

    void moveLayers(const float &x, const float &y);

    void setLayerPosition(const string &name, const float &x, const float &y);

    bool setLayerCameraDamp(const string &name, const float &xFactor, const float &yFactor);

    float width() const { return Trivial::App::Instance()->GetWidth() /* Width changed to GetWidth */; };
    float height() const { return Trivial::App::Instance()->GetHeight() /* Height changed to GetHeight */; };

    bool getPersistance() const { return _keepPersistent; }
    void setPersistance(bool p) { _keepPersistent = p; }

    Camera* getCamera(const string &name = "default") {
        return &defaultCamera;
        /*
        if(name == "default") {
            return _defaultCamera;
        } else {
            return NULL;
            // ? find the right camera and give it from a camera list
        }
        */
    }

    bool ready() const { return _hasInited; }
    //void setReady(bool b) { _hasInited = b; }
/*
    bool glueLayerToCamera(string name);
    bool unglueLayerFromCamera(string name);*/

    // Box2D for removal
    /*
    void enableBox2DPhysics() {
        _hasBox2DPhysics = true;
        _world = new TrivialBox2DWorld();
        _world->_init();
    };
    void disableBox2DPhysics() { _hasBox2DPhysics = false; };
    */

protected:
    std::map<string, SceneObject*> _objects;

    std::map<string, sf::View *> _layers;

    std::map<int, string> _layerIndexes;

    std::map<string, pair<float, float> > _cameraDamps;

    //Camera* _camera;

    float _cameraMoveX;
    float _cameraMoveY;
    float _cameraSpeed;
    float _cameraAngle;

    bool _keepPersistent;
    bool _hasInited;

    Camera defaultCamera;

    // Box2D for removal
    // bool _hasBox2DPhysics;
    // TrivialBox2DWorld* _world;
};

}

#endif // TRIVIALSCENE_H_INCLUDED
