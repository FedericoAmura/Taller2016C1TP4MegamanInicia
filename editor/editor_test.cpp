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
#define NO_INDENT 0
#define INDENT 1

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

    printTest("Adds entity", level.addEntity(p0, "foreground"));
    printTest("Does not add entity on top of existing one", !level.addEntity(p0, "foreground"));
    printTest("Does not remove non-existing entity", !level.removeEntity(1, 1, "foreground"));
    printTest("Removes entity", level.removeEntity(0, 0, "foreground"));
}

void jsonTest(prototype_t p0, prototype_t p1, prototype_t b0){
    printTitle("JSON Test");
    string file_name = "test_level.json";
    Level level(SMALL);
    level.addEntity(p0, "foreground");
    level.addEntity(p1, "foreground");
    level.addEntity(b0, "background");
    level.toJson(file_name);
    level.visualize();
    Level loaded(file_name);
    loaded.visualize();
    printTest("Entity successfully recovered from loaded level", loaded.removeEntity(5,5,"foreground"));
    printTest("Loaded level does not recover non-existent entity", !loaded.removeEntity(5,6,"foreground"));
}

int main(){
    prototype_t spike;
    spike.x = spike.y = 0;
    spike.id = STONE_SPIKE;

    prototype_t sparkman;
    sparkman.x = sparkman.y = 5;
    sparkman.id = SPARKMAN;

    prototype_t cave;
    cave.x = cave.y = 5;
    cave.id = SPARKMAN;

    levelTest(spike);
    jsonTest(spike, sparkman, cave);
}