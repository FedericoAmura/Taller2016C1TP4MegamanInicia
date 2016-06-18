//
// Created by marcos on 22/05/16.
//

#ifndef MEGAMAN_SPRITEDISPENSER_H
#define MEGAMAN_SPRITEDISPENSER_H

#include <map>
#include <string>

#include "Thread.h"

typedef unsigned int uint;

using std::string;

class SpriteDispenser {
public:
    SpriteDispenser();
    string get(uint id, uint offset = 0);
    double getHeight(uint id);
    double getWidth(uint id);
private:
    std::map<uint, string> paths;
    std::map<uint, double> heigths;
    std::map<uint, double> widths;
    double tileSize;
};


#endif //MEGAMAN_SPRITEDISPENSER_H
