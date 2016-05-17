//
// Created by marcos on 17/05/16.
//

#include "Layer.h"
#include "Level.h"

#define WIDTH 15

Layer::Layer(unsigned int length) : length(length) {
    entities = vector<vector<Entity*> >(length, std::vector<Entity*>(WIDTH));
    for (unsigned int i = 0; i != length; ++i){
        for (unsigned int j = 0; j != WIDTH; ++j){
            entities[i][j] = NULL;
        }
    }
}

bool Layer::isEmpty(unsigned int x, unsigned int y) {
    return entities[x][y] == 0;
}

bool Layer::addEntity(prototype_t prototype) {
    uint x = prototype.x;
    uint y = prototype.y;
    size_t id = prototype.id;
    string orientation = prototype.orientation;
    if (!isEmpty(x, y)){
        return false;
    }
    Entity* new_entity = new Entity(id, orientation);
    entities[x][y] = new_entity;
    return true;
}

bool Layer::removeEntity(uint x, uint y) {
    if (isEmpty(x, y)){
        return false;
    }
    Entity* erase = entities[x][y];
    entities[x].erase(entities[x].begin() + y);
    delete erase;
    return true;
}

Layer::~Layer() {
    Entity* current_entity;
    for(unsigned int i = 0; i != length; ++i){
        for(unsigned int j = 0; j != WIDTH; ++j){
            current_entity = entities[i][j];
            if(current_entity != NULL){
                delete current_entity;
            }
        }
    }
}

