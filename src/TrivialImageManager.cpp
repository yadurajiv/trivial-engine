#include <iostream>

#include "TrivialImageManager.h"

namespace Trivial {

ImageManager* ImageManager::_pInstance;

ImageManager::ImageManager() {
}

ImageManager* ImageManager::Instance()
{
   if (!_pInstance)   // Only allow one instance of class to be generated.
      _pInstance = new ImageManager;

   return _pInstance;
}

sf::Texture* ImageManager::get(const string &name) {
   if(_images.count(name) == 0) {
        std::cout << "\nERROR: texture resource not found\n";
        return new sf::Texture();
   }

    map<string, sf::Texture *>::iterator it = _images.find(name);
    if (it != _images.end())
    {
        return (*it).second;
    }
}

bool ImageManager::add(const string &name, const string &path) {
// return false if image name exists
   if(_images.count(name) != 0)
        return false;

    sf::Texture* img = new sf::Texture();
    if(img->LoadFromFile(path)) {
        // images remain sharp after zooming if SetSmooth is false(by default)
        // img->SetSmooth(true);
        _images[name] = img;
    } else {
        delete img;
        return false;
        // throw exception, log image failed to load.
    }

    return true;

}

ImageManager::~ImageManager() {

    map<string, sf::Texture *>::iterator it;
    for ( it=_images.begin() ; it != _images.end(); it++ ) {
        delete (*it).second;
    }
}

}
