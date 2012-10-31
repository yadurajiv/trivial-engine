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
		const char *image;
	};
	
	std::vector<rgbaToImage> _mapColorArray;
	
	const char *_imageName;

protected:
	
public:
	Map() {
		myImageManager = ImageManager::Instance();
		Trivial::SceneObject();
		moveTo(0,0);
	}
	
	void loadMapImage(const char *imageName) {
		_imageName = imageName;
		_levelBackground.image(_imageName);
		

	}
	
	virtual void update() {
		
	}
	
	virtual void _update(const bool& render = false) {
		Trivial::SceneObject::_update(render);
	}
	
	
	void replaceRGBAWithImage(int r, int g, int b, int a, const char *imageName) {
		rgbaToImage temp;
		temp.r = r;
		temp.g = g;
		temp.b = b;
		temp.a = a;

		temp.image = imageName;
		
		_mapColorArray.push_back(temp);
	}
	
	void replaceRGBWithImage(int r, int g, int b, const char *imageName) {
		rgbaToImage temp;
		temp.r = r;
		temp.g = g;
		temp.b = b;
		temp.a = 255;
		temp.image = imageName;
		
		_mapColorArray.push_back(temp);
		
	}
	
	void loadMap() {
		cout<<"loading start"<<endl;
		Trivial::Sprite **aSprite = new Trivial::Sprite*[50];
		for (int i=0; i<50; i++) {
			aSprite[i] = new Trivial::Sprite[38];
			for (int j=0; j<38; j++) {
				sf::Image img = Trivial::ImageManager::Instance()->get(_imageName)->copyToImage();

		        sf::Color col = img.getPixel(i,j);
				//cout<<"COLOR "<<col.r<<":"<<col.g<<":"<<col.b<<":"<<col.a<<endl;
				// Traverse Map Color Array to find images
				for(std::vector<rgbaToImage>::iterator it = _mapColorArray.begin(); it != _mapColorArray.end(); it++) {
				//for(int ctr=0; ctr<_mapColorIndex; ctr++) {
					if (col.r == it->r && col.g == it->g && col.b == it->b && col.a == it->a) {
						stringstream mapIndex;
						int index = i*j;
						mapIndex<<"MapIndex"<<i<<":"<<j;
						aSprite[i][j].image(it->image);
						int X = aSprite[i][j].width()*i + aSprite[i][j].width()/2 + Trivial::SceneObject::X();
						int Y = aSprite[i][j].height()*j + aSprite[i][j].height()/2 + Trivial::SceneObject::Y();

						aSprite[i][j].moveTo(8 + 16*i,8 +16*j);
						cout<<"Postition : "<<aSprite[i][j].X()<<":"<<aSprite[i][j].Y()<<endl;
						//cout<<"Postition : "<<Trivial::SceneObject::X()<<":"<<Trivial::SceneObject::Y()<<endl;
						add(mapIndex.str().c_str(), aSprite[i][j]);
						
						break;
					}
				}
			}
		}
		cout<<"loading end"<<endl;
	}
	
	
	~Map(){
		
	}
};

#endif