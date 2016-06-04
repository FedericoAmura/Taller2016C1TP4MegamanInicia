//
// Created by marcos on 04/06/16.
//

#ifndef MEGAMAN_DYNAMICLAYER_H
#define MEGAMAN_DYNAMICLAYER_H

#include "Layer.h"

#define EMPTY_MARGIN 8

class DynamicLayer : public Layer {
public:
    explicit DynamicLayer(uint length) : Layer(length) {}
    bool addEntity(prototype_t prototype);
    bool removeEntity(uint x, uint y);

private:
    void adjust();
    int getAdjustmentNeeded();
    void enlarge(int this_much);
    void shorten(int this_much);
};


#endif //MEGAMAN_DYNAMICLAYER_H
