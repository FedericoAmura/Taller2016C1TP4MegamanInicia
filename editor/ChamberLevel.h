//
// Created by marcos on 04/06/16.
//

#ifndef MEGAMAN_CHAMBERLEVEL_H
#define MEGAMAN_CHAMBERLEVEL_H

#include "Level.h"

/*A Level which uses Layer instead of DynamicLayer*/
class ChamberLevel : public Level {
public:
    ChamberLevel(string json_file);
    ChamberLevel() {
        entities = new Layer(27); //hardcodeo por ahora
    }
    void toJson(string file_name);
};


#endif //MEGAMAN_CHAMBERLEVEL_H
