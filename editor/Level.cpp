//
// Created by marcos on 15/05/16.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Level.h"

#define WIDTH 15

using std::stringstream;
using std::ofstream;
using std::make_pair;
using std::runtime_error;

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
        throw runtime_error("Requested non-existent layer");
    }
    return *layer;
}

void Level::toJson(string file_name) {
    Json::Value level(Json::objectValue);
    level["length"] = length;
    level["width"] = WIDTH;
    Json::Value color(Json::objectValue);
    color["r"] = background_color.r;
    color["g"] = background_color.g;
    color["b"] = background_color.b;
    level["background color"] = color;
    level["background"] = layers["background"].toJson();
    level["foreground"] = layers["foreground"].toJson();
    ofstream out(file_name, ofstream::out);
    out << level;
    out.close();
}











