/**
 * @file    TrivialButton.h
 * @author  Team Trivial <team@trivialengine.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * -- TBD --
 *
 * @section DESCRIPTION
 *
 * Contains the Button Class.
 */

#ifndef TRIVIALBUTTON_H_INCLUDED
#define TRIVIALBUTTON_H_INCLUDED

#include "TrivialGUIObject.h"
#include "TrivialSprite.h"
#include "TrivialEventManager.h"
#include <sstream>

namespace Trivial{	
	/**
	 *	A GUIObject Button class, to create Buttons.
	 */
	class Button : public GUIObject
	{
	private:
		/*! Structure for current mouse state on the button. */
		struct _mouseState
		{
			bool down; /*!< to check the mouse button down state on the button. */
			bool up; /*!< to check the mouse button up state on the button. */
			bool hover; /*!< to check the mouse button over state on the button. */
		};
		bool isMaskAvailable; /*!< bool variable to make the button detect mask collision for the Sprite */
		bool isAnimated; /*!< bool variable to check if the button is Animated or not */
		Trivial::Sprite _button; /*!< Holds the Sprite object for the button */
		stringstream _buttonStateImages[3]; /*!< Uses string parameter of the image names passed for different states @see _mouseState */
		AnimatedSprite _animatedButton; /*!< Holds the AnimatedSprite object for the button */
		EventManager *myEventManager; /*!< Object to subscribe to the mouse events for the button */
	public:
		 /*! Generates the mouse state on the current button. 
		  * @see _mouseState
		  *
		  * Sample Usage : To check mouse button down state of a button
		  * @code Trivial::Button aButton;
          * 	if(aButton.state.down){} 
    	  *	@endcode
		 */
		_mouseState state;
		
		/**
		* Constructor for the class.
		*/
		Button();
		
		/**
		* Destructor for the class.
		*/
		~Button();
		
		/**
		*	This function initializes the Button object with Sprites.
		*	@param buttonUpState - is a string key of the image for button when it is not clicked (Mouse Up State of button).
		*	@param buttonDownState - is a string key of the image for button when it is clicked (Mouse Down State of button).
		*	@param buttonHoverState - is a string key of the image for button when mouse is over it (Mouse Hover State of button)
		*	
		*	@see ImageManager
		*	@see Sprite 
		*/
		void buttonWithSprite(const string &buttonUpState, const string &buttonDownState, const string &buttonHoverState);
		
		/**
		*	This function initializes the Button object with AnimatedSprites.
		*	@param name - is a string key of the animation to be loaded.
		*	@param colWidth - is the width of the cell in the atlas file.
		*	@param colHeight - is the height of the cell in the atlas file.
		*	
		*	@see AnimatedSprite
		*	@see Animation 
		*/
		void buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight);
		
		/**
		*	This function sets the Animation for button when it is not clicked (Mouse Up State of button)
		*	@param name - us a string key of the animation to be played.
		*	@param startFrame - is the number of the frame from where the animation is to be started.
		*	@param endFrame - is the number of the frame to where the animation is to be played.
		*	@param frameRate - is the frame rate at which the animation is to be played.
		*
		*	@see AnimatedSprite
		*	@see Animation	
		*/
		void buttonUpAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
		
		/**
		*	This function sets the Animation for button when it is clicked (Mouse Down State of button)
		*	@param name - us a string key of the animation to be played.
		*	@param startFrame - is the number of the frame from where the animation is to be started.
		*	@param endFrame - is the number of the frame to where the animation is to be played.
		*	@param frameRate - is the frame rate at which the animation is to be played.	
		*
		*	@see AnimatedSprite
		*	@see Animation	
		*/
		void buttonDownAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
		
