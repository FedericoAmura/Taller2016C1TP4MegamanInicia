//
// Created by marcos on 17/05/16.
//

#ifndef MEGAMAN_LAYER_H
#define MEGAMAN_LAYER_H

#include "Entity.h"
#include "../json/json.h"
#include <vector>

#define DEF_LEN 20

using std::vector;

typedef unsigned int uint;
typedef struct prototype {
    uint x;
    uint y;
    uint id;
} prototype_t;

class Layer {
public:
    Layer() : Layer(DEF_LEN) {}
    explicit Layer(uint length);
    virtual ~Layer();
    virtual bool addEntity(prototype_t prototype);
    virtual bool removeEntity(uint x, uint y);
    uint getEntity(uint x, uint y);
    bool isEmpty(uint x, uint y);
    Json::Value toJson();
    uint getLength();
    uint getWidth();
    virtual bool isValid();
    uint getBossId();

private:
    //Validity functions
    bool isSeiled();
    bool hasBoss();

protected:
    vector<vector <Entity*> >entities;

    int countElementsWithId(uint floor, uint ceiling);
};


#endif //MEGAMAN_LAYER_H
