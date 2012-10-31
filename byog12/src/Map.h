#ifndef MAP_H
#define MAP_H

#include "TrivialSceneObject.h"
#include "TrivialSprite.h"
#include "TrivialObject.h"
#include "TrivialSceneManager.h"
#include <string>

using namespace Trivial;
class Map : public Trivial::SceneObject{
private:

	Trivial::Sprite **aSprite;
	Trivial::Sprite _levelBackground;
	EventManager *myEventManager;
    ImageManager *myImageManager;
	SceneManager *mySceneManager;
	Camera cam;

	struct rgbaToImage {
		int r;
		int g;
		int b;
		int a;
		const char *image;
	};

	std::vector<rgbaToImage> _mapColorArray;

	const char *_imageName;

	int _currentCameraX, _currentCameraY;
	unsigned int _mapIndexX, _mapIndexY;
protected:

public:
	Map() {
		myImageManager = ImageManager::Instance();
		mySceneManager = SceneManager::Instance();

		Trivial::SceneObject();
		moveTo(0,0);
		_currentCameraX = 0;
		_currentCameraY = 0;
		_mapIndexX = 0;
		_mapIndexY = 0;
	}

	void loadMapImage(const char *imageName) {
		_imageName = imageName;
		_levelBackground.image(_imageName);

	}

	virtual void update() {
		//if (Trivial::SceneManager::Instance()->getActiveScene() != NULL)
		cam = *(Trivial::SceneManager::Instance()->getActiveScene()->getCamera());
		if(_currentCameraX != cam.X() || _currentCameraY != cam.Y()) {
			_mapIndexX = _currentCameraX - cam.X();
			_mapIndexY = _currentCameraY - cam.Y();
			if(_mapIndexX/16 + 75 <= _levelBackground.width() && _mapIndexY/16 + 50 <= _levelBackground.height()) {
				//DrawMap();
			}
		}
	}

	virtual void _update(const bool& render = false) {
		Trivial::SceneObject::_update(render);
	}
	
	void DrawMap() {
		int tilewidth = 16;
		int tileheight = 16;
		//for(int i= _mapIndexX/tilewidth; i<_mapIndexX/tilewidth + 75; i++){
		for (int i=0; i<_levelBackground.width(); i++) {
			//for(int j=_mapIndexY/tileheight;j<_mapIndexY/tileheight + 50;j++){
			for(int j=0;j<_levelBackground.height();j++) {
				int X = aSprite[i][j].width()*i + aSprite[i][j].width()/2 + Trivial::SceneObject::X();
				int Y = aSprite[i][j].height()*j + aSprite[i][j].height()/2 + Trivial::SceneObject::Y();

				aSprite[i][j].moveTo(X,Y);
				stringstream mapIndex;
				int index = i*j;
				mapIndex<<"MapIndex"<<i<<":"<<j;
				add(mapIndex.str().c_str(), aSprite[i][j]);
			}
		}
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
		aSprite = new Trivial::Sprite*[(int)_levelBackground.width()];

		// do this once for heavens sake
		sf::Image img = Trivial::ImageManager::Instance()->get(_imageName)->copyToImage();
		for (int i=0; i<_levelBackground.width(); i++) {
			aSprite[i] = new Trivial::Sprite[(int)_levelBackground.height()];
			for (int j=0; j<_levelBackground.height(); j++) {
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

						//add(mapIndex.str().c_str(), aSprite[i][j]);

						break;
					}
				}
			}
		}

		DrawMap();
		cout<<"loading end"<<endl;
	}


	~Map(){

	}
};

#endif
