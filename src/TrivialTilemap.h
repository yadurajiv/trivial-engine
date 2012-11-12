#ifndef TRIVIALTILEMAP_H_INCLUDED
#define TRIVIALTILEMAP_H_INCLUDED

#include <string>

#include <vector>

#include <SFML/Graphics.hpp>

#include "TrivialSceneObject.h"

#include "TrivialImageManager.h"

using namespace std;

namespace Trivial {

class Tilemap : public SceneObject {
public:

    Tilemap() {
        _app = Trivial::App::Instance();
        _im = Trivial::ImageManager::Instance();
    };

    ~Tilemap() { };

    virtual void update() { };

    virtual void _update(const bool& render = false) {

        for(int i=0;i<_mapFilled;i++) {
            _tiles[i]->_update(true);
        }

        update();
    };

    bool loadTilemap(const string &map, const string &tileset, const int &tileWidth, const int &tileHeight, const bool &isometric = false) {

        _tileset = tileset;

        _mapTex = _im->get(map);
        _mapImg = _mapTex->copyToImage();

        sf::Vector2u ms = _mapImg.getSize();
        _numCols = ms.x;
        _numRows = ms.y;
        _width = ms.x * tileWidth;
        _height = ms.y * tileHeight;

        _tileWidth = tileWidth;
        _tileHeight = tileHeight;

        _isometric = isometric;

        //cout << _width;

        const Uint8* pixels = _mapImg.getPixelsPtr();

        unsigned int c = ms.x * ms.y * 4;

        Uint8 r;
        Uint8 g;
        Uint8 b;

        bool x1,x2,x3,y1,y2,y3,z1,z2,z3;

        _mapSize = 0;
        _mapEmpty = 0;
        _mapFilled = 0;

        int twb2 = _tileWidth/2;
        int twb4 = _tileWidth/4;

        for(int i = 0, tileCounter=0,wc=1, row=0; i < c; i=i+4, wc++,tileCounter++) {
            r = *(pixels+i);
            g = *(pixels+(i+1));
            b = *(pixels+(i+2));
            //a = (pixels+(i+3));

            //y2 or i
            if(r==0&&g==0&&b==0) {
                y2 = true;
                /*
                i-(w+1) i-w i-(w-1)
                i-1     i   i+1
                i+(w-1) i+w i+w
                */

                _mapFilled = _mapFilled + 1;
                string cell = "x";

                /**

                x1  x2  x3
                y1  y2  y3
                z1  z2  z3

                y2 = i

                **/

                //x1
                if(i-((ms.x*4)+4) >= 0) {
                    int tmpx1 = i-((ms.x*4)+4);
                    r = *(pixels+tmpx1);
                    g = *(pixels+(tmpx1+1));
                    b = *(pixels+(tmpx1+2));
                    if(r==0&&g==0&&b==0) {
                        x1 = true;
                    } else {
                        x1 = false;
                    }
                } else {
                    x1 = false;
                }

                //x2
                if(i-(ms.x*4) >= 0) {
                    int tmpx2 = i-(ms.x*4);
                    r = *(pixels+tmpx2);
                    g = *(pixels+(tmpx2+1));
                    b = *(pixels+(tmpx2+2));
                    if(r==0&&g==0&&b==0) {
                        x2 = true;
                    } else {
                        x2 = false;
                    }
                } else {
                    x2 = false;
                }

                //x3
                if(i-((ms.x*4)-4) >= 0) {
                    int tmpx3 = i-((ms.x*4)-4);
                    r = *(pixels+tmpx3);
                    g = *(pixels+(tmpx3+1));
                    b = *(pixels+(tmpx3+2));
                    if(r==0&&g==0&&b==0) {
                        x3 = true;
                    } else {
                        x3 = false;
                    }
                } else {
                    x3 = false;
                }

                //y1
                if(i-4 >= 0) {
                    int tmpy1 = i-4;
                    r = *(pixels+tmpy1);
                    g = *(pixels+(tmpy1+1));
                    b = *(pixels+(tmpy1+2));
                    if(r==0&&g==0&&b==0) {
                        y1 = true;
                    } else {
                        y1 = false;
                    }
                } else {
                    y1 = false;
                }

                //y3
                if(i+4 >= 0) {
                    int tmpy3 = i+4;
                    r = *(pixels+tmpy3);
                    g = *(pixels+(tmpy3+1));
                    b = *(pixels+(tmpy3+2));
                    if(r==0&&g==0&&b==0) {
                        y3 = true;
                    } else {
                        y3 = false;
                    }
                } else {
                    y3 = false;
                }

                //z1
                if(i+((ms.x*4)-4) >= 0) {
                    int tmpz1 = i+((ms.x*4)-4);
                    r = *(pixels+tmpz1);
                    g = *(pixels+(tmpz1+1));
                    b = *(pixels+(tmpz1+2));
                    if(r==0&&g==0&&b==0) {
                        z1 = true;
                    } else {
                        z1 = false;
                    }
                } else {
                    z1 = false;
                }

                //z2
                if(i+(ms.x*4) >= 0) {
                    int tmpz2 = i+(ms.x*4);
                    r = *(pixels+tmpz2);
                    g = *(pixels+(tmpz2+1));
                    b = *(pixels+(tmpz2+2));
                    if(r==0&&g==0&&b==0) {
                        z2 = true;
                    } else {
                        z2 = false;
                    }
                } else {
                    z2 = false;
                }

                //z3
                if(i+((ms.x*4)+4) >= 0) {
                    int tmpz3 = i+((ms.x*4)+4);
                    r = *(pixels+tmpz3);
                    g = *(pixels+(tmpz3+1));
                    b = *(pixels+(tmpz3+2));
                    if(r==0&&g==0&&b==0) {
                        z3 = true;
                    } else {
                        z3 = false;
                    }
                } else {
                    z3 = false;
                }

                //y
                if(!x1&&!x2&&!x3&&!y1&&!y3&&!z1&&!z2&&!z3) {
                    cell = "y";
                }

                //a
                if((!x1&&!x2&&!y1)&&(y3&&z3&&z2)) {
                    cell = "a";
                }

                //b
                if((!x2&&!x3&&!y3)&&(y1&&z1&&z2)) {
                    cell = "b";
                }

                //c
                if((x1&&x2&&y1)&&(!y3&&!z3&&!z2)) {
                    cell = "c";
                }

                //d
                if((!y1&&!z1&&!z2)&&(x2&&x3&&y3)) {
                    cell = "d";
                }

                //i
                if((x2&&z2)&&(!y1&&!y3)) {
                    cell = "i";
                }

                //k
                if((!x2&&!z2)&&(y1&&y3)) {
                    cell = "j";
                }

                //m
                if((z2)&&(!x2&&!y1&&!y3)) {
                    cell = "o";
                }

                //n
                if((y1)&&(!x2&&!y3&&!z2)) {
                    cell = "p";
                }

                //o
                if((x2)&&(!z2&&!y1&&!y3)) {
                    cell = "q";
                }

                //p
                if((y3)&&(!x2&&!y1&&!z2)) {
                    cell = "r";
                }

                //s
                if((!z2)&&(x2&&y1&&y3)) {
                    cell = "s";
                }

                //w
                if((!y1)&&(x2&&y3&&z2)) {
                    cell = "w";
                }

                //n
                if((!x2)&&(z2&&y1&&y3)) {
                    cell = "n";
                }

                //e
                if((!y3)&&(x2&&y1&&z2)) {
                    cell = "e";
                }

                /**
                    assuming 15 frames are possible ~_~
                **/
                Trivial::AnimatedSprite* tmp = new Trivial::AnimatedSprite();
                tmp->image(_tileset,_tileWidth, _tileHeight);
                tmp->addAnimation("y", 0, 0, 1);
                tmp->addAnimation("q", 1, 1, 1);
                tmp->addAnimation("r", 2, 2, 1);
                tmp->addAnimation("d", 3, 3, 1);
                tmp->addAnimation("o", 4, 4, 1);
                tmp->addAnimation("i", 5, 5, 1);
                tmp->addAnimation("a", 6, 6, 1);
                tmp->addAnimation("w", 7, 7, 1);
                tmp->addAnimation("p", 8, 8, 1);
                tmp->addAnimation("c", 9, 9, 1);
                tmp->addAnimation("j", 10, 10, 1);
                tmp->addAnimation("s", 11, 11, 1);
                tmp->addAnimation("b", 12, 12, 1);
                tmp->addAnimation("e", 13, 13, 1);
                tmp->addAnimation("n", 14, 14, 1);
                tmp->addAnimation("x", 15, 15, 1);

                /**
                    maybe a different approach can be found here
                    http://stackoverflow.com/questions/892811/drawing-isometric-game-worlds
                **/
                if(_isometric) {
                    if(row%2 == 0) {
                        tmp->moveTo( ((tileCounter % ms.x) * _tileWidth) + twb2, ((tileCounter / ms.x) * twb4) );
                    } else {
                        tmp->moveTo( (tileCounter % ms.x) * _tileWidth, ((tileCounter / ms.x) * twb4)  );
                    }
                } else {
                    tmp->moveTo( (tileCounter % ms.x) * _tileWidth, (tileCounter / ms.x) * _tileWidth);
                }
                //cout << "\nX: " << (tileCounter % ms.x) * _tileWidth;
                //cout << " Y: " << (tileCounter / ms.x) * _tileWidth;
                //cout << "\n";

                tmp->gotoAndPlay(cell,15);

                _tiles.push_back(tmp);

                _map.push_back(cell);
                cout << cell;
            } else {

                y2 = false;

                _mapEmpty = _mapEmpty + 1;

                _map.push_back("~");
                cout << "~";
            }

            if(wc == ms.x) {
                cout << "\n";
                wc = 0;
                row++;
            }
        }

        // this should be equal to _mapFilled + _mapEmpty
        _mapSize = _map.size();
/*
        cout << "\ntotal is : " << c << " and also c*4 is " << c *4;
        cout << "\nmapSize: " << _mapSize;
        cout << "\nmapFilled: " << _mapFilled;
        cout << "\nmapEmpty: " << _mapEmpty << "\n";
*/
        return true;
    }

    /**
     need to override more base class functions
    **/

private:

    sf::Texture* _mapTex;
    sf::Image _mapImg;

    vector<string> _map;

    Trivial::App* _app;
    Trivial::ImageManager* _im;

    int _mapSize;
    int _mapEmpty;
    int _mapFilled;

    vector<Trivial::AnimatedSprite*> _tiles;

    string _tileset;
    int _tileWidth;
    int _tileHeight;

    int _numCols;
    int _numRows;

    bool _isometric;
};

}

#endif // TRIVIALTILEMAP_H_INCLUDED
