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
    }

    void GUIText::text(const float &x, const float &y, const string &data) {
        _data = data;
        moveTo(x,y);
        _text.SetString(data);
    }

    void GUIText::_update() {
        update();

        App::Instance()->render(_text);
    }

}
