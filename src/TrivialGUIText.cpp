#include <string>

#include "TrivialApp.h"
#include "TrivialFontManager.h"
#include "TrivialGUIText.h"

using namespace std;

namespace Trivial {

    void GUIText::font(const string &name) {
        _text.SetFont(*(FontManager::Instance()->get(name)));
    }

    void GUIText::text(const string &data) {
        _data = data;
        _text.SetString(data);
        _width = _text.GetGlobalBounds().Width;
        _height = _text.GetGlobalBounds().Height;
    }

    void GUIText::text(const float &x, const float &y, const string &data) {
        _data = data;
        moveTo(x,y);
        _text.SetString(data);
        _width = _text.GetGlobalBounds().Width;
        _height = _text.GetGlobalBounds().Height;
    }

    void GUIText::_update(const bool& render) {
        update();

        if(render && _visible) {
            App::Instance()->render(_text);
        }
    }

}
