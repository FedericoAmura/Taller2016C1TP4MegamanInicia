//
// Created by marcos on 04/06/16.
//

#include "ChamberLevel.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <giomm.h>

#define WIDTH 15

using std::stringstream;
using std::ifstream;
using std::ofstream;

typedef Json::Value::iterator v_iter;

ChamberLevel::ChamberLevel(string json_file) {
    //Open File
    ifstream in(json_file);
    Json::Value level_json;
    in >> level_json;
    //Chamber tiles
    Json::Value elements = level_json["chamber"];
    entities = new Layer(27); //TODO sacar de header
    for (v_iter it = elements.begin(); it != elements.end(); ++it) {
        prototype_t p;
        p.x = (*it)["x"].asUInt();
        p.y = (*it)["y"].asUInt();
        p.id = (*it)["id"].asUInt();
        entities->addEntity(p);
    }
    in.close();
}

void ChamberLevel::toJson(string file_name) {
    ifstream in(file_name);
    Json::Value level;
    in >> level;
    level["chamber"] = entities->toJson();
    ofstream out(file_name, ofstream::out);
    out << level;
    in.close();
    out.close();
}

Level* ChamberLevel::cleanCopy() {
    return new ChamberLevel;
}

Level* ChamberLevel::openCopy(string file) {
    return new ChamberLevel(file);
}



