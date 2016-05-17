//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_LEVEL_H
#define MEGAMAN_LEVEL_H

#include <vector>
#include "Entity.h"
#include "Layer.h"

using std::vector;

typedef unsigned int uint;
typedef unsigned char color_t;
typedef struct rgb {
    color_t r;
    color_t g;
    color_t b;
} rgb_t;


class Level {
private:
    unsigned int length;
    map<string, Layer> layers;
    rgb_t background_color;
    Layer& getLayer(string which_layer);

public:
    //Level(string json_file);
    Level(uint len);
    void setBackgroundColor(color_t r, color_t g, color_t b);
    //void toJson(string file_name);
    bool addEntity(prototype_t prototype, string layer);
    bool removeEntity(uint x, uint y, string layer);

};


#endif //MEGAMAN_LEVEL_H
