#ifndef AUTOMOUNTSCENE_H
#define AUTOMOUNTSCENE_H

#include "TrivialEngine.h"
#include "cars.h"
#include "bus.h"
#include "autoCab.h"
#include "Player.h"
#include "TrivialProgressBar.h"
#include <iostream>
#include <sstream>

#define AUTOCOST1 0.4
#define AUTOPEACE1 0.5

#define AUTOCOST2 0.5
#define AUTOPEACE2 0.3

#define AUTOCOST3 0.7
#define AUTOPEACE3 0.2

#define TOTALPLAYERMONEY 500
#define TOTALPLAYERPEACE 500

using namespace std;

class AutoMountScene : public Trivial::Scene
{
public:
	AutoMountScene()
	{
		playerAtCar = -1;
	}

	void preload()
	{
		myApp = Trivial::App::Instance();
		mySceneManager = Trivial::SceneManager::Instance();
		myImageManager = Trivial::ImageManager::Instance();
		myEventManager = Trivial::EventManager::Instance();
        myFontManager = Trivial::FontManager::Instance();

		myImageManager->add("backgroundImage", "data/GAmeBackground1.jpg");
		myImageManager->add("carImage", "data/Car.png");
		myImageManager->add("playerImage", "data/player.png");
		myImageManager->add("progressBack", "data/progressBarBackground.png");
		myImageManager->add("progressRepeat", "data/progressBarRepeat.png");
		
		myFontManager->add("dejavu","data/DEJAVUSANS.TTF");

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
			car[i].setAttackCost(AUTOCOST3);
			car[i].setAttackPeace(AUTOPEACE3);
			stringstream append;
			append<<"car"<<i;
			cout<<"WHAT ADDS : "<<add(append.str().c_str(), car[i], "FrontLayer");
			int randomVelocity = rand() % (80-20+1) + 20;
			car[i].setVelocity(randomVelocity);
		}
		
		aPlayer.image("playerImage");
		aPlayer.moveTo(car[2].X(), car[2].Y());
		aPlayer.moveBy(0, -100);
		aPlayer.setTotalCost(TOTALPLAYERMONEY);
		aPlayer.setTotalPeace(TOTALPLAYERPEACE);
		car[2].setAttackCost(AUTOCOST1);
		car[2].setAttackPeace(AUTOPEACE1);
		car[2].add("playerObject", aPlayer);
		car[2].affectChildren();
		playerAtCar = 2;
		// aPlayer.moveBy(0, 100);
		// add("playerObject", aPlayer, "FrontLayer");

		//Set background velocity to the current vehicle the player is travelling in.
		setBackgroundVelocity(car[2].getVelocity());

		//Set that vehicles velocity to 0 to make it stay in the screen.
		car[2].setVelocity(0);
		
		costBar.moveTo(230,50);
		costBar.init("progressBack", "progressRepeat");
		add("costBar", costBar, "FrontLayer");
		
		peaceBar.moveTo(230,100);
		peaceBar.init("progressBack", "progressRepeat");
		add("peaceBar", peaceBar, "FrontLayer");
		
		
		HUDTextCost.font("dejavu");
        HUDTextCost.text(10,40,"-($_$)- Meter");
        add("hudtextCost", HUDTextCost, "FrontLayer");

		HUDTextPeace.font("dejavu");
        HUDTextPeace.text(10,90,"V(*_*)V Meter");
        add("hudtextPeace", HUDTextPeace, "FrontLayer");
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
		
		//Setting Progress Bars right
		float attackCostPercentage = (aPlayer.getTotalCost() - car[playerAtCar].getTotalAttackCost())/5;
		float attackPeacePercentage = (aPlayer.getTotalPeace() - car[playerAtCar].getTotalAttackPeace())/5;
		
		
		costBar.setPercentValue(attackCostPercentage);
		peaceBar.setPercentValue(attackPeacePercentage);
		
		//Check Game Over state
		if(attackCostPercentage == 0 || attackPeacePercentage == 0)
		{
			//Game's Over bitches
		}
		
		//Assigning Player to the specific Child Class..
		for(int i=0; i<3; i++)
		{
			if(car[i].isHit && i!=playerAtCar)
			{
				//Set background velocity to the current vehicle the player is travelling in.
				setBackgroundVelocity(car[i].getVelocity());

				//Set that vehicles velocity to 0 to make it stay in the screen.
				car[i].setVelocity(0);
				aPlayer.setTotalCost(aPlayer.getTotalCost() - car[playerAtCar].getTotalAttackCost());
				aPlayer.setTotalPeace(aPlayer.getTotalPeace() - car[playerAtCar].getTotalAttackPeace());
				car[playerAtCar].remove("playerObject");
				int randomVelocity = rand() % (80-20+1) + 20;
				car[playerAtCar].setVelocity(randomVelocity);
				car[i].add("playerObject", aPlayer);
				playerAtCar = i;
				car[i].isHit = false;
				
				aPlayer.moveTo(car[i].X(), car[i].Y());
				aPlayer.moveBy(0, -100);
			}
			else
			{
				if(i == playerAtCar)
				{
					car[i].isHit = false;
				}
			}
		}
		
		//Create New Objects If Previous one are removed
		for(int i=0; i<3; i++)
		{
			if(car[i].X() < -200)
			{
				car[i].setAttackCost(AUTOCOST2);
				car[i].setAttackPeace(AUTOPEACE2);
				int randomVelocity = rand() % (80-20+1) + 20;
				car[i].setVelocity(randomVelocity);
				
				car[i].moveTo(1000,car[i].Y());
			}
		}
				
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
	AutoCab car[3];
	Player aPlayer;
	ProgressBar costBar;
	ProgressBar peaceBar;
	int playerAtCar;
	Trivial::GUIText HUDTextCost;
	Trivial::GUIText HUDTextPeace;

	Trivial::App *myApp;
	Trivial::SceneManager *mySceneManager;
	Trivial::ImageManager *myImageManager;
	Trivial::EventManager *myEventManager;
	Trivial::FontManager *myFontManager;

};



#endif
