//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_ENTITY_H
#define MEGAMAN_ENTITY_H

#include <string>
#include "Orientation.h"

using std::string;

class Entity {
public:
    Entity(size_t id) : id(id) {};
    Entity(size_t id, string orientation);
    void rotate(string direction);
    string getOrientation();
    string asJson(size_t x, size_t y, size_t indent);
private:
    size_t id;
    Orientation orientation;
};

#endif //MEGAMAN_ENTITY_H
