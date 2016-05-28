//
// Created by marcos on 28/05/16.
//

#include "SelectionDrawing.h"

#define SIDE 45

bool SelectionDrawing::on_selection(uint id) {
    if (id){
        setImage(sprites.get(id), SIDE, SIDE);
        show();
    } else {
        hide();
    }
    return true;
}

