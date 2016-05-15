//
// Created by marcos on 15/05/16.
//

#include <string>
#include <iostream>
#include "Orientation.h"
#include "Level.h"
#include "../entities.h"
#include "JsonReader.h"

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
    printTest("Does not add entity on top of existing one", !level.addEntity(0, 0, SPIKE));
    printTest("Does not remove non-existing entity", !level.removeEntity(1, 1));
    printTest("Removes entity", level.removeEntity(0,0));
}

void jsonTest(){
    printTitle("JSON Test");
    string file_name = "test_level.json";
    Level level = Level(SMALL, BACKGROUND);
    level.addEntity(3, 5, SPARKMAN);
    level.addEntity(1, 2, LADDER);
    level.writeJsonFile(file_name);
    JsonReader reader = JsonReader();
    Level read = reader.read(file_name);
    printTest("Reader did not write garbage", !read.removeEntity(0,0));
    printTest("Reader included entity correctly", read.removeEntity(3,5));
}

int main(){
    orientationTest();
    levelTest();
    jsonTest();
}