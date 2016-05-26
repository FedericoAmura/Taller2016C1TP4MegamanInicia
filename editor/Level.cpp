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
using std::ifstream;
using std::ofstream;
using std::make_pair;
using std::runtime_error;

typedef Json::Value::iterator v_iter;

Level::Level(uint len) : length(len) {
    width = WIDTH;
    layers.insert(make_pair("background", Layer(length)));
    layers.insert(make_pair("foreground", Layer(length)));
    background_color.r = 0;
    background_color.g = 255;
    background_color.b = 255;
}

Level::Level(string json_file) : width(WIDTH) {
    //Open File
    ifstream in(json_file);
    Json::Value level_json;
    in >> level_json;
    //Length
    this->length = level_json["length"].asUInt();
    //Background color
    Json::Value b_color = level_json["background color"];
    color_t r = (color_t) b_color["r"].asUInt();
    color_t g = (color_t) b_color["g"].asUInt();
    color_t b = (color_t) b_color["b"].asUInt();
    this->setBackgroundColor(r, g, b);
    //Background tiles
    Json::Value background = level_json["background"];
    Layer background_layer(this->length);
    for (v_iter it = background.begin(); it != background.end(); ++it) {
        prototype_t p;
        p.x = (*it)["x"].asUInt();
        p.y = (*it)["y"].asUInt();
        p.id = (*it)["id"].asUInt();
        background_layer.addEntity(p);
    }
    this->layers["background"] = background_layer;
    //Foreground tiles
    Json::Value foreground = level_json["foreground"];
    Layer foreground_layer(this->length);
    for (v_iter it = foreground.begin(); it != foreground.end(); ++it) {
        prototype_t p;
        p.x = (*it)["x"].asUInt();
        p.y = (*it)["y"].asUInt();
        p.id = (*it)["id"].asUInt();
        foreground_layer.addEntity(p);
    }
    this->layers["foreground"] = foreground_layer;
    in.close();
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
    level["valid"] = true; //TODO: por ahora hardcodeo esto, despues va a depender de los chequeos del editor
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

void Level::visualize() {
    std::cout << "BACKGROUND" << std::endl;
    layers["background"].visualize();
    std::cout << "FOREGROUND" << std::endl;
    layers["foreground"].visualize();
}



















