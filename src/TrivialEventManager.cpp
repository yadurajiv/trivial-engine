#include <stdio.h>
#include <iostream>

#include "SFML/Window.hpp"

#include "TrivialApp.h"
#include "TrivialEventManager.h"

using namespace std;

using namespace sf;

namespace Trivial {

EventManager* EventManager::_pInstance;

EventManager::EventManager() {
    map<string, sf::Keyboard::Key>::iterator keyIt;

    keyBoardKeyCodeMap.insert(make_pair("up", sf::Keyboard::Up));
    keyBoardKeyCodeMap.insert(make_pair("down", sf::Keyboard::Down));
    keyBoardKeyCodeMap.insert(make_pair("left", sf::Keyboard::Left));
    keyBoardKeyCodeMap.insert(make_pair("right", sf::Keyboard::Right));

    keyBoardKeyCodeMap.insert(make_pair("spacebar", sf::Keyboard::Space));
    keyBoardKeyCodeMap.insert(make_pair("escape", sf::Keyboard::Escape));
    keyBoardKeyCodeMap.insert(make_pair("enter", sf::Keyboard::Return));

    keyBoardKeyCodeMap.insert(make_pair("a", sf::Keyboard::A));
    keyBoardKeyCodeMap.insert(make_pair("c", sf::Keyboard::C));
    keyBoardKeyCodeMap.insert(make_pair("d", sf::Keyboard::D));
    keyBoardKeyCodeMap.insert(make_pair("s", sf::Keyboard::S));
    keyBoardKeyCodeMap.insert(make_pair("w", sf::Keyboard::W));
    keyBoardKeyCodeMap.insert(make_pair("x", sf::Keyboard::X));
    keyBoardKeyCodeMap.insert(make_pair("z", sf::Keyboard::Z));

    keyBoardEventMap.insert(make_pair("keydown", sf::Event::KeyPressed));
    keyBoardEventMap.insert(make_pair("keyup", sf::Event::KeyReleased));

    // Set all key states to zero
    for (keyIt = keyBoardKeyCodeMap.begin(); keyIt != keyBoardKeyCodeMap.end(); keyIt++) {
        _keyStates[keyIt->first] = 0;
    }

    _quitFlag = false;
}

EventManager* EventManager::Instance() {
   if (!_pInstance)   // Only allow one instance of class to be generated.
      _pInstance = new EventManager;

   return _pInstance;
}

/** if an event already exists, from the same object, then do not subscribe to it again! **/
int EventManager::subscribe(const string &eventName, Object *o) {
    int returnKey;

    string eventType;
    string eventCode;
    size_t pos;

    pos = eventName.find("-");

    if ((pos + 1) > eventName.size()) {
        cout << "\nERROR: " << eventName << " The supplied event string is invalid.";
        return -1;
    }

    eventType = eventName.substr(pos + 1);   // get from "live" to the end
    eventCode = eventName.substr(0, pos);

    pair<string, string> eventPair = make_pair(eventCode, eventType);

    if (eventType == "keyup" || eventType == "keydown") {
        _keyboardEventSubscribers[eventPair].push_back(o);
        returnKey = _keyboardEventSubscribers[eventPair].size() - 1;
    } else if (eventType == "system") {
        _SystemEventSubscribers[eventPair] = o;
        returnKey = 1337; // wtf is a returnKey?
    } else {
        cout << "\nERROR: " << eventType << " The supplied event type is invalid.";
        return -1;
    }

    return returnKey;
}

/** unsubscribe from an event for an object **/
bool EventManager::unsubscribe(const string &eventName, const int &key) {
	return true;
}

/**
sf::Input is gone, we need to use sf::Keyboard and sf::Mouse now
and the functions are static so the class can be directly accessed.
**/

void EventManager::update() {
    if(_quitFlag)
        return;

    //const sf::Input* _SFMLInput = App::Instance()->getInput();

    int i = 0;

    bool isKeyDown = false;
    bool raiseEvent = false;

    map<pair<string, string>, vector<Object * > >::iterator keyIt;

    for (keyIt = _keyboardEventSubscribers.begin(); keyIt != _keyboardEventSubscribers.end(); keyIt++) {
        raiseEvent = false;

        //isKeyDown = _SFMLInput->IsKeyDown(keyBoardKeyCodeMap[keyIt->first.first]);
        isKeyDown = sf::Keyboard::IsKeyPressed(keyBoardKeyCodeMap[keyIt->first.first]);

        if (keyIt->first.second == "keyup" && isKeyDown == false && _keyStates[keyIt->first.first] == 1) {
            raiseEvent = true;
            _keyStates[keyIt->first.first] = 0;
        } else if (keyIt->first.second == "keydown" && isKeyDown == true && _keyStates[keyIt->first.first] == 0) {
            raiseEvent = true;
            _keyStates[keyIt->first.first] = 1;
        } else {
            raiseEvent = false;
        }

        if (raiseEvent) {
            for(i = 0; i < keyIt->second.size(); i++) {
                (*(keyIt->second[i])).keyBoardEventCallback(keyIt->first.first + "-" + keyIt->first.second);
            }
        }
    }

    /* system event callbacks */
    map<pair<string, string>, Object *>::iterator sysIt;
    for (sysIt = _SystemEventSubscribers.begin(); sysIt != _SystemEventSubscribers.end(); sysIt++) {
        if(sysIt->first.first == "update" && sysIt->first.second == "system") {
            sysIt->second->systemEventCallback(sysIt->first.first + "-" + sysIt->first.second);
        }
    }
}

void EventManager::releaseResource() {
    _quitFlag = true;
}

// Box2D for removal
/*
// Implement contact listener.
void EventManager::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    /*if (fixtureA == m_sensor)
    {
        void* userData = fixtureB->GetBody()->GetUserData();
        if (userData)
        {
            bool* touching = (bool*)userData;
            *touching = true;
        }
    }

    if (fixtureB == m_sensor)
    {
        void* userData = fixtureA->GetBody()->GetUserData();
        if (userData)
        {
            bool* touching = (bool*)userData;
            *touching = true;
        }
    }*/
//}

/*
// Implement contact listener.
void EventManager::EndContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    /*if (fixtureA == m_sensor)
    {
        void* userData = fixtureB->GetBody()->GetUserData();
        if (userData)
        {
            bool* touching = (bool*)userData;
            *touching = false;
        }
    }

    if (fixtureB == m_sensor)
    {
        void* userData = fixtureA->GetBody()->GetUserData();
        if (userData)
        {
            bool* touching = (bool*)userData;
            *touching = false;
        }
    }*/
// }
}
