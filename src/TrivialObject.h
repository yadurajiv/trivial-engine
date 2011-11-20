/**
 * @file    TrivialObject.h
 * @author  Team Trivial <team@trivialengine.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * -- TBD --
 *
 * @section DESCRIPTION
 *
 * The base class for all other objects in TrivialEngine.
 */

#ifndef TRIVIALOBJECT_H_INCLUDED
#define TRIVIALOBJECT_H_INCLUDED

#include <string>
#include <vector>

#include "SFML/System/Vector2.hpp"

using namespace std;

namespace Trivial {


struct TrivialEvent {
    string eventName; // Complete string identifier
    string eventType; // identifier substring defining event super type
    string eventCode; // identifier substring defining event sub type
    vector<string> subEventCodes; // vector of sub sub types (for crazy events)
};

struct TrivialKeyBoardEvent : TrivialEvent {
    // Nothing special here, for now...
};

struct TrivialSystemEvent : TrivialEvent {
    // Nothing special here, for now...
};

struct TrivialMouseEvent : TrivialEvent {
    int scroll;
    bool lButton;
    bool mButton;
    bool rButton;
    bool x1Button;
    bool x2Button;
    sf::Vector2i pos;
};

class Object {

public:

    /**
        constructor for the class.
    */
    Object();

    /**
        destructor for the class.
    */
    ~Object();

    /**
        keyBoardEventCallback is a virtual keyboard event callback used
        by the EventManager. This needs to be implemented by inheriting
        classes as and when needed. All Objects in TrivialEngine can subscribe
        to various events.

        @param eventName is a string value passed back to the callback
        by the EventManager

        @see systemEventCallback
        @see mouseEventCallBack
        @see collisionEventCallBack
        @see EventManager.subscribe
        @see EventManager.unsubscribe
    */
    virtual void keyBoardEventCallback(const TrivialKeyBoardEvent &e) { };

    /**
        systemEventCallback is a virtual system event callback used
        by the EventManager. This needs to be implemented by inheriting
        classes as and when needed. All Objects in TrivialEngine can subscribe
        to various events.

        @param eventName - is a string value passed back to the callback
        by the EventManager

        @see keyBoardEventCallback
        @see mouseEventCallBack
        @see collisionEventCallBack
        @see EventManager.subscribe
        @see EventManager.unsubscribe
    */
    virtual void systemEventCallback(const TrivialSystemEvent &e) { };

    /**
        mouseEventCallBack is a virtual mouse event callback used
        by the EventManager. This needs to be implemented by inheriting
        classes as and when needed. All Objects in TrivialEngine can subscribe
        to various events.

        *This is a work in progress.*

        @see keyBoardEventCallback
        @see systemEventCallback
        @see collisionEventCallBack
        @see EventManager.subscribe
        @see EventManager.unsubscribe
    */
    virtual void mouseEventCallBack(const TrivialMouseEvent &e) { };

    /**
        collisionEventCallBack is a virtual collision event callback used
        by the EventManager. This needs to be implemented by inheriting
        classes as and when needed. All Objects in TrivialEngine can subscribe
        to various events.


        @see keyBoardEventCallback
        @see systemEventCallback
        @see mouseEventCallBack
        @see collisionEventCallBack
        @see EventManager.subscribe
        @see EventManager.unsubscribe
    */
    virtual void collisionEventCallBack() { };
};

}

#endif // TRIVIALOBJECT_H_INCLUDED
