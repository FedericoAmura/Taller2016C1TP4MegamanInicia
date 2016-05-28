//
// Created by marcos on 15/05/16.
//

#include <string>
#include <iostream>
#include "Level.h"
#include "Layer.h"
#include "../entities.h"

#define SMALL 50
#define BACKGROUND "false background"

using std::string;
using std::cout;

void printTest(string msg, bool test){
    cout << msg << ": ";
    if (test) cout << "OK";
    else cout << "ERROR";
    cout << std::endl;
}

void printTitle(string msg){
    cout << "===================\n" << msg << "\n";
    cout << "===================\n";
}

void levelTest(prototype_t p0){
    printTitle("Level Test");
    Level level = Level(SMALL);

    printTest("Adds entity", level.addEntity(p0));
    printTest("Does not add entity on top of existing one", !level.addEntity(p0));
    printTest("Does not remove non-existing entity", !level.removeEntity(1, 1));
    printTest("Removes entity", level.removeEntity(0, 0));
}

void jsonTest(prototype_t p0, prototype_t p1){
    printTitle("JSON Test");
    string file_name = "test_level.json";
    Level level(SMALL);
    level.addEntity(p0);
    level.addEntity(p1);
    level.toJson(file_name);
    Level loaded(file_name);
    printTest("Entity successfully recovered from loaded level", loaded.removeEntity(5,5));
    printTest("Loaded level does not recover non-existent entity", !loaded.removeEntity(5,6));
}

int main(){
    prototype_t spike;
    spike.x = spike.y = 0;
    spike.id = SPIKE;

    prototype_t sparkman;
    sparkman.x = sparkman.y = 5;
    sparkman.id = SPARKMAN;

    levelTest(spike);
    jsonTest(spike, sparkman);
}