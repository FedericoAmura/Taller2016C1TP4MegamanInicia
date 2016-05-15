//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_ORIENTATION_H
#define MEGAMAN_ORIENTATION_H

#include <string>
#include <map>
#include <vector>

using std::vector;
using std::map;
using std::string;

class Orientation {
public:
    Orientation();
    Orientation(string orientation);
    void rotate(string direction);
    string getOrientation() {return orientation;}
private:
    string orientation;
    map<string, vector<string> > rotations;
};


#endif //MEGAMAN_ORIENTATION_H
