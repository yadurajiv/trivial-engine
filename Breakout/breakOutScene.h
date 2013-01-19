#ifndef MYSCENE_H_INCLUDED
#define MYSCENE_H_INCLUDED

#include <stdio.h>

#include <iostream>

#include <sstream>

#include <string>

#include "TrivialEngine.h"

#include "helpers.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

// USE THIS IF YOU REALLY NEED OpenGL!
#if defined(SFML_SYSTEM_WINDOWS)
    #include <GL/gl.h>
    #include <GL/glu.h>
#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD)
    #include <GL/gl.h>
    #include <GL/glu.h
#elif defined(SFML_SYSTEM_MACOS)
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#endif

//#include "TrivialButton.h"
//#include "TrivialMaskCollision.h"
//#include "mouseDrawing.h"
// #include "quadTreeTest.h"


using namespace std;


class breakOutScene : public Trivial::Scene {
public:

    breakOutScene() {
		isBallMoving = false;	//Set bool value to define state of the ball
    }

    void preload() {	//To preload graphics for the scene.
        cout << "ONE TIME PRELOAD!\n";

        myApp = Trivial::App::Instance();	//Creating app instance
        mySceneManager = Trivial::SceneManager::Instance();	//Creating Scene Instance
        myImageManager = Trivial::ImageManager::Instance();	//Creating Instance for Trivial Graphic Objects

		//Adding image resources;
		myImageManager->add("brick", "data/element_yellow_rectangle_glossy.png");
		myImageManager->add("paddle","data/paddleBlu.png");
		myImageManager->add("ball", "data/ballBlue.png");
		myImageManager->add("button", "data/button.png");
		myImageManager->add("buttonPressed", "data/buttonPressed.png");
		myImageManager->add("buttonHover", "data/buttonHover.png");
		myImageManager->add("animatedButton", "data/vegeta.png");
		//myImageManager->add("maskedSprite","data/obj1.png");

        myImageManager->add("blob","../test/data/blob.png");

        blob.image("blob");
        blob.setAngularAcceleration(12);
        blob.setAlpha(64);
        blob.moveBy(400,300);
        blob.setBlendMode("alpha");
        add("blob",blob);

		//To load all the Bricks
		for(int i = 0; i < 4; ++i)
		{
			for(int j = 0; j < 12; ++j)
			{
				stringstream append;
				append<<"brickImage"<<i<<j;
				brickSprite[i][j].image("brick");
				add(append.str().c_str(), brickSprite[i][j]);
				pos brickPosition;
				brickPosition.x = 48+(64*j + 1);
				brickPosition.y = 32+(32*i + 1);
				brickSprite[i][j].setPositionBy(brickPosition);
			}
		}

		paddleSprite.image("paddle");
		add("paddleImage", paddleSprite);
		pos paddlePosition;
		paddlePosition.x = 400;
		paddlePosition.y = 582;
		paddleSprite.setPosition(paddlePosition);

		ballSprite.image("ball");
		add("ballImage", ballSprite);
		ballPosition.x = 400;
		ballPosition.y = 555;
		ballSprite.setAngularAcceleration(20);
		ballSprite.setPosition(ballPosition);

		/*aButton2.buttonWithAnimatedSprite("animatedButton", 150, 40);
		aButton2.buttonUpAddAnimation("buttonAnimate", 0, 12, 10);
		aButton2.buttonDownAddAnimation("buttonAnimate2", 12, 14, 10);
		aButton2.buttonHoverAddAnimation("buttonAnimate3", 1, 1, 10);

		aButton.buttonWithSprite("button", "buttonPressed", "buttonHover");

		add("buttonDisplay", aButton);
		add("vegetaButtonDisplay",aButton2);
		aButton.moveTo(400,300);
		aButton2.moveTo(200,300);

		mc.image("maskedSprite", "maskedSprite");
		add("mask", mc);
		cout<<mc.isMaskAt(0,0);*/


    }

    void reset() {
        /* key state flags */

		isBallMoving = false;

        // look at object needs to be rewritten or given to scene
        defaultCamera.lookAt(400, 300);

        myApp->setClearColor(8,31,70,255);

////        myAudioManager->earPosition(camera.getCenterX(), camera.getCenterY());
    }

    /* the event call back is called by the event manager */

