//
// Created by marcos on 15/05/16.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Level.h"

#define WIDTH 15
#define INDENT 1

using std::stringstream;
using std::ofstream;
using std::make_pair;

Level::Level(uint len) : length(len) {
    layers.insert(make_pair("background", Layer(length)));
    layers.insert(make_pair("foreground", Layer(length)));
    background_color.r = 0;
    background_color.g = 255;
    background_color.b = 255;
}

void Level::setBackgroundColor(color_t r, color_t g, color_t b) {
    background_color.r = r;
    background_color.g = g;
    background_color.b = b;
}

bool Level::addEntity(prototype_t prototype, string which_layer) {
    return getLayer(which_layer).addEntity(prototype);

}

bool Level::removeEntity(uint x, uint y, string which_layer) {
    return getLayer(which_layer).removeEntity(x, y);
}

Layer& Level::getLayer(string which_layer) {
    Layer* layer = &layers[which_layer];
    if (layer == NULL){
        throw std::runtime_error("Requested non-existent layer");
    }
    return *layer;
}











