#include <iostream>

#include "TrivialSettings.h"

namespace Trivial {

Settings* Settings::_pInstance;

Settings::Settings() {
}

Settings* Settings::Instance()
{
   if (!_pInstance)   // Only allow one instance of class to be generated.
      _pInstance = new Settings;

   return _pInstance;
}


Settings::~Settings() {
}

}