    void update() {

        if(!_activated)
            return;

		if(!isBallMoving)
		{
			if(paddleSprite.getKeyUpState())
			{
				isBallMoving = true;
				ballSprite.setLastCollidePlace(ballPosition);
				ballPosition.x -= 1;
				ballPosition.y -= 2;
				ballSprite.setRelativeToPaddle(-1);
				ballSprite.setPosition(ballPosition);
			}
		}

		if(isBallMoving)
		{
			//Collision Check for bricks;
			GLubyte* pixel = new GLubyte[4];
			glReadPixels(ballSprite.getPosition().x-20, 600-ballSprite.getPosition().y-50, 1, 1, GL_RGBA, GL_UNSIGNED_INT, pixel);
			/** count eats up a lot of time **/
			/*
			cout<<"RED : "<<(int)pixel[0]<<endl;
			cout<<"GREEN : "<<(int)pixel[1]<<endl;
			cout<<"BLUE : "<<(int)pixel[2]<<endl;
			cout<<"Alpha : "<<(int)pixel[3]<<endl;
            */
			for(int i = 0; i < 4; ++i)
			{
				for(int j = 0; j < 12; ++j)
				{
					if(ballSprite.getPosition().x >= brickSprite[i][j].getPosition().x-35 && ballSprite.getPosition().x <= brickSprite[i][j].getPosition().x+35)
					{
						if(ballSprite.getPosition().y >= brickSprite[i][j].getPosition().y-18 && ballSprite.getPosition().y <= brickSprite[i][j].getPosition().y+18)
						{
							stringstream append;
							append<<"brickImage"<<i<<j;
							pos tempPos;
							tempPos.x = -40;
							tempPos.y = -40;
							brickSprite[i][j].setPosition(tempPos);
							remove(append.str().c_str());
							ballSprite.setBallMotionDirection(false);
						}
					}
				}
			}

			//Collision check for paddle;
			if(ballSprite.getPosition().x >= paddleSprite.getPosition().x-35 && ballSprite.getPosition().x <= paddleSprite.getPosition().x+35)
			{
				if(ballSprite.getPosition().y >= paddleSprite.getPosition().y-18 && ballSprite.getPosition().y <= paddleSprite.getPosition().y+18)
				{
					int movFactor = (paddleSprite.getPosition().x - ballSprite.getPosition().x) / 7;
					if(movFactor >= 0)
						movFactor+=1;
					else movFactor-=1;
					ballSprite.setBallMotionDirection(true);
					ballSprite.setRelativeToPaddle(-movFactor);
				}
			}

			//Collision check for wall;
			int movFactor = ballSprite.getRelativeToPaddle();
			if(ballSprite.getPosition().x >= 800 || ballSprite.getPosition().x <= 0)
			{
				movFactor = -movFactor;
			}

			if(ballSprite.getPosition().y >= 585)
			{
				ballSprite.setBallMotionDirection(false);
			}

			if(ballSprite.getPosition().y <= 5)
			{
				reset();
			}

			//Ball Motion
			if(ballSprite.getBallMotionDirection())
			{
				ballPosition.x += movFactor;
				ballPosition.y -= 2;
				ballSprite.setPosition(ballPosition);
			}
			else
			{
				ballPosition.x += movFactor;
				ballPosition.y += 2;
				ballSprite.setPosition(ballPosition);
			}
			ballSprite.setRelativeToPaddle(movFactor);
		}

    }

    void deactivated() {
        _activated = false;
        cout << "\nmyScene deactivated" << endl;
    }

    void activated() {
        _activated = true;
        cout << "\nmyScene activated!" << endl;

        reset();
    }

    ~breakOutScene() {
    }


private:

    Trivial::Sprite blob;


    bool _activated;
	bool isBallMoving;

	brick brickSprite[4][12];
	paddle paddleSprite;
	ball ballSprite;
	pos ballPosition;
	/*Button aButton;
	Button aButton2;
	Trivial::AnimatedSprite explosion, explosion2;
	MaskCollision mc;*/



    /**
        moved inside class since sfml has its own global variables and they might
        not be initialized before main, which causes a segfault.
        http://www.sfml-dev.org/forum/viewtopic.php?p=29824#29824
    **/
    Trivial::App *myApp;
    Trivial::SceneManager *mySceneManager;
    Trivial::ImageManager *myImageManager;

};

#endif // MYSCENE_H_INCLUDED
