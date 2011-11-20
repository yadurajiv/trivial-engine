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

    _keyBoardKeyCodeMap.insert(make_pair("up", sf::Keyboard::Up));
    _keyBoardKeyCodeMap.insert(make_pair("down", sf::Keyboard::Down));
    _keyBoardKeyCodeMap.insert(make_pair("left", sf::Keyboard::Left));
    _keyBoardKeyCodeMap.insert(make_pair("right", sf::Keyboard::Right));

    _keyBoardKeyCodeMap.insert(make_pair("spacebar", sf::Keyboard::Space));
    _keyBoardKeyCodeMap.insert(make_pair("escape", sf::Keyboard::Escape));
    _keyBoardKeyCodeMap.insert(make_pair("enter", sf::Keyboard::Return));

    _keyBoardKeyCodeMap.insert(make_pair("a", sf::Keyboard::A));
    _keyBoardKeyCodeMap.insert(make_pair("b", sf::Keyboard::B));
    _keyBoardKeyCodeMap.insert(make_pair("c", sf::Keyboard::C));
    _keyBoardKeyCodeMap.insert(make_pair("d", sf::Keyboard::D));
    _keyBoardKeyCodeMap.insert(make_pair("e", sf::Keyboard::E));
    _keyBoardKeyCodeMap.insert(make_pair("f", sf::Keyboard::F));
    _keyBoardKeyCodeMap.insert(make_pair("g", sf::Keyboard::G));
    _keyBoardKeyCodeMap.insert(make_pair("h", sf::Keyboard::H));
    _keyBoardKeyCodeMap.insert(make_pair("i", sf::Keyboard::I));
    _keyBoardKeyCodeMap.insert(make_pair("j", sf::Keyboard::J));
    _keyBoardKeyCodeMap.insert(make_pair("k", sf::Keyboard::K));
    _keyBoardKeyCodeMap.insert(make_pair("l", sf::Keyboard::L));
    _keyBoardKeyCodeMap.insert(make_pair("m", sf::Keyboard::M));
    _keyBoardKeyCodeMap.insert(make_pair("n", sf::Keyboard::N));
    _keyBoardKeyCodeMap.insert(make_pair("o", sf::Keyboard::O));
    _keyBoardKeyCodeMap.insert(make_pair("p", sf::Keyboard::P));
    _keyBoardKeyCodeMap.insert(make_pair("q", sf::Keyboard::Q));
    _keyBoardKeyCodeMap.insert(make_pair("r", sf::Keyboard::R));
    _keyBoardKeyCodeMap.insert(make_pair("s", sf::Keyboard::S));
    _keyBoardKeyCodeMap.insert(make_pair("t", sf::Keyboard::T));
    _keyBoardKeyCodeMap.insert(make_pair("u", sf::Keyboard::U));
    _keyBoardKeyCodeMap.insert(make_pair("v", sf::Keyboard::V));
    _keyBoardKeyCodeMap.insert(make_pair("w", sf::Keyboard::W));
    _keyBoardKeyCodeMap.insert(make_pair("x", sf::Keyboard::X));
    _keyBoardKeyCodeMap.insert(make_pair("y", sf::Keyboard::Y));
    _keyBoardKeyCodeMap.insert(make_pair("z", sf::Keyboard::Z));

    // _keyBoardEventMap.insert(make_pair("keydown", sf::Event::KeyPressed));
    // _keyBoardEventMap.insert(make_pair("keyup", sf::Event::KeyReleased));

    // Set all key states to zero
    for (keyIt = _keyBoardKeyCodeMap.begin(); keyIt != _keyBoardKeyCodeMap.end(); keyIt++) {
        _keyStates[keyIt->first] = 0;
    }
    
    map<string, sf::Mouse::Button>::iterator mouseButtonIt;
    
    _mouseButtonMap.insert(make_pair("left", sf::Mouse::Left));
    _mouseButtonMap.insert(make_pair("right", sf::Mouse::Right));
    _mouseButtonMap.insert(make_pair("middle", sf::Mouse::Middle));
    _mouseButtonMap.insert(make_pair("x1", sf::Mouse::XButton1));
    _mouseButtonMap.insert(make_pair("x2", sf::Mouse::XButton2));
    
    for (mouseButtonIt = _mouseButtonMap.begin(); mouseButtonIt != _mouseButtonMap.end(); mouseButtonIt++) {
        _mouseButtonStatesMain[mouseButtonIt->first] = 0;
    }
    
    for (mouseButtonIt = _mouseButtonMap.begin(); mouseButtonIt != _mouseButtonMap.end(); mouseButtonIt++) {
        _mouseButtonStatesSub[mouseButtonIt->first] = 0;
    }
    
    // mouseButtonEventMap.insert(make_pair("buttondown", 0))

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

    // Find from the right side 
    pos = eventName.rfind("-");
    
    // In case not found
    if (pos == string::npos) {
        cout << "\nERROR: " << eventName << " The supplied event string is invalid.";
        return -1;
    }

    // In case the '-' was the last character
    if ((pos + 1) > eventName.size()) {
        cout << "\nERROR: " << eventName << " The supplied event string is invalid.";
        return -1;
    }

    // Parse the event identifier
    eventType = eventName.substr(pos + 1);   // get from last '-' to the end
    eventCode = eventName.substr(0, pos); // get everything from beginning of time and beyond...

    // Make the higher level pair for the event identifier. 
    // The eventCode can be parsed later for sub event types in its respective
    // logic. Any further subsubsub event type parsing is left to the user as a 
    // homework exercise. x-) eventType are a few keyworded types in Trivial. 
    pair<string, string> eventPair = make_pair(eventCode, eventType);

    // Now lets see what we have here
    if (eventType == "keyup" || eventType == "keydown") {
        _keyboardEventSubscribers[eventPair].push_back(o);
        returnKey = _keyboardEventSubscribers[eventPair].size() - 1;
    } else if (eventType == "system") {
        _systemEventSubscribers[eventPair] = o;
        returnKey = 0;
    } else if (eventType == "mouse") {
        _mouseEventSubscribers[eventPair].push_back(o);
        returnKey = _mouseEventSubscribers[eventPair].size() - 1;
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
    bool raiseKeyboardEvent = false;

    map<pair<string, string>, vector<Object * > >::iterator keyIt;

    for (keyIt = _keyboardEventSubscribers.begin(); keyIt != _keyboardEventSubscribers.end(); keyIt++) {
        raiseKeyboardEvent = false;

        //isKeyDown = _SFMLInput->IsKeyDown(_keyBoardKeyCodeMap[keyIt->first.first]);
        isKeyDown = sf::Keyboard::IsKeyPressed(_keyBoardKeyCodeMap[keyIt->first.first]);

        if (keyIt->first.second == "keyup" && isKeyDown == false && _keyStates[keyIt->first.first] == 1) {
            raiseKeyboardEvent = true;
            _keyStates[keyIt->first.first] = 0;
        } else if (keyIt->first.second == "keydown" && isKeyDown == true && _keyStates[keyIt->first.first] == 0) {
            raiseKeyboardEvent = true;
            _keyStates[keyIt->first.first] = 1;
        } else {
            raiseKeyboardEvent = false;
        }

        if (raiseKeyboardEvent) {
            for (i = 0; i < keyIt->second.size(); i++) {
                TrivialKeyBoardEvent tke;
                
                tke.eventName = keyIt->first.first + "-" + keyIt->first.second;
                tke.eventType = keyIt->first.second;
                tke.eventCode = keyIt->first.first;
                
                (*(keyIt->second[i])).keyBoardEventCallback(tke);
                raiseKeyboardEvent = false;
            }
        }
    }
    
    TrivialMouseEvent tme;

    // Do this preemptive. Most of the mouse struct members are better filled
    // at the start.
    if (_mouseEventSubscribers.size() >= 1) {
        tme.lButton = sf::Mouse::IsButtonPressed(sf::Mouse::Left);
        tme.mButton = sf::Mouse::IsButtonPressed(sf::Mouse::Middle);
        tme.rButton = sf::Mouse::IsButtonPressed(sf::Mouse::Right);
        tme.x1Button = sf::Mouse::IsButtonPressed(sf::Mouse::XButton1);
        tme.x2Button = sf::Mouse::IsButtonPressed(sf::Mouse::XButton2);
        tme.pos = sf::Mouse::GetPosition(*(Trivial::App::Instance()->getSFMLRenderWindow()));
        tme.pos.x += Trivial::SceneManager::Instance()->getActiveScene()->getCamera()->X();
        tme.pos.y += Trivial::SceneManager::Instance()->getActiveScene()->getCamera()->Y();
    }
    
    map<pair<string, string>, vector<Object *> >::iterator mouseIt;
    for (mouseIt = _mouseEventSubscribers.begin(); mouseIt != _mouseEventSubscribers.end(); mouseIt++) {
        // Fill up the event string details
        tme.eventName = mouseIt->first.first + "-" + mouseIt->first.second;
        tme.eventType = mouseIt->first.second;
        tme.eventCode = mouseIt->first.first;
        
        // First kick off the basic mouse handler directly if that is what it is
        if (tme.eventCode == "update") {
            for (i = 0; i < mouseIt->second.size(); i++) {
                 (*(mouseIt->second[i])).mouseEventCallBack(tme);
            }
            continue; // Move on to the next object
        }
        
        // Else calculate the other event types        
        pair<string, vector<string> > eC;
        
        eC = parseSubEventString(tme.eventCode);
        
        tme.eventCode = eC.first;
        tme.subEventCodes = eC.second;
        
        if (tme.eventCode == "buttondown" || tme.eventCode == "buttonup") {
            if (tme.subEventCodes.size() > 0) {
                /* mouse event callbacks */
                bool isMouseButtonDown = false;
                bool raiseMouseButtonEvent = false;
                
                // Check for a specific button
                isMouseButtonDown = sf::Mouse::IsButtonPressed(_mouseButtonMap[tme.subEventCodes.front()]);
                            
                if (tme.eventCode == "buttonup" && isMouseButtonDown == false && _mouseButtonStatesSub[tme.subEventCodes.front()] == 1) {
                    raiseMouseButtonEvent = true;
                    _mouseButtonStatesSub[tme.subEventCodes.front()] = 0;
                } else if (tme.eventCode == "buttondown" && isMouseButtonDown == true && _mouseButtonStatesSub[tme.subEventCodes.front()] == 0) {                            
                    raiseMouseButtonEvent = true;
                    _mouseButtonStatesSub[tme.subEventCodes.front()] = 1;
                } else {
                    raiseMouseButtonEvent = false;
                }

                if (raiseMouseButtonEvent) {
                    for (i = 0; i < mouseIt->second.size(); i++) {
                         (*(mouseIt->second[i])).mouseEventCallBack(tme);
                        raiseMouseButtonEvent = false;
                    }
                }
            } else {
                /* mouse event callbacks */
                bool isMouseButtonDown = false;
                bool raiseMouseButtonEvent = false;
                
                // Check if any button is down                
                map<string, sf::Mouse::Button>::iterator mouseButtonIt;

                for (mouseButtonIt = _mouseButtonMap.begin(); mouseButtonIt != _mouseButtonMap.end(); mouseButtonIt++) {
                    isMouseButtonDown = sf::Mouse::IsButtonPressed(mouseButtonIt->second);
                    
                    if (tme.eventCode == "buttonup" && isMouseButtonDown == false && _mouseButtonStatesMain[mouseButtonIt->first] == 1) {
                        raiseMouseButtonEvent = true;
                        _mouseButtonStatesMain[mouseButtonIt->first] = 0;
                    } else if (tme.eventCode == "buttondown" && isMouseButtonDown == true && _mouseButtonStatesMain[mouseButtonIt->first] == 0) {                        
                        raiseMouseButtonEvent = true;
                        _mouseButtonStatesMain[mouseButtonIt->first] = 1;
                    } else {
                        raiseMouseButtonEvent = false;
                    }

                    if (raiseMouseButtonEvent) {
                        for (i = 0; i < mouseIt->second.size(); i++) {
                             (*(mouseIt->second[i])).mouseEventCallBack(tme);
                            raiseMouseButtonEvent = false;
                        }
                    }
                }
            }
        }
    }



    /* system event callbacks */
    map<pair<string, string>, Object *>::iterator sysIt;
    for (sysIt = _systemEventSubscribers.begin(); sysIt != _systemEventSubscribers.end(); sysIt++) {
        if (sysIt->first.first == "update") {
            TrivialSystemEvent tse;
            
            tse.eventName = sysIt->first.first + "-" + sysIt->first.second;
            tse.eventType = sysIt->first.second;
            tse.eventCode = sysIt->first.first;
            
            sysIt->second->systemEventCallback(tse);
        }
    }
}

pair<string, vector<string> > EventManager::parseSubEventString(string subEventString) {
    string eventCode;
    vector<string> subEventCodes;

    int subPos = subEventString.rfind("-");
    
    if (subPos == string::npos) {
        eventCode = subEventString;
        return make_pair(eventCode, subEventCodes);
    } else {
        eventCode = subEventString.substr(subPos + 1);
        subEventString = subEventString.substr(0, subPos);
    }
    
    while (1) {
        subPos = subEventString.rfind("-");
        
        if (subPos == string::npos) {
            subEventCodes.push_back(subEventString);
            break;
        }
        
        subEventCodes.push_back(subEventString.substr(subPos + 1));
        subEventString = subEventString.substr(0, subPos);
    }
    
    return make_pair(eventCode, subEventCodes);
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
