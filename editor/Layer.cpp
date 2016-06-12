//
// Created by marcos on 17/05/16.
//

#include <iostream>
#include "Layer.h"
#include "Level.h"

#define BOSS_FLOOR 1100
#define BOSS_CEILING 2000

#define WIDTH 15

using std::runtime_error;

typedef vector<Entity*>::iterator v_iter;

Layer::Layer(unsigned int length) {
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
    if (x >= getLength() || y >= getWidth()) {
        throw runtime_error("Insertion out of bounds");
    }
    uint id = prototype.id;
    if (!isEmpty(x, y)){
        return false;
    }
    Entity* new_entity = new Entity(id);
    entities[x][y] = new_entity;
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
    for(unsigned int i = 0; i != getLength(); ++i){
        for(unsigned int j = 0; j != getWidth(); ++j){
            current_entity = entities[i][j];
            if(current_entity != NULL){
                delete current_entity;
            }
        }
    }
}

Json::Value Layer::toJson() {
    Json::Value array(Json::arrayValue);
    for (uint i = 0; i != getLength(); ++i){
        for (uint j = 0; j != getWidth(); ++j){
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

uint Layer::getLength() {
    return (uint) entities.size();
}

uint Layer::getWidth() {
    return (uint) entities[0].size();
}

bool Layer::isValid() {
    return isSeiled() && hasBoss();
}

int Layer::countElementsWithId(uint floor, uint ceiling) {
    int count = 0;
    for (uint i = 0; i != getLength(); ++i){
        for (uint j = 0; j != getWidth(); ++j){
            if (entities[i][j] != NULL) {
                uint id = entities[i][j]->getId();
                if (floor <= id && id < ceiling){
                    count++;
                }
            }
        }
    }
    return count;
}

bool Layer::isSeiled() {
    uint last_column = getLength() - 1;
    uint last_row = getWidth() - 1;
    for (uint i = 0; i != getLength(); ++i){
        for (uint j = 0; j != getWidth(); ++j){
            if (i == 0 || i == last_column || j == 0 || j == last_row){
                if (entities[i][j] == NULL) return false;
            }
        }
    }
    return true;
}

bool Layer::hasBoss() {
    return countElementsWithId(BOSS_FLOOR, BOSS_CEILING) == 1;
}

















