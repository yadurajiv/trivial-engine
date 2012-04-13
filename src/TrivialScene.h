#ifndef TRIVIALSCENE_H_INCLUDED
#define TRIVIALSCENE_H_INCLUDED

#include <map>
#include <list>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

#include <SFML/Graphics.hpp>

// Box2D for removal
// #include "TrivialBox2D.h"
#include "TrivialSceneObject.h"
#include "TrivialCamera.h"

using namespace std;

namespace Trivial {

class Scene : public GraphicsObject {

public:
    Scene(): _defaultCameraZoom(1), _doZoom(false), _cellSize(128) { };
    ~Scene();

    virtual void update() {};

    void _update();

    //virtual void init() = 0;

    //void _init();

    virtual void deactivated() {};
    virtual void activated() {};

    virtual void preload() {};

    void _preload();

    void _reset() {
        defaultCamera.reset();
    }

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

    float width() const { return Trivial::App::Instance()->width(); };
    float height() const { return Trivial::App::Instance()->height(); };

    bool getPersistance() const { return _keepPersistent; }
    void setPersistance(bool p) { _keepPersistent = p; }

    void setCellSize(const unsigned int& size = 128) {
        _cellSize = size;
    }

    unsigned int getCellSize() const {
        return _cellSize;
    }

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

protected:
    string _name;

    std::map<string, SceneObject*> _objects;

    std::map<string, sf::View *> _layers;

    std::map<int, string> _layerIndexes;

    std::map<string, pair<float, float> > _cameraDamps;

    unsigned int _cellSize;

    //Camera* _camera;

    float _cameraMoveX;
    float _cameraMoveY;
    float _cameraSpeed;
    float _cameraAngle;

    bool _keepPersistent;
    //bool _hasInited;
   // int _forceInit;

    Camera defaultCamera;
    float _defaultCameraZoom;
    bool _doZoom;

    ostringstream _sink;

    friend class SceneManager;
};

}

#endif // TRIVIALSCENE_H_INCLUDED
