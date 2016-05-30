//
// Created by marcos on 28/05/16.
//

#ifndef MEGAMAN_SELECTIONDRAWING_H
#define MEGAMAN_SELECTIONDRAWING_H

#include "../common/MyArea.h"
#include "../common/SpriteDispenser.h"

class SelectionDrawing : public Drawing {
public:
    bool on_selection(uint id);
private:
    SpriteDispenser sprites;
};


#endif //MEGAMAN_SELECTIONDRAWING_H
