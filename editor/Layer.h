//
// Created by marcos on 17/05/16.
//

#ifndef MEGAMAN_LAYER_H
#define MEGAMAN_LAYER_H


#include "Entity.h"
#include "../json/json.h"
#include <vector>

using std::vector;

typedef unsigned int uint;
typedef struct prototype {
    uint x;
    uint y;
    uint id;
} prototype_t;

class Layer {
public:
    Layer(){} //TODO: Consultar sobre esto.
    explicit Layer(uint length);
    ~Layer();
    bool addEntity(prototype_t prototype);
    bool removeEntity(uint x, uint y);
    bool isEmpty(uint x, uint y);
    Json::Value toJson();
    void visualize(); //para trabajo interno: borrar
private:
    uint length;
    uint width;
    vector<vector <Entity*> >entities;
};


#endif //MEGAMAN_LAYER_H
