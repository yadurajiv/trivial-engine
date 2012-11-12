#ifndef TRIVIALAUDIOMANAGER_H_INCLUDED
#define TRIVIALAUDIOMANAGER_H_INCLUDED

#include <map>
#include <iostream>

#include "TrivialObject.h"
#include "TrivialAudioResource.h"

using namespace std;

namespace Trivial {


class AudioManager : public Object {
public:
    static AudioManager* Instance();

    void add(const string &name, const string &path, bool streamAudio) {

        if(streamAudio) {
            addMusic(name,path);
        } else {
            addSound(name,path);
        }
    };

    void addMusic(const string &name, const string &path) {
        _sounds[name] = new AudioResource(name, path, true);
    };

    void addSound(const string &name, const string &path) {
        _sounds[name] = new AudioResource(name, path, false);
    };

    bool play(const string &name) {
        // If layer not found, return
        if (_sounds.count(name) == 0) {
            return false;
        }

        _sounds[name]->play();

        return true;
    }

    bool ready(const string &name) {
        if (_sounds.count(name) == 0) {
            return false;
        }

        return _sounds[name]->ready();
    }

    void earPosition(float x, float y) {
        sf::Listener::setPosition(x, 0, y);
    };

    void earDirection(float x, float y) {
        sf::Listener::setDirection(x, 0, y); // changed to setTarget
//        sf::Listener::SetTarget(x, 0, y); // changed back to SetDirection!
    }

    void setVolume(float v) {
        sf::Listener::setGlobalVolume(v);
    }

    float getVolume() const {
        return sf::Listener::getGlobalVolume();
    }

    void setSoundPosition(const string &name, float x, float y) {
        if (_sounds.count(name) != 0) {
            _sounds[name]->setPosition(x, 50, y);
        }
    }

    void setSoundPositionRelative(const string &name, bool b) {
        if (_sounds.count(name) != 0) {
            _sounds[name]->positionRelative(b);
        }
    }

    void setSoundAttenuation(const string &name, float a = 1.0) {
        if (_sounds.count(name) != 0) {
            _sounds[name]->attenuation(a);
        }
    }

    void setSoundDistance(const string &name, float d = 1.0) {
        if (_sounds.count(name) != 0) {
            _sounds[name]->distance(d);
        }
    }

    void fadeOut(const string &name, unsigned int t) {
        if (_sounds.count(name) != 0) {
            _sounds[name]->fadeOut(t*1000);
        }
    }

    void fadeIn(const string &name, unsigned int t) {
        if (_sounds.count(name) != 0) {
            _sounds[name]->fadeIn(t*1000);
        }
    }

    const bool playing(const string &name) {
        if (_sounds.count(name) != 0) {
           return _sounds[name]->playing();
        }
    }

	void loop(const string &name, bool value){
		if(_sounds.count(name) != 0){
			_sounds[name]->loop(value);
		}
	}

	unsigned int getSampleRate(const string &name) {
        if(_sounds.count(name) != 0){
			return _sounds[name]->sampleRate();
		}
	}

	const Int16 * getSamples(const string &name) {
        if(_sounds.count(name) != 0) {
            return _sounds[name]->samples();
        }
	}

	unsigned int getChannelCount(const string &name) {
        if(_sounds.count(name) != 0) {
            return _sounds[name]->channels();
        }
	}

	float getSlider(const string &name) {
        if(_sounds.count(name) != 0) {
            sf::Time t;
            t = _sounds[name]->getSlider();
            return t.asMilliseconds();
        }
	}

    void releaseResources();

private:
    AudioManager();  // Private so that it can  not be called
    ~AudioManager();

    AudioManager(AudioManager const&){};             // copy constructor is private
    AudioManager& operator=(AudioManager const&){};  // assignment operator is private

    static AudioManager* _pInstance;

    map<string, AudioResource*> _sounds;

};

}


#endif // TRIVIALAUDIOMANAGER_H_INCLUDED
