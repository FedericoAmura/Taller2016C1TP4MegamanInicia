//
// Created by marcos on 17/05/16.
//

#ifndef MEGAMAN_LAYER_H
#define MEGAMAN_LAYER_H


#include "Entity.h"
#include <vector>

typedef unsigned int uint;
typedef struct prototype {
    uint x;
    uint y;
    size_t id;
    string orientation;
} prototype_t;

class Layer {
public:
    Layer(){}; //TODO: Consultar sobre esto. (explicit al de abajo? Nico)
    Layer(unsigned int length);
    ~Layer();
    bool addEntity(prototype_t prototype);
    bool removeEntity(uint x, uint y);
    bool isEmpty(unsigned int x, unsigned int y);
private:
    vector<vector <Entity*> >entities;
    uint length;
};


#endif //MEGAMAN_LAYER_H
