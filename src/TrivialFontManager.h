#ifndef TRIVIALFONTMANAGER_H_INCLUDED
#define TRIVIALFONTMANAGER_H_INCLUDED

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialObject.h"

using namespace std;

namespace Trivial {


class FontManager : public Object {

public:
    static FontManager* Instance();

    bool parse(const string &resourceFile);

    bool add(const string &name, const string &path);

    sf::Font* get(const string &name);

    void releaseResources() {
        map<string, sf::Font*>::iterator it;
        for ( it=_fonts.begin() ; it != _fonts.end(); it++ ) {
            delete (*it).second;
        }
    }

private:
    FontManager();  // Private so that it can  not be called
    ~FontManager();

    FontManager(FontManager const&){};             // copy constructor is private
    FontManager& operator=(FontManager const&){};  // assignment operator is private

    static FontManager* _pInstance;

    std::map<string, sf::Font*> _fonts;

};


}

#endif // TRIVIALFONTMANAGER_H_INCLUDED
