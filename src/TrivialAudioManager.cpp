#include <iostream>

#include "TrivialAudioResource.h"
#include "TrivialAudioManager.h"

using namespace std;

namespace Trivial {

AudioManager* AudioManager::_pInstance;

AudioManager::AudioManager() {
}

AudioManager::~AudioManager() {
    /** safely removing objects from scene **/
    releaseResources();
}

void AudioManager::releaseResources() {
    map<string, AudioResource*>::iterator it;
    for ( it=_sounds.begin() ; it != _sounds.end(); it++ ) {
        (*it).second->stop();
        delete (*it).second;
    }
}

AudioManager* AudioManager::Instance()
{
   if (!_pInstance)   // Only allow one instance of class to be generated.
      _pInstance = new AudioManager;

   return _pInstance;
}

}
