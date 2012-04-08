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

#define AUTOSPEEDMAX 160
#define AUTOSPEEDMIN 80 

#define AUTODROPMAX 2500
#define AUTODROPMIN 500

#define DISTANCELEFT 5000

#define HIDEPOSITION -100,-100

using namespace std;

class AutoMountScene : public Trivial::Scene
{
public:
	AutoMountScene()
	{
		playerAtCar = -1;
		score = 0;
	}

	void preload()
	{
		myApp = Trivial::App::Instance();
		mySceneManager = Trivial::SceneManager::Instance();
		myImageManager = Trivial::ImageManager::Instance();
		myEventManager = Trivial::EventManager::Instance();
        myFontManager = Trivial::FontManager::Instance();
		myAudioManager = Trivial::AudioManager::Instance();

		myImageManager->add("backgroundImage", "data/GAmeBackground1.jpg");
		// myImageManager->add("carImage", "data/Car.png");
		myImageManager->add("playerImage", "data/player.png");
		myImageManager->add("progressBack", "data/progressBarBackground.png");
		myImageManager->add("progressRepeat", "data/progressBarRepeat.png");
		myImageManager->add("auto0", "data/black_auto.png");
		myImageManager->add("auto1", "data/blue_auto.png");
		myImageManager->add("auto2", "data/yellow_auto.png");
		myImageManager->add("playerStanding", "data/playerStanding.png");
		
		myFontManager->add("dejavu","data/DEJAVUSANS.TTF");
		
		myAudioManager->setVolume(100);
		myAudioManager->add("bgmusic","data/AutoMount.ogg", true);
		myAudioManager->setSoundPosition("bgmusic",300,300); // positioned with the explosion sprite
        myAudioManager->setSoundAttenuation("bgmusic",10); // fall off
        myAudioManager->setSoundDistance("bgmusic",100); // minimum distance till the sound is heard
        cout <<"Audio Manager"<< myAudioManager->play("bgmusic") << "\n"; // play loaded music
		myAudioManager->loop("bgmusic", true);

		addLayer("bgLayer", -1);
		backgroundImage.image("backgroundImage");
		backgroundImage.moveTo(400,300);
		add("town", backgroundImage, "bgLayer");
		backgroundBufferBackImage.image("backgroundImage");
		backgroundBufferBackImage.moveTo(backgroundImage.X()-backgroundImage.width(),300);
		add("townBuffer", backgroundBufferBackImage, "bgLayer");
		backgroundBufferFrontImage.image("backgroundImage");
		backgroundBufferFrontImage.moveTo(backgroundImage.X()+backgroundImage.width(), 300);
		add("townBuffer2", backgroundBufferFrontImage, "bgLayer");

		backgroundImage.setAcceleration(1,0);
		backgroundBufferBackImage.setAcceleration(1,0);
		backgroundBufferFrontImage.setAcceleration(1,0);

		addLayer("FrontLayer",1);
		for(int i=0;i<3;i++)
		{
			stringstream autoImageString;
			autoImageString<<"auto"<<i;
			car[i].image(autoImageString.str().c_str(),500,i);
			car[i].setAttackCost(AUTOCOST3);
			car[i].setAttackPeace(AUTOPEACE3);
			stringstream append;
			append<<"car"<<i;
			add(append.str().c_str(), car[i], "FrontLayer");
			int randomVelocity = rand() % (AUTOSPEEDMAX-AUTOSPEEDMIN+1) + AUTOSPEEDMIN;
			car[i].setVelocity(randomVelocity);
			if(!i%3)
			{
				int randomDistance = rand() % (AUTODROPMAX - AUTODROPMIN+1) + AUTODROPMIN;
				car[i].setDropAt(randomDistance);
			}
		}
		
		aPlayer.image("playerImage");
		aPlayer.moveTo(car[2].X(), car[2].Y());
		aPlayer.moveBy(0, -100);
		aPlayer.setTotalCost(TOTALPLAYERMONEY);
		aPlayer.setTotalPeace(TOTALPLAYERPEACE);
		car[2].setAttackCost(AUTOCOST1);
		car[2].setAttackPeace(AUTOPEACE1);
		car[2].add("playerObject", aPlayer);
		//car[2].affectChildren();
		

		playerAtCar = 2;
		add("playerObject", aPlayer, "FrontLayer");

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

		HUDTextScore.font("dejavu");
		HUDTextScore.text(350, 65, "Distance Left : ");
		add("hudtextScore", HUDTextScore, "FrontLayer");

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
		if(attackCostPercentage <= 0 || attackPeacePercentage <= 0)
		{
			//Game's Over bitches
			mySceneManager->setActiveScene("autoMountGameOverScene");
		}
		
		//Assigning Player to the specific Child Class..
		for(int i=0; i<3; i++)
		{
//			cout<<"Player X "<<aPlayer.X()<<" : "<<"car X "<<car[i].X()<<endl;
			if(car[i].isHit && i!=playerAtCar && aPlayer.X()+100 >= car[i].X() && aPlayer.X()-100 <= car[i].X() && car[i].X() > 50 && car[i].X() < 750)
			{
				if(playerAtCar != -1)
				{
					aPlayer.setTotalCost(aPlayer.getTotalCost() - car[playerAtCar].getTotalAttackCost());
					aPlayer.setTotalPeace(aPlayer.getTotalPeace() - car[playerAtCar].getTotalAttackPeace());
					car[playerAtCar].remove("playerObject");
					int randomVelocity = rand() % (AUTOSPEEDMAX-AUTOSPEEDMIN+1) + AUTOSPEEDMIN;
					car[playerAtCar].setVelocity(randomVelocity);
					
				}
				//Set background velocity to the current vehicle the player is travelling in.
				setBackgroundVelocity(car[i].getVelocity());

				//Set that vehicles velocity to 0 to make it stay in the screen.
				car[i].setVelocity(0);
				
				car[i].add("playerObject", aPlayer);
				car[i].affectChildren();
				playerAtCar = i;
				car[i].isHit = false;
				
				aPlayer.moveTo(car[i].X(), car[i].Y());
				aPlayer.moveBy(0, -100);
				// car[playerAtCar].setMoveToCenter();
				
			}
			else
			{
				if(i == playerAtCar)
				{
					car[i].isHit = false;
				}
			}
		}
		
		for(int i=0; i<3; i++)
		{
			//Create New Objects If Previous one are removed			
			if(car[i].X() < -200)
			{
				car[i].setAttackCost(AUTOCOST2);
				car[i].setAttackPeace(AUTOPEACE2);
				int randomVelocity = rand() % (AUTOSPEEDMAX-AUTOSPEEDMIN+1) + AUTOSPEEDMIN;
				car[i].setVelocity(randomVelocity);
				
				car[i].moveTo(1000,car[i].Y());
				if(!i%3)
				{
					int randomDistance = rand() % (AUTODROPMAX - AUTODROPMIN+1) + AUTODROPMIN;
					car[i].setDropAt(randomDistance);
				}
				car[i].resetDistance();
			}
			
		}
				
		//Check for occupied state
		if(playerAtCar != -1)
		{
			if(car[playerAtCar].getOccupiedState())
			{
				aPlayer.setTotalCost(aPlayer.getTotalCost() - car[playerAtCar].getTotalAttackCost());
				aPlayer.setTotalPeace(aPlayer.getTotalPeace() - car[playerAtCar].getTotalAttackPeace());
				car[playerAtCar].remove("playerObject");
				int randomVelocity = rand() % (AUTOSPEEDMAX-AUTOSPEEDMIN+1) + AUTOSPEEDMIN;
				car[playerAtCar].setVelocity(randomVelocity);

				add("playerObject", aPlayer);
				aPlayer.moveTo(aPlayer.X(), 550);
				setBackgroundVelocity(0);
				playerAtCar = -1;
				aPlayer.image("playerStanding");
			}
			else
			{
				aPlayer.image("playerImage");
			}
			//Update Score
			score++;
			stringstream scoreString;
			scoreString<<"Distance Left : "<<DISTANCELEFT - (int)score/10;
			HUDTextScore.text(scoreString.str());
			if(DISTANCELEFT - (int)score/10 <= 0)
			{
				//Game Won
				mySceneManager->setActiveScene("autoMountGameWinScene");				
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
	int score;
	Trivial::GUIText HUDTextScore;

	Trivial::App *myApp;
	Trivial::SceneManager *mySceneManager;
	Trivial::ImageManager *myImageManager;
	Trivial::EventManager *myEventManager;
	Trivial::FontManager *myFontManager;
	Trivial::AudioManager *myAudioManager;

};



#endif
