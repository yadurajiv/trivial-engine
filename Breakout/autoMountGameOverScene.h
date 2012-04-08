#ifndef AUTOMOUNTGAMEOVERSCENE_H
#define AUTOMOUNTGAMEOVERSCENE_H 

#include "TrivialEngine.h"
#include "TrivialButton.h"

class gameOverScene : public Trivial::Scene
{
public :
	gameOverScene()
	{
		
	}
	
	void preload()
	{
		myApp = Trivial::App::Instance();
		mySceneManager = Trivial::SceneManager::Instance();
		myImageManager = Trivial::ImageManager::Instance();
		myEventManager = Trivial::EventManager::Instance();
        myFontManager = Trivial::FontManager::Instance();
		myAudioManager = Trivial::AudioManager::Instance();
		
		myImageManager->add("bgImage", "data/GAmeBackground1.jpg");
		myImageManager->add("button", "data/button.png");
		myImageManager->add("buttonPressed", "data/buttonPressed.png");

		myFontManager->add("dejavu","data/DEJAVUSANS.TTF");
		
		backgroundSprite.image("bgImage");
		backgroundSprite.moveTo(400, 300);
		add("backgroundSprite", backgroundSprite);
		
		playButton.buttonWithSprite("button", "buttonPressed");
		playButton.moveTo(400, 300);
		add("playButton", playButton);
		
		gameOverText.font("dejavu");
		gameOverText.text(380, 250, "You Lose!");
		add("gameOverText", gameOverText);
		
		playText.font("dejavu");
        playText.text(380 ,285 ,"Play Again");
        add("playText", playText);
	}
	
	void update()
	{
		if(playButton._state.down)
		{
			mySceneManager->setActiveScene("autoMountScene");
		}
	}
	
	void reset()
	{
		
	}
	
	void activated()
	{
		
	}
	
	void deactivated()
	{
		
	}
	
	~gameOverScene()
	{
		
	}
	
private :
	Trivial::Sprite backgroundSprite;
	Button playButton;
	Trivial::GUIText playText;
	Trivial::GUIText gameOverText;

	Trivial::App *myApp;
	Trivial::SceneManager *mySceneManager;
	Trivial::ImageManager *myImageManager;
	Trivial::EventManager *myEventManager;
	Trivial::FontManager *myFontManager;
	Trivial::AudioManager *myAudioManager;
};
#endif