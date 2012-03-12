#ifndef AUTOMOUNTSCENE_H
#define AUTOMOUNTSCENE_H 

#include "TrivialEngine.h"
#include "cars.h"
#include "bus.h"
#include "autoCab.h"
#include <iostream>
#include <sstream>

using namespace std;

class AutoMountScene : public Trivial::Scene
{
public:
	AutoMountScene()
	{
		
	}
	
	void preload()
	{
		myApp = Trivial::App::Instance();
		mySceneManager = Trivial::SceneManager::Instance();
		myImageManager = Trivial::ImageManager::Instance();
		myEventManager = Trivial::EventManager::Instance();
		
		myImageManager->add("backgroundImage", "data/GAmeBackground1.jpg");
		myImageManager->add("carImage", "data/Car.png");
		
		addLayer("bgLayer", -1);
		backgroundImage.image("backgroundImage");
		backgroundImage.moveTo(400,300);
		add("town", backgroundImage, "bgLayer");
		backgroundBufferBackImage.image("backgroundImage");
		backgroundBufferBackImage.moveTo(backgroundImage.X()-1366,300);
		add("townBuffer", backgroundBufferBackImage, "bgLayer");
		backgroundBufferFrontImage.image("backgroundImage");
		backgroundBufferFrontImage.moveTo(backgroundImage.X()+1366, 300);
		add("townBuffer2", backgroundBufferFrontImage, "bgLayer");
		
		backgroundImage.setAcceleration(1,0);
		backgroundBufferBackImage.setAcceleration(1,0);
		backgroundBufferFrontImage.setAcceleration(1,0);
		
		addLayer("FrontLayer",1);
		for(int i=0;i<3;i++)
		{
			car[i].image("carImage",500,i);
			stringstream append;
			append<<"car"<<i;
			cout<<"WHAT ADDS : "<<add(append.str().c_str(), car[i], "FrontLayer");
			int randomVelocity = rand() % (80-20+1) + 20;
			car[i].setVelocity(randomVelocity);
		}
		
		//Set background velocity to the current vehicle the player is travelling in.
		setBackgroundVelocity(car[2].getVelocity());
		
		//Set that vehicles velocity to 0 to make it stay in the screen.
		car[2].setVelocity(0);
	}
	
	void setBackgroundVelocity(int aVelocity)
	{
		backgroundImage.setMaxVelocity(aVelocity, 0);
		backgroundBufferFrontImage.setMaxVelocity(aVelocity, 0);
		backgroundBufferBackImage.setMaxVelocity(aVelocity, 0);
	}
	
	void reset()
	{
		
	}
	
	void update()
	{
		if(backgroundBufferFrontImage.X() > 1366+283){
			backgroundBufferFrontImage.moveTo(backgroundBufferBackImage.X()-1366, 300);
		}
		if(backgroundImage.X() > 1366+283){
			backgroundImage.moveTo(backgroundBufferFrontImage.X()-1366, 300);
		}
		if(backgroundBufferBackImage.X() > 1366+283)
		{
			backgroundBufferBackImage.moveTo(backgroundImage.X()-1366, 300);
		}
		fflush(stdout);
	}
	
	void deactivated()
	{
		
	}
	
	void activated()
	{
		
	}
	
	~AutoMountScene()
	{
		
	}
	
	
private:
	Trivial::Sprite backgroundImage;
	Trivial::Sprite backgroundBufferBackImage;
	Trivial::Sprite backgroundBufferFrontImage;
	Car car[3];
	
	Trivial::App *myApp;
	Trivial::SceneManager *mySceneManager;
	Trivial::ImageManager *myImageManager;
	Trivial::EventManager *myEventManager;
	
};
	


#endif