		/**
		*	This function sets the Animation for button when mouse is over the button. (Mouse Hover State of button)
		*	@param name - us a string key of the animation to be played.
		*	@param startFrame - is the number of the frame from where the animation is to be started.
		*	@param endFrame - is the number of the frame to where the animation is to be played.
		*	@param frameRate - is the frame rate at which the animation is to be played.	
		*
		*	@see AnimatedSprite
		*	@see Animation	
		*/
		void buttonHoverAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate);
		
		/**
		*	This function sets if the mask collision is to be used for the button.
		*	@param bValue - is the boolean value to set Mask collision to true/false.
		*
		*	@see Sprite::pointOverlap
		*/
		void setIsMask(bool bValue);
		
		/**
		*	This is an update function for the button which updates the Button according to its state and calls the parent class.
		*/
		virtual void _update();
		
		/**
		*	This a virtual update function, so that classes derived from Button can get their update state.
		*/
		virtual void update();

		/**
		*	This function is a callback function for any mouse event.
		*	 @param e - is a string value passed back to the callback by the EventManager
		*	
		*	@see EventManager
		*/
		void mouseEventCallBack(const TrivialMouseEvent &e);

		/**
		*	This function is called when the mouse is in the button down state.
		*/
		void buttonDown();
		
		/**
		*	This function is called when the mouse is in the button up state.
		*/
		void buttonUp();
		
		/**
		*	This function is called when the mouse is in the button hover state.
		*/
		void buttonHover();

	};

	Button::Button()
	{
		isMaskAvailable = false;
		isAnimated = false;

		state.up = true;
		state.down = false;
		state.hover = false;

		myEventManager = EventManager::Instance();
		myEventManager->subscribe("update-mouse", this);
		myEventManager->subscribe("left-buttondown-mouse", this);
		myEventManager->subscribe("left-buttonup-mouse", this);
	}

	Button::~Button()
	{

	}

	void Button::mouseEventCallBack(const TrivialMouseEvent &e)
	{
		if((!isAnimated && _button.pointOverlap(e.pos.x, e.pos.y, isMaskAvailable)) || (isAnimated && _animatedButton.pointOverlap(e.pos.x, e.pos.y, isMaskAvailable)))
		{
			if(e.eventName == "left-buttondown-mouse")
			{
				state.up = false;
				state.down = true;
				state.hover = false;
			}
			else
			if(e.eventName == "left-buttonup-mouse")
			{
				state.down = false;
				state.up = true;
				state.hover = false;
			}
			else
			if(e.eventName == "update-mouse")
			{
				if(!e.lButton){
					state.hover = true;
				}
			}
		}
		else
		{
			state.hover = false;
		}
	}

	void Button::_update()
	{
		if(state.down)
		{
			buttonDown();
		}
		if(state.up){
			buttonUp();
		}
		if(state.hover)
		{
			buttonHover();
		}
		GUIObject::_update(true);
	}

	void Button::update()
	{
		
	}

	void Button::buttonWithSprite(const string &buttonUpState, const string &buttonDownState = "", const string &buttonHoverState = "")
	{
		_button.image(buttonUpState);
		add("TrivialButton",_button);
		_buttonStateImages[0]<<buttonUpState;
		if(buttonDownState != "") _buttonStateImages[1]<<buttonDownState;
		else _buttonStateImages[1]<<buttonUpState;
		if(buttonHoverState != "") _buttonStateImages[2]<<buttonHoverState;
		else _buttonStateImages[2]<<buttonUpState;

	}

	void Button::buttonWithAnimatedSprite(const string &name, const float &colWidth, const float &colHeight)
	{
		_animatedButton.image(name, colWidth, colHeight);
		add("TrivialAnimatedButton",_animatedButton);
		isAnimated = true;
	}

	void Button::buttonUpAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
	{
		_animatedButton.addAnimation(name, startFrame, endFrame, frameRate);
		_buttonStateImages[0]<<name;
		_animatedButton.play(name);
	}

	void Button::buttonDownAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
	{
		_animatedButton.addAnimation(name, startFrame, endFrame, frameRate);
		_buttonStateImages[1]<<name;
	}

	void Button::buttonHoverAddAnimation(const string &name, const int &startFrame, const int &endFrame, const int &frameRate)
	{
		_animatedButton.addAnimation(name, startFrame, endFrame, frameRate);
		_buttonStateImages[2]<<name;
	}

	void Button::setIsMask(bool bValue)
	{
		isMaskAvailable = bValue;
	}

	void Button::buttonDown()
	{
		if(isAnimated == false)
		{
			_button.image(_buttonStateImages[1].str().c_str());
		}
		else
		{
			_animatedButton.play(_buttonStateImages[1].str().c_str());
		}
	}

	void Button::buttonUp()
	{
		if(isAnimated == false)
		{
			_button.image(_buttonStateImages[0].str().c_str());
		}
		else
		{
			_animatedButton.play(_buttonStateImages[0].str().c_str());
		}

	}

	void Button::buttonHover()
	{
		if(isAnimated == false)
		{
			_button.image(_buttonStateImages[2].str().c_str());
		}
		else
		{
			_animatedButton.play(_buttonStateImages[2].str().c_str());
		}
	}
	
}
#endif // TRIVIALBUTTON_H_INCLUDED