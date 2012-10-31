#ifndef TRIVIALSETTINGS_H_INCLUDED
#define TRIVIALSETTINGS_H_INCLUDED

#include <map>

#include <string>

#include "TrivialObject.h"

#include "../extlibs/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace Trivial {


/**
    TrivialSettings

    get and set functions check if a file exists, if it does, they load and hold
    the setting file, the first time get, set or load is called. They then
    continue their function.

    load()
    get("name")
    set("name", "value", TYPE)

**/
class Settings : public Object {

public:
    static Settings* Instance();

    bool load(const string &settings = "trivial.xml") {
        doc = new XMLDocument();
        doc->LoadFile(settings.c_str());
        _file = settings;

        if(doc->ErrorID() == 0) { // loaded, then parse

            _ready = true;
            parse();

        } else { // not loaded, then create
            _ready = false;
            doc->InsertEndChild( doc->NewDeclaration() );
            XMLNode* element = doc->InsertEndChild( doc->NewElement( "TrivialEngine" ) );
            XMLNode* base = element->InsertFirstChild( doc->NewElement( "settings" ) );
            XMLElement* data = doc->NewElement("data");
            data->SetAttribute("type","string");
            data->SetAttribute("name", "info");
            data->SetAttribute("value","auto generated settings");
            base->InsertEndChild(data);
            doc->SaveFile(_file.c_str());
            if(doc->ErrorID() == 0 || doc->ErrorID() == XML_ERROR_FILE_NOT_FOUND) { // created then ok
                _ready = true;
                parse();
            } else { // not created
                _ready = false;
            }
        }

        return _ready;
    }

    string get(const string &name) {
        if(!_ready) {
            load();
        }

        if(!_ready) {
            return "";
        }

       if(_stringStore.count(name) == 0)
            return "";

        return _stringStore[name];

        /*
        map<string, string>::iterator it = _stringStore.find(name);
        if (it != _stringStore.end()) {
            return (*it).second;
        } else {
            return "";
        }
        */

    }

    bool set(const string &name, const string &value) {
        if(!_ready) {
            load();
        }

        if(!_ready) {
            return false;
        }

        _stringStore[name] = value;

        return true;
    }

    /**
        call save for settings to be saved!
    **/
    bool save() {
        doc = new XMLDocument();
        doc->InsertEndChild( doc->NewDeclaration() );
        XMLNode* element = doc->InsertEndChild( doc->NewElement( "TrivialEngine" ) );
        XMLNode* base = element->InsertFirstChild( doc->NewElement( "settings" ) );

        map<string, string>::iterator it;
        for ( it=_stringStore.begin() ; it != _stringStore.end(); it++ ) {
            XMLElement* data = doc->NewElement("data");
            data->SetAttribute("type","string");
            data->SetAttribute("name", (*it).first.c_str());
            data->SetAttribute("value",(*it).second.c_str());
            base->InsertEndChild(data);
        }
        doc->SaveFile(_file.c_str());

        if(doc->ErrorID() == 0 || doc->ErrorID() == XML_ERROR_FILE_NOT_FOUND) { // created then ok
            _ready = true;
            parse();
            return true;
        } else {
            return false;
        }


    }

private:
    Settings();  // Private so that it can  not be called
    ~Settings();

    Settings(Settings const&){};             // copy constructor is private
    Settings& operator=(Settings const&){};  // assignment operator is private

    static Settings* _pInstance;

    bool _ready;
    string _file;

    XMLDocument* doc;

    std::map<string, string> _stringStore;

    void parse() {
        if(_ready) {

            _stringStore.clear();

            XMLElement *base = doc->FirstChildElement()->FirstChildElement();

            if(!base->NoChildren()) {

                const char* name;
                const char* value;
                XMLElement *c = base->FirstChildElement();
                XMLElement *lc = base->LastChildElement();
                for(c;c!=lc;c=c->NextSiblingElement()) {
                    //_stringStore[c]
                    name = c->Attribute("name");
                    value = c->Attribute("value");
                    if(name != NULL && value != NULL) {
                        _stringStore[name] = value;
                        //cout << "Type: " << c->Attribute("type") << " Name: " << c->Attribute("name") << " Value: " << c->Attribute("value") << "\n";
                    }
                }
                // that last one we skipped
                name = lc->Attribute("name");
                value = lc->Attribute("value");
                if(name != NULL && value != NULL) {
                    _stringStore[name] = value;
                    //cout << "Type: " << lc->Attribute("type") << " Name: " << lc->Attribute("name") << " Value: " << lc->Attribute("value") << "\n";
                }
            }

        }
    }

};


}

#endif // TRIVIALSETTINGS_H_INCLUDED
