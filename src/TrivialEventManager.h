#ifndef TRIVIALEVENTMANAGER_H_INCLUDED
#define TRIVIALEVENTMANAGER_H_INCLUDED

#include <map>
#include <vector>
#include <utility>

#include "SFML/Window.hpp"
// Box2D for removal
// #include <Box2D/Box2D.h>

#include "TrivialObject.h"
#include "TrivialSceneManager.h"

using namespace std;
using namespace sf;

namespace Trivial {

// Box2D for removal
// class EventManager : public Object, public b2ContactListener {
class EventManager : public Object {
public:
    static EventManager* Instance();

    int subscribe(const string &eventName, Object *o);
    bool unsubscribe(const string &eventName, const int &key);

    void update();

    void releaseResource();

    //class EventManager : public Object, public b2ContactListener {
    // Callbacks for physics
	// void BeginContact(b2Contact* contact);
	// void EndContact(b2Contact* contact);

private:
    EventManager();  // Private so that it can  not be called

    EventManager(EventManager const&){};             // copy constructor is private
    EventManager& operator=(EventManager const&){};  // assignment operator is private

    static EventManager* _pInstance;
    
    pair<string, vector<string> > parseSubEventString(string subEventString);

    // Keyboard events related
    map<pair<string, string>, vector<Object *> > _keyboardEventSubscribers;
    map<string, sf::Keyboard::Key> _keyBoardKeyCodeMap;
    // map<string, sf::Event::EventType> _keyBoardEventMap;
    map<string, int> _keyStates;

    // System events related
    map<pair<string, string>, Object * > _systemEventSubscribers;

    // Mouse events related
    map<pair<string, string>, vector<Object *> > _mouseEventSubscribers;
    map<string, sf::Mouse::Button> _mouseButtonMap;
    // map<string, int> _mouseButtonEventMap;
    // Need to find a better way to do this
    map<string, int> _mouseButtonStatesMain;
    map<string, int> _mouseButtonStatesSub;

    // Not sure what to do with the following for now x-)
    map<string, vector<Object *> > _joystickEventSubscribers;
    map<string, vector<Object *> > _collisionEventSubscribers;
    map<string, vector<Object *> > _customEventSubscribers;

    bool _quitFlag;
};

}


#endif // TRIVIALEVENTMANAGER_H_INCLUDED
