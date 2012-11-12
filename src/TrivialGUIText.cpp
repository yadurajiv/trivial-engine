#include <string>

#include "TrivialApp.h"
#include "TrivialFontManager.h"
#include "TrivialGUIText.h"

using namespace std;

namespace Trivial {

    void GUIText::font(const string &name) {
        _text.setFont(*(FontManager::Instance()->get(name)));
    }

    void GUIText::text(const string &data) {
        _data = data;
        _text.setString(data);
        _width = _text.getGlobalBounds().width;
        _height = _text.getGlobalBounds().height;
    }

    void GUIText::text(const float &x, const float &y, const string &data) {
        _data = data;
        moveTo(x,y);
        _text.setString(data);
        _width = _text.getGlobalBounds().width;
        _height = _text.getGlobalBounds().height;
    }

    void GUIText::_update(const bool& render) {
        update();

        if(render && _visible) {
            App::Instance()->render(_text, _renderStates);
        }
    }

}
