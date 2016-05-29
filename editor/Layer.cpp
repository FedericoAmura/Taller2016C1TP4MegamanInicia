//
// Created by marcos on 17/05/16.
//

#include <iostream>
#include "Layer.h"
#include "Level.h"

#define WIDTH 15

using std::runtime_error;

typedef vector<Entity*>::iterator v_iter;

Layer::Layer(unsigned int length) : length(length), width(WIDTH) {
    entities = vector<vector<Entity*> >(length, std::vector<Entity*>(width));
    for (unsigned int i = 0; i != length; ++i){
        for (unsigned int j = 0; j != width; ++j){
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
    if (x >= length || y >= width) {
        throw runtime_error("Insertion out of bounds");
    }
    uint id = prototype.id;
    if (!isEmpty(x, y)){
        return false;
    }
    Entity* new_entity = new Entity(id);
    entities[x][y] = new_entity;
    if (length - x == 1) {
        addLength();
    }
    return true;
}

bool Layer::removeEntity(uint x, uint y) {
    if (isEmpty(x, y)){
        return false;
    }
    Entity* erase = entities[x][y];
    delete erase;
    entities[x][y] = NULL;
    return true;
}

uint Layer::getEntity(uint x, uint y) {
    if (isEmpty(x, y)){
        return 0;
    } else {
        return entities[x][y]->getId();
    }
}

Layer::~Layer() {
    Entity* current_entity;
    for(unsigned int i = 0; i != length; ++i){
        for(unsigned int j = 0; j != width; ++j){
            current_entity = entities[i][j];
            if(current_entity != NULL){
                delete current_entity;
            }
        }
    }
}

Json::Value Layer::toJson() {
    Json::Value array(Json::arrayValue);
    for (uint i = 0; i != length; ++i){
        for (uint j = 0; j != width; ++j){
            if (entities[i][j] != NULL){
                Json::Value entity_value(Json::objectValue);
                entity_value["x"] = i;
                entity_value["y"] = j;
                entity_value["id"] = (uint) entities[i][j]->getId();
                array.append(entity_value);
            }
        }
    }
    return array;
}

void Layer::addLength() {
    vector<Entity*> new_row(width);
    for (uint j = 0; j != width; ++j){
        new_row[j] = NULL;
    }
    entities.push_back(new_row);
    ++length;
}






