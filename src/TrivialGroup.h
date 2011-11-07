#ifndef TRIVIALGROUP_H_INCLUDED
#define TRIVIALGROUP_H_INCLUDED

#include <map>
#include <string>

#include "TrivialGraphicsObject.h"

namespace Trivial {

class Group : public GraphicsObject {
public:

    Group();
    ~Group();

    virtual bool add(const string &name, GraphicsObject &o);
    virtual bool remove(const string &name);

    virtual void _update();
    virtual void update();

protected:

    std::map<string, GraphicsObject*> _items;

};

}

#endif // TRIVIALGROUP_H_INCLUDED
