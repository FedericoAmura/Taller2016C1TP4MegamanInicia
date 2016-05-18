//
// Created by marcos on 15/05/16.
//

#include <string>
#include <map>
#include <sstream>
#include "Entity.h"

using std::map;
using std::stringstream;

void Entity::rotate(string direction) {
    orientation.rotate(direction);
}

string Entity::getOrientation() {
    return orientation.getOrientation();
}

Entity::Entity(size_t id, string orient) : id(id) {
    orientation = Orientation(orient);
}

string indentate(size_t indent){
    stringstream s;
    for(unsigned int i = 0; i != indent; ++i){
        s << "\t";
    }
    return s.str();
}








