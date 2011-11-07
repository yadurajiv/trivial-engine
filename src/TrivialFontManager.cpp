#include <iostream>

#include "TrivialFontManager.h"

using namespace std;

namespace Trivial {

FontManager* FontManager::_pInstance;

FontManager::FontManager() {
}

FontManager* FontManager::Instance()
{
   if (!_pInstance)   // Only allow one instance of class to be generated.
      _pInstance = new FontManager;

   return _pInstance;
}

sf::Font* FontManager::get(const string &name) {
   if(_fonts.count(name) == 0) {
        std::cout << "\nERROR: Font resource not found\n";
        return new sf::Font();
   }

    map<string, sf::Font *>::iterator it = _fonts.find(name);
    if (it != _fonts.end())
    {
        return (*it).second;
    }
}

bool FontManager::add(const string &name, const string &path) {
// return false if image name exists
   if(_fonts.count(name) != 0)
        return false;

    sf::Font* fnt = new sf::Font();
    if(fnt->LoadFromFile(path)) {
        _fonts[name] = fnt;
    } else {
        delete fnt;
        return false;
        // throw exception, log image failed to load.
    }

    return true;

}

FontManager::~FontManager() {

    map<string, sf::Font *>::iterator it;
    for ( it=_fonts.begin() ; it != _fonts.end(); it++ ) {
        delete (*it).second;
    }
}

}
