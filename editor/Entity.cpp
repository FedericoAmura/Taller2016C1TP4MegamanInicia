//
// Created by marcos on 15/05/16.
//

#include <string>
#include <map>
#include "Entity.h"

using std::map;

void Entity::rotate(string direction) {
    orientation.rotate(direction);
}

string Entity::getOrientation() {
    return orientation.getOrientation();
}

Entity::Entity(size_t id, string orient) : id(id) {
    orientation = Orientation(orient);
}







