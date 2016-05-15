//
// Created by marcos on 15/05/16.
//

#include <string>
#include <iostream>
#include "Orientation.h"
#include "Level.h"
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

void levelTest(){
    printTitle("Level Test");
    Level level = Level(SMALL, BACKGROUND);
    printTest("Adds entity", level.addEntity(0, 0, SPIKE));
    printTest("Removes entity", level.removeEntity(0,0));
}

void jsonTest(){
    printTitle("JSON Test");
    Level level = Level(SMALL, BACKGROUND);
    level.addEntity(3, 5, SPARKMAN);
    level.addEntity(1, 2, LADDER);
    level.writeJsonFile("test_level.json");
}

int main(){
    orientationTest();
    levelTest();
    jsonTest();
}