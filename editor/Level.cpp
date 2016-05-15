//
// Created by marcos on 15/05/16.
//

#include "Level.h"

#define WIDTH 15

Level::Level(unsigned int length) {
    entities = vector<vector<Entity*> >(length, std::vector<Entity*>(WIDTH));
    for (unsigned int i = 0; i != length; ++i){
        for (unsigned int j = 0; j != WIDTH; ++j){
            entities[i][j] = NULL;
        }
    }
}

bool Level::isEmpty(unsigned int x, unsigned int y) {
    return entities[x][y] == NULL;
}

bool Level::addEntity(uint x, uint y, size_t id, string orientation) {
    if (!isEmpty(x, y)){
        return false;
    }
    Entity* new_entity = new Entity(id, orientation);
    entities[x][y] = new_entity;
    return true;
}

bool Level::removeEntity(uint x, uint y) {
    if (isEmpty(x, y)){
        return false;
    }
    Entity* erase = entities[x][y];
    entities[x].erase(entities[x].begin() + y);
    delete erase;
    return true;
}







