//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_ENTITY_H
#define MEGAMAN_ENTITY_H

#include <string>

using std::string;

class Entity {
public:
    Entity(size_t id) : id(id) {};
    size_t getId() {return id;};
private:
    size_t id;
};

#endif //MEGAMAN_ENTITY_H
