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

bool ImageManager::setSmooth(const string &name, const bool& b) {
   if(_images.count(name) == 0) {
        std::cout << "\nERROR: texture resource not found\n";
        return false;
   }

    map<string, sf::Texture *>::iterator it = _images.find(name);
    if (it != _images.end())
    {
        (*it).second->setSmooth(b);
        return true;
    }
    return false;
}

bool ImageManager::setRepeat(const string &name, const bool& b) {
   if(_images.count(name) == 0) {
        std::cout << "\nERROR: texture resource not found\n";
        return false;
   }

    map<string, sf::Texture *>::iterator it = _images.find(name);
    if (it != _images.end())
    {
        (*it).second->setRepeated(b);
        return true;
    }
    return false;
}

bool ImageManager::createTexture(const string &name, const int &width, const int &height, const sf::Color fill) {

    sf::Image* image = new sf::Image();
    image->create(width, height,fill);

    sf::Texture* img = new sf::Texture();
    if(img->loadFromImage(*image)) {
        _images[name] = img;
    } else {
        delete img;
        delete image;
        return false;
        // throw exception, log image failed to load.
    }

    delete image;
    return true;
}

bool ImageManager::add(const string &name, const string &path) {
// return false if image name exists
   if(_images.count(name) != 0)
        return false;

    sf::Texture* img = new sf::Texture();
    if(img->loadFromFile(path)) {
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
