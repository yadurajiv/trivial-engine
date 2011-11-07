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

using namespace std;

namespace Trivial {

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
    virtual void keyBoardEventCallback(const string &eventName) { };

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
    virtual void systemEventCallback(const string &eventName) { };

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
    virtual void mouseEventCallBack() { };

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
