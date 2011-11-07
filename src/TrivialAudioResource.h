#ifndef TRIVIALAUDIORESOURCE_H_INCLUDED
#define TRIVIALAUDIORESOURCE_H_INCLUDED

#include <SFML/Audio.hpp>

#include "TrivialObject.h"
#include "TrivialEventManager.h"
#include "TrivialApp.h"

namespace Trivial {

class AudioResource : public Object {
public:
    AudioResource(const string &name, const string &path, bool streamAudio) {

        _fadeOut = false;
        _fadeIn = false;

        _streaming = streamAudio;
        if(_streaming) {

            _music = new sf::Music();

            if(_music->OpenFromFile(path)) {
                _ready = true;
                _stopped = true;
                setVolume(100);
                _eventManager = Trivial::EventManager::Instance();
                _app = Trivial::App::Instance();
            }
        } else {

            _sound = new sf::Sound();
            _soundBuffer = new sf::SoundBuffer();

            if(_soundBuffer->LoadFromFile(path)) {
                _sound->SetBuffer(*_soundBuffer);
                _ready = true;
                _stopped = true;
                setVolume(100);
                _eventManager = Trivial::EventManager::Instance();
                _app = Trivial::App::Instance();
            }
        }
    };

    void play() {
        if(_ready) {
            if(_streaming) {
                _music->Play();
            } else {
                _sound->Play();
            }

            _playing = true;
            _paused = false;
            _stopped = false;
        }
    }

    void pause() {
        if(_ready) {
            if(_streaming) {
                _music->Pause();
            } else {
                _sound->Pause();
            }

            _playing = false;
            _paused = true;
            _stopped = false;
        }
    }

    void stop() {
        if(_ready) {
            if(_streaming) {
                _music->Stop();
            } else {
                _sound->Stop();
            }

            _playing = false;
            _paused = false;
            _stopped = true;
        }
    }


    void setPosition(float x, float y, float z) {
        if(_ready) {
            if(_streaming) {
                _music->SetPosition(x, y, z);
            } else {
                _sound->SetPosition(x, y, z);
            }
        }
    }

    void positionRelative(bool b = false) {
        if(_ready) {
            if(_streaming) {
                _music->SetRelativeToListener(b);
            } else {
                _sound->SetRelativeToListener(b);
            }
        }
    }

    void attenuation(float a = 1.0) {
        if(_ready) {
            if(_streaming) {
                _music->SetAttenuation(a);
            } else {
                _sound->SetAttenuation(a);
            }
        }
    }

    void distance(float d = 1.0) {
        if(_ready) {
            if(_streaming) {
                _music->SetMinDistance(d);
            } else {
                _sound->SetMinDistance(d);
            }
        }
    }

    void loop(bool b) {
        if(_ready) {
            if(_streaming) {
                _music->SetLoop(b);
            } else {
                _sound->SetLoop(b);
            }
            _looped = b;
        }
    }

    unsigned int channels() const {
        if(_ready) {
            if(_streaming) {
                return _music->GetChannelsCount();
            } else {
                return _soundBuffer->GetChannelsCount();
            }
        }
    }

    unsigned int sampleRate() const {
        if(_ready) {
            if(_streaming) {
                return _music->GetSampleRate();
            } else {
                return _soundBuffer->GetSampleRate();
            }
        }
    }

    unsigned int  getSlider() {
        if(_ready) {
            if(_streaming) {
                return _music->GetPlayingOffset();
            } else {
                return _sound->GetPlayingOffset();
            }
        }
    }

    void setSlider(unsigned int  pos) {
        if(_ready) {
            if(_streaming) {
                _music->SetPlayingOffset(pos);
                // no way in getting offset in sfml 1.7 for the music class
                // i wonder what will happen if we use the soundstream class
                // ref: http://www.sfml-dev.org/forum/viewtopic.php?t=154&view=next&sid=b338a5541f001982eaec04b7c4cf812e
            } else {
                _sound->SetPlayingOffset(pos);
            }
        }
    }

