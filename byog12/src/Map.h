#ifndef MAP_H
#define MAP_H 

#include "TrivialSceneObject.h"
#include "TrivialSprite.h"
#include <string>

using namespace Trivial;
class Map : public Trivial::SceneObject{
private:
	
	
	Trivial::Sprite _levelBackground;
	EventManager *myEventManager;
    ImageManager *myImageManager;
	
	struct rgbaToImage {
		int r;
		int g;
		int b;
		int a;
		Trivial::Sprite image;
	};
	
	rgbaToImage *_mapColorArray;
	int _mapColorIndex;
	
	const char *_imageName;

protected:
	
public:
	Map() {
		myImageManager = ImageManager::Instance();
		Trivial::SceneObject();
	}
	
	void loadMapImage(const char *imageName) {
        
		_levelBackground.image(imageName);
		
		_mapColorIndex = 0;

	}
	
	
	void replaceRGBAWithImage(int r, int g, int b, int a, const char *imageName) {
		_mapColorArray[_mapColorIndex].r = r;
		_mapColorArray[_mapColorIndex].g = g;
		_mapColorArray[_mapColorIndex].b = b;
		_mapColorArray[_mapColorIndex].a = a;
		
		_mapColorArray[_mapColorIndex].image.image(imageName);
		
		_mapColorIndex++;
	}
	
	void replaceRGBWithImage(int r, int g, int b, const char *imageName) {
		_mapColorArray[_mapColorIndex].r = r;
		_mapColorArray[_mapColorIndex].g = g;
		_mapColorArray[_mapColorIndex].b = b;
		_mapColorArray[_mapColorIndex].a = 1;
		_mapColorArray[_mapColorIndex].image.image(imageName);
		
		_mapColorIndex++;
		
	}
	
	void loadMap() {
		for (int i=0; i<_levelBackground.width(); i++) {
			for (int j=0; i<_levelBackground.height(); j++) {
				sf::Image img = Trivial::ImageManager::Instance()->get(_imageName)->copyToImage();

		        sf::Color col = img.getPixel(i,j);
		        
				// Traverse Map Color Array to find images
				for(int i=0; i<_mapColorIndex; i++) {
					if (col.r == _mapColorArray[_mapColorIndex].r && col.g == _mapColorArray[_mapColorIndex].g && col.b == _mapColorArray[_mapColorIndex].b && col.a == _mapColorArray[_mapColorIndex].a) {
						stringstream mapIndex;
						mapIndex<<"MapIndex"<<i<<":"<<j;
						add(mapIndex.str().c_str(), _mapColorArray[_mapColorIndex].image);
						int X = _mapColorArray[_mapColorIndex].image.width()*i;
						int Y = _mapColorArray[_mapColorIndex].image.height()*j;
						_mapColorArray[_mapColorIndex].image.moveTo(X,Y);
					}
				}
			}
		}
	}
	
	
	~Map(){}
};

#endif