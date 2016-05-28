//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_ENTITY_H
#define MEGAMAN_ENTITY_H

#include <string>

using std::string;

class Entity {
public:
    Entity(uint id) : id(id) {}
    uint getId() {return id;}
private:
    uint id;
};

#endif //MEGAMAN_ENTITY_H
