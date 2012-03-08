#ifndef TRIVIALMASKCOLLISION_H_INCLUDED
#define TRIVIALMASKCOLLISION_H_INCLUDED 

#include "TrivialSprite.h"
#include "TrivialScene.h"
#include "TrivialHelper.h"
#include <SFML/Graphics.hpp>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

using namespace std;

namespace Trivial
{
	
	struct Color
	{
		int r;
		int g;
		int b;
		int a;
	};
	
	class MaskScene : public Scene
	{
	private:
		
	public:
		MaskScene();
		~MaskScene();
		
		void preload();
		
		void reset();
		
		void update();
		
		void deactivated();
		
		void activated();
		
	};
	
	MaskScene::MaskScene()
	{
		
	}
	
	MaskScene::~MaskScene()
	{
		
	}
	
	void MaskScene::preload()
	{
		
	}
	
	void MaskScene::reset()
	{
		
	}
	
	void MaskScene::update()
	{
		
	}
	
	void MaskScene::deactivated()
	{
	
	}
	
	void MaskScene::activated()
	{
		
	}
	
	class MaskCollision : public Sprite
	{
	private:
		Sprite maskSprite;
		SceneManager *mySceneManager;
		Color color;
	public:
		MaskCollision();
		~MaskCollision();
		
		virtual void update(){};
		virtual void _update();
		
		void image(const string &imageName, const string &maskImageName);
		bool isMaskAt(int x, int y);
		
	};
	
	MaskCollision::MaskCollision()
	{
		color.r = color.g = color.b = color.a = 255;
	}
	
	MaskCollision::~MaskCollision()
	{
		
	}
	
	void MaskCollision::_update()
	{
		update();
		maskSprite.moveTo(X(), Y());
	}
	
	
	void MaskCollision::image(const string &imageName, const string &maskImageName)
	{
		Sprite::image(imageName);
		mySceneManager = SceneManager::Instance();
		MaskScene *maskScene = new MaskScene;
		mySceneManager->addScene("maskScreen", maskScene);
		maskSprite.image(maskImageName);
		sf::Color c = maskSprite.SFMLsprite.GetColor();
		color.r = c.r;
		color.b = c.b;
		color.g = c.g;
		color.a = c.a;
		maskScene->add(maskImageName, maskSprite);
		cout<<"Set Active Scene : "<<mySceneManager->setActiveScene("maskScreen");
		
	}
	
	bool MaskCollision::isMaskAt(int x, int y)
	{
		if(pointOverlap(x,y))
		{
			GLubyte* pixel = new GLubyte[4];
			glReadPixels(x, 600-y, 1, 1, GL_RGBA, GL_UNSIGNED_INT, pixel);
			cout<<"OR:"<<color.r<<endl;
			cout<<"OG:"<<color.g<<endl;
			cout<<"OB:"<<color.b<<endl;
			cout<<"OA:"<<color.a<<endl;
			if(color.r == pixel[0])
			{
				cout<<"At Red";
			}
			if(color.g == pixel[1])
			{
				cout<<"At Green";
			}
			if(color.b == pixel[2])
			{
				cout<<"At blue";
			}
			if(color.a == pixel[3])
			{
				cout<<"At Alpha";
			}
			cout<< "R:"<<(int)pixel[0]<<endl;
			cout<< "G:"<<(int)pixel[1]<<endl;
			cout<< "B:"<<(int)pixel[2]<<endl;
			cout<< "A:"<<(int)pixel[3]<<endl;
			
		}
		return false;
		
	}
}

#endif