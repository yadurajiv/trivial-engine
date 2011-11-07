#include "TrivialGraphicsObject.h"
#include "TrivialGroup.h"

namespace Trivial {

Group::Group() {
}

Group::~Group() {
}

bool Group::add(const string &name, GraphicsObject &o) {
    // If an object with this name already exisits, return
    if(_items.count(name) > 0) {
        return false;
    }

    _items[name] = &o;

    return true;
}

bool Group::remove(const string &name) {
    if(_items.count(name) == 0)
        return false;

    map<string, GraphicsObject*>::iterator it = _items.find(name);
    if (it != _items.end())
    {
        _items.erase(it);
        return true;
    }

    return false;

}

void Group::_update() {
    map<string, GraphicsObject*>::iterator it;

    for ( it=_items.begin() ; it != _items.end(); it++ ) {
        (*it).second->_update();
    }

    update();
}

void Group::update() {

}

}
