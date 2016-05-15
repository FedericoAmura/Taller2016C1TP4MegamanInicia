//
// Created by marcos on 15/05/16.
//

#ifndef MEGAMAN_JSONREADER_H
#define MEGAMAN_JSONREADER_H

#include <string>
#include "Level.h"

using std::string;
using std::ifstream;

class JsonReader {
public:
    Level read(string& file_name);
private:
    Level levelInit(ifstream& file);
    void addEntities(ifstream& file, Level& level);
    string getValue(string block);
};


#endif //MEGAMAN_JSONREADER_H
