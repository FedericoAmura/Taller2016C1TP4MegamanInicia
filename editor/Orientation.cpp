//
// Created by marcos on 15/05/16.
//

#include "Orientation.h"

#define RIGHT 1
#define LEFT 0

Orientation::Orientation() {
    orientation = "up";
    vector<string> up;
    up.push_back("left");
    up.push_back("right");
    vector<string> right;
    right.push_back("up");
    right.push_back("down");
    vector<string> down;
    down.push_back("right");
    down.push_back("left");
    vector<string> left;
    left.push_back("down");
    left.push_back("up");
    rotations["up"] = up;
    rotations["right"] = right;
    rotations["down"] = down;
    rotations["left"] = left;
}

void Orientation::rotate(string direction) {
    int modifier;
    if (!(direction == "right") && !(direction == "left")){
        //TODO: raise error
        return;
    } else if (direction == "right"){
        modifier = RIGHT;
    } else {
        modifier = LEFT;
    }
    orientation = rotations[orientation][modifier];
}

Orientation::Orientation(string orient) {
    if (orient == "up" || orient == "right"
        || orient == "down" || orient == "left"){
        orientation = orient;
    } else {
        //TODO: raise error
    }
}

string Orientation::getOrientation() {
    return orientation;
}






