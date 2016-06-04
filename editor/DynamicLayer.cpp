//
// Created by marcos on 04/06/16.
//

#include "DynamicLayer.h"
#include <vector>

#define MIN_LEN 20
#define EMPTY_MARGIN 8

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
    if (getLength() - EMPTY_MARGIN <= MIN_LEN) {
        return;
    }
    for (int i = 0; i < this_much; ++i){
        //popped vectors are guaranteed to be empty
        entities.pop_back();
    }
}

int DynamicLayer::getAdjustmentNeeded() {
    int empty_columns = 0;
    for (uint i = getLength() - 1; i > MIN_LEN; --i){
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
