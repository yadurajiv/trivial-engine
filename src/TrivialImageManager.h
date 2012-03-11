#ifndef TRIVIALIMAGEMANAGER_H_INCLUDED
#define TRIVIALIMAGEMANAGER_H_INCLUDED

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

#include "TrivialObject.h"

using namespace std;

namespace Trivial {


class ImageManager : public Object {

public:
    static ImageManager* Instance();

    bool parse(const string &resourceFile);

    bool add(const string &name, const string &path);

    sf::Texture* get(const string &name);

    bool setSmooth(const string &name, const bool& b);

    bool setRepeat(const string &name, const bool& b);

private:
    ImageManager();  // Private so that it can  not be called
    ~ImageManager();

    ImageManager(ImageManager const&){};             // copy constructor is private
    ImageManager& operator=(ImageManager const&){};  // assignment operator is private

    static ImageManager* _pInstance;

    std::map<string, sf::Texture*> _images;

};


}

#endif // TRIVIALIMAGEMANAGER_H_INCLUDED
