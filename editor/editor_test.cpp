//
// Created by marcos on 15/05/16.
//

#include <string>
#include <iostream>
#include "Orientation.h"
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

void orientationTest(){
    printTitle("Orientation Test");
    Orientation orientation = Orientation();
    printTest("Up by default", orientation.getOrientation() == "up");
    orientation.rotate("right");
    printTest("Right of up is right", orientation.getOrientation() == "right");
    orientation.rotate("right");
    printTest("Right of right is down", orientation.getOrientation() == "down");
    orientation.rotate("right");
    printTest("Right of down is left", orientation.getOrientation() == "left");
    orientation.rotate("right");
    printTest("Right of left is up", orientation.getOrientation() == "up");
    orientation.rotate("left");
    printTest("Left of up is left", orientation.getOrientation() == "left");
    orientation.rotate("left");
    printTest("Left of left is down", orientation.getOrientation() == "down");
    orientation.rotate("left");
    printTest("Left of down is right", orientation.getOrientation() == "right");
    orientation.rotate("left");
    printTest("Left of right is up", orientation.getOrientation() == "up");
}

void levelTest(prototype_t p0){
    printTitle("Level Test");
    Level level = Level(SMALL);

    printTest("Adds entity", level.addEntity(p0, "foreground"));
    printTest("Does not add entity on top of existing one", !level.addEntity(p0, "foreground"));
    printTest("Does not remove non-existing entity", !level.removeEntity(1, 1, "foreground"));
    printTest("Removes entity", level.removeEntity(0,0, "foreground"));
}

void jsonTest(prototype_t p0, prototype_t p1, prototype_t b0){
    printTitle("JSON Test");
    string file_name = "test_level.json";
    Level level(SMALL);
    level.addEntity(p0, "foreground");
    level.addEntity(p1, "foreground");
    level.addEntity(b0, "background");
    level.toJson("test_level.json");
}

int main(){
    prototype_t spike;
    spike.x = spike.y = 0;
    spike.id = SPIKE;
    spike.orientation = "up";

    prototype_t sparkman;
    sparkman.x = sparkman.y = 5;
    sparkman.id = SPARKMAN;
    sparkman.orientation = "up";

    prototype_t cave;
    cave.x = cave.y = 5;
    cave.id = SPARKMAN;
    cave.orientation = "up";

    orientationTest();
    levelTest(spike);
    jsonTest(spike, sparkman, cave);
}