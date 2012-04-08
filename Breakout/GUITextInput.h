#ifndef GUITEXTINPUT_H
#define GUITEXTINPUT_H 

#include "TrivialGUIObject.h"
#include "TrivialGUIText.h"
#include "TrivialEventManager.h"
#include "TrivialSprite.h"

using namespace Trivial;

class GUITextInput : public GUIObject
{
private:
	bool _render;
	bool _inFocus;
	Sprite _bgSprite;
	GUIText _inputText;
	EventManager *_GUITextEventManager;
	
public:
	GUITextInput(bool inFocus=false);
	~GUITextInput();
	
	virtual void update(){}
	virtual void _update(const bool &render = false);
};

GUITextInput::GUITextInput(bool inFocus)
{
	_render = false;
	_inFocus = inFocus;
	_GUITextEventManager = EventManager::Instance();
	_GUITextEventManager->subscribe("keydown");
	_GUITextEventManager->subscribe("keyup");
}

void GUITextInput::_update(const bool &render)
{
	_render = render;
	GUIObject::_update(_render);
}

GUITextInput::~GUITextInput()
{
	
}
#endif