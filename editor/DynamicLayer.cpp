//
// Created by marcos on 04/06/16.
//

#include "DynamicLayer.h"
#include <vector>
#include <iostream>

#define NPC_FLOOR 1000
#define NPC_CEILING 1100
#define MEGAMAN 9000
#define BOSS_DOOR 4000
#define BOSS_FLOOR 1100
#define BOSS_CEILING 2000

#define MIN_LEN 20


using std::vector;

void DynamicLayer::enlarge(int this_much) {
    //enlarges layer by 1
    vector<Entity*> new_row(getWidth());
    for (int i = 0; i < this_much; ++i){
        for (uint j = 0; j != getWidth(); ++j){
            new_row[j] = NULL;
        }
        entities.push_back(new_row);
    }
}

void DynamicLayer::shorten(int this_much) {
    //shortens layer by 1 if last two columns are empty
    int margin = std::min(EMPTY_MARGIN, this_much);
    for (int i = 0; i < this_much; ++i){
        if (getLength() - margin < MIN_LEN) {
            return;
        }
        //popped vectors are guaranteed to be empty
        entities.pop_back();
        --margin;
    }
}

int DynamicLayer::getAdjustmentNeeded() {
    int empty_columns = 0;
    for (uint i = getLength() - 1; i >= MIN_LEN - EMPTY_MARGIN; --i){
        for (uint j = 0; j < getWidth(); ++j){
            if (entities[i][j] != NULL){
                return EMPTY_MARGIN - empty_columns;
            }
        }
        ++empty_columns;
    }
    return EMPTY_MARGIN - empty_columns;
}

void DynamicLayer::adjust() {
    int needed = getAdjustmentNeeded();
    if (needed > 0) {
        enlarge(needed);
    } else if (needed < 0) {
        shorten(-needed);
    }
}

bool DynamicLayer::addEntity(prototype_t prototype) {
    bool res = Layer::addEntity(prototype);
    adjust();
    return res;
}

bool DynamicLayer::removeEntity(uint x, uint y) {
    bool res = Layer::removeEntity(x, y);
    adjust();
    return res;
}

bool DynamicLayer::isValid() {
    return hasEnemy()
           && hasBossDoor()
           && hasFourPlayerSpawners()
           && hasNoBoss();
}

bool DynamicLayer::hasEnemy() {
    return countElementsWithId(NPC_FLOOR, NPC_CEILING) > 0;
}

bool DynamicLayer::hasFourPlayerSpawners() {
    return countElementsWithId(MEGAMAN, MEGAMAN + 1) == 4;
}

bool DynamicLayer::hasBossDoor() {
    return countElementsWithId(BOSS_DOOR, BOSS_DOOR + 1) == 4;
}

bool DynamicLayer::hasNoBoss() {
    return countElementsWithId(BOSS_FLOOR, BOSS_CEILING) == 0;
}
