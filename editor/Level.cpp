//
// Created by marcos on 15/05/16.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <giomm.h>
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
    entities = new Layer(len);
}

Level::Level(string json_file) : width(WIDTH) {
    //Open File
    ifstream in(json_file);
    Json::Value level_json;
    in >> level_json;
    //Length
    this->length = level_json["length"].asUInt();
    //Width
    this->width = level_json["width"].asUInt();
    //Foreground tiles
    Json::Value foreground = level_json["foreground"];
    Layer* foreground_layer = new Layer(this->length);
    for (v_iter it = foreground.begin(); it != foreground.end(); ++it) {
        prototype_t p;
        p.x = (*it)["x"].asUInt();
        p.y = (*it)["y"].asUInt();
        p.id = (*it)["id"].asUInt();
        foreground_layer->addEntity(p);
    }
    entities = foreground_layer;
    in.close();
}

bool Level::addEntity(prototype_t prototype) {
    if (length - prototype.x == 1) ++length;
    return entities->addEntity(prototype);

}

bool Level::removeEntity(uint x, uint y) {
    return entities->removeEntity(x, y);
}

void Level::toJson(string file_name) {
    Json::Value level(Json::objectValue);
    level["valid"] = true; //TODO: por ahora hardcodeo esto, despues va a depender de los chequeos del editor
    level["length"] = length;
    level["width"] = WIDTH;
    level["foreground"] = entities->toJson();
    ofstream out(file_name, ofstream::out);
    out << level;
    out.close();
}

void Level::setBackgroundFile(string path) {
    std::ifstream infile(path);
    if (infile.good()){
        background_file = path;
    } else {
        throw std::runtime_error("Background file does not exist");
    }
}

uint Level::getEntity(uint x, uint y) {
    return entities->getEntity(x, y);
}

Level::~Level() {
    delete entities;
}


