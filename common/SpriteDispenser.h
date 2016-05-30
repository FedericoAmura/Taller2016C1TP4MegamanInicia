//
// Created by marcos on 22/05/16.
//

#ifndef MEGAMAN_SPRITEDISPENSER_H
#define MEGAMAN_SPRITEDISPENSER_H

#include <string>
#include <map>

typedef unsigned int uint;

using std::string;

class SpriteDispenser {
public:
    SpriteDispenser();
    string get(uint id);
private:
    std::map<uint, string> paths;
};


#endif //MEGAMAN_SPRITEDISPENSER_H
