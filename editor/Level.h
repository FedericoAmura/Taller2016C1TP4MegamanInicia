//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_LEVEL_H
#define MEGAMAN_LEVEL_H

#include <vector>
#include "Entity.h"
#include "Layer.h"
//#include <../json/json.h>

using std::vector;
using std::map;

typedef unsigned int uint;

class Level {
private:
    Layer* entities;
    string background_file;

public:
    Level(string json_file);
    ~Level();
    explicit Level(uint len);
    void setBackgroundFile(string path);
    string getBackgroundFile() {return background_file;};
    uint getLength() {return entities->getLength();}
    uint getWidth() {return entities->getWidth();}
    void toJson(string file_name);
    bool addEntity(prototype_t prototype);
    bool removeEntity(uint x, uint y);
    uint getEntity(uint x, uint y);
    void enlarge() {entities->enlarge();}
    void shorten() {entities->shorten();}
};


#endif //MEGAMAN_LEVEL_H
