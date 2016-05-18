//
// Created by marcos on 15/05/16.
//

#include <fstream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "JsonReader.h"

using std::ifstream;
using std::remove;

typedef unsigned int uint;

Level JsonReader::read(string& file_name) {
    ifstream file;
    file.open(file_name.c_str());
    if(!file.is_open()) {
        //TODO: ERROR
    }
    Level level = this->levelInit(file);
    addEntities(file, level);
    return level;
}

string& removeInvalidCharacters(string& str){
    char chars[] = "},\"";
    for (unsigned int i = 0; i < strlen(chars); ++i) {
        str.erase(remove(str.begin(), str.end(), chars[i]), str.end());
    }
    return str;
}

//Gets a value that is not a JSON object
string JsonReader::getValue(string line) {
    size_t pos = line.find(":");
    string substr = line.substr(pos+1);
    return removeInvalidCharacters(substr);
}

Level JsonReader::levelInit(ifstream& file) {
    string line;
    uint length = 0;
    string background_name = "";
    string length_search = "\"length\"";
    string background_search = "\"background\"";
    while(getline(file, line)){
        if (line.find(length_search, 0) != string::npos) {
            length = (uint) atoi(getValue(line).c_str());
        } else if (line.find(background_search, 0) != string::npos){
            background_name = getValue(line);
        }
    }
    if (length == 0 || background_name == ""){
        //TODO: error
    }
    //return Level(length, background_name);//TODO comente para que compile: Nico
    return Level(length);//TODO cambiar por lo de arriba (o asi estaba)
}



void JsonReader::addEntities(ifstream& file, Level& level) {
    string line;
    file.clear();
    file.seekg(0);
    string entities_search = "\"entities\"";
    while(getline(file, line)){
        if (line.find(entities_search, 0) != string::npos) {
            break; //found "entity" key
        }
    }
    while (getline(file,line) && line.find("]") == string::npos) {
        unsigned int x;
        unsigned int y;
        int id;
        string orientation;
        x = (uint) atoi(getValue(line).c_str());
        getline(file, line);
        y = (uint) atoi(getValue(line).c_str());
        getline(file, line);
        id = atoi(getValue(line).c_str());
        getline(file, line);
        orientation = getValue(line);
	//TODO Nico: comente la 1er linea aniadi el resto aca abajo para que compile
        //level.addEntity((uint) x, (uint) y, (size_t) id, orientation);
	//a partir de aca meti yo, sacalo o saca mis comentarios, como te valla, #include "Level.h"?
	prototype_t p;
	p.x=(uint)x;
	p.y=(uint)y;
	p.id=(size_t)id;
	level.addEntity(p,orientation);
    }
}









