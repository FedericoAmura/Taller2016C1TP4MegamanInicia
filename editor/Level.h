//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_LEVEL_H
#define MEGAMAN_LEVEL_H

#include <vector>
#include "Entity.h"

using std::vector;

typedef unsigned int uint;

class Level {
public:
    Level(unsigned int length);
    bool addEntity(uint x, uint y, size_t id, string orientation = "up");
    bool removeEntity(uint x, uint y);
private:
    bool isEmpty(uint x, uint y);
    vector<vector <Entity*> > entities;
};


#endif //MEGAMAN_LEVEL_H
