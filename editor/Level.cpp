//
// Created by marcos on 15/05/16.
//

#include <sstream>
#include <fstream>
#include "Level.h"

#define WIDTH 15
#define INDENT 1

using std::stringstream;
using std::ofstream;

Level::Level(unsigned int length, string background_name)
    : length(length), background_name(background_name) {
    width = WIDTH;
    entities = vector<vector<Entity*> >(length, std::vector<Entity*>(width));
    for (unsigned int i = 0; i != length; ++i){
        for (unsigned int j = 0; j != width; ++j){
            entities[i][j] = NULL;
        }
    }
}

bool Level::isEmpty(unsigned int x, unsigned int y) {
    return entities[x][y] == NULL;
}

bool Level::addEntity(uint x, uint y, size_t id, string orientation) {
    if (!isEmpty(x, y)){
        return false;
    }
    Entity* new_entity = new Entity(id, orientation);
    entities[x][y] = new_entity;
    return true;
}

bool Level::removeEntity(uint x, uint y) {
    if (isEmpty(x, y)){
        return false;
    }
    Entity* erase = entities[x][y];
    entities[x].erase(entities[x].begin() + y);
    delete erase;
    return true;
}

string Level::asJson() {
    stringstream s;
    s << "{\n";
    s << "\t\"length\":" << length << ",\n";
    s << "\t\"width\":" << width << ",\n";
    s << "\t\"background\":\"" << background_name << "\",\n";
    s << "\t\"entities\":[\n";
    Entity* current_entity;
    bool first = true;
    for(unsigned int i = 0; i != length; ++i){
        for(unsigned int j = 0; j != width; ++j){
            current_entity = entities[i][j];
            if(current_entity != NULL){
                if (!first) s << ",\n";
                s << current_entity->asJson(i, j, 2*INDENT);
                first = false;
            }
        }
    }
    s << "\n\t\t]\n";
    s << "}";
    return s.str();
}

void Level::writeJsonFile(string file_name) {
    ofstream file(file_name.c_str());
    file << this->asJson();
    file.close();
}