    float getPitch() {
        if(_ready) {
            if(_streaming) {
                return _music->GetPitch();
            } else {
                return _sound->GetPitch();
            }
        }
    }

    void setPitch(float p) {
        if(_ready) {
            if(_streaming) {
                _music->SetPitch(p);
            } else {
                _sound->SetPitch(p);
            }
        }
    }

    float getVolume() {
        if(_ready) {
            if(_streaming) {
                _volume = _music->GetVolume();
            } else {
                _volume = _sound->GetVolume();
            }

            return _volume;
        }
    }

    void setVolume(float v) {
        if(_ready) {
            _volume = v;
            if(_streaming) {
                _music->SetVolume(_volume);
            } else {
                _sound->SetVolume(_volume);
            }
        }
    }

    bool ready() const { return _ready; };

    bool streaming() const { return _streaming; }

    bool playing() const { return _playing; }
    bool paused() const { return _paused; }
    bool stopped() const { return _stopped; }
    bool looped() const { return _looped; }

    void fadeOut(float t) {
        if(_ready && _playing) {

            if(!_fadeOut && !_fadeIn && _volume > 0 && t > 0) {

                _fadeOut = true;

                _timeEnd = t;
                _timeStep = 1/(_timeEnd/_volume); // ~_~ john carmack can divide by zer0
                _timeChanged = 0;

                cout << "\nFade out started! ";
                _eventManager->subscribe("update-system", this);

            }

        }
    }

    void fadeIn(float t) {
        if(_ready && !_playing) {

            if(!_fadeOut && !_fadeIn && t > 0) {

                setVolume(0);
                play();

                _fadeIn = true;

                _timeEnd = t;
                _timeStep = 1/(_timeEnd/100);
                _timeChanged = 0;

                cout << "\nFade in started! ";
                _eventManager->subscribe("update-system", this);

            }

        }
    }

    void systemEventCallback(const string &eventName) {
        if(eventName == "update-system") {
            update();
        }
    };

    void update() {
        if(_fadeOut) {
            cout << "\n" << _volume;
            if(_volume <= 0) {
                _fadeOut = false;
                stop();
                _eventManager->unsubscribe("update-system",0);
                cout << "\nFade out complete!";
            } else {
                _timeChanged += _app->frameTime();
                if(_volume > 0 && _timeChanged >= _timeStep) {
                    setVolume(_volume-1);
                    _timeChanged = 0;
                }
            }
        }

        if(_fadeIn) {
            cout << "\n" << _volume;
            if(_volume >= 100) {
                _fadeIn = false;
                _eventManager->unsubscribe("update-system",0);
                cout << "\nFade In complete!";
            } else {
                _timeChanged += _app->frameTime();
                if(_volume < 100 && _timeChanged >= _timeStep) {
                    setVolume(_volume+1);
                    _timeChanged = 0;
                }
            }
        }
    }

    void releaseResource() {
        _eventManager->unsubscribe("update-system",0);

        if(_ready) {
            if(_streaming) {
                _music->Stop();
                delete _music;
            } else {
                _sound->Stop();
                delete _sound;
                delete _soundBuffer;
            }
        }
    }

    ~AudioResource() {
        releaseResource();
    }

protected:

    sf::SoundBuffer* _soundBuffer;
    sf::Sound* _sound;
    sf::Music* _music;

// pls2 init these variables *properly* later on T_T

    bool _ready;

    bool _looped;
    bool _playing;
    bool _paused;
    bool _stopped;

    bool _streaming;

    bool _fadeOut;
    bool _fadeIn;

    float _timeStep;
    float _volStep;
    float _timeEnd;
    float _timeChanged;

    float _volume;


    Trivial::EventManager *_eventManager;
    Trivial::App *_app;

};

}

#endif // TRIVIALAUDIORESOURCE_H_INCLUDED
