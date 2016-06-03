//
// Created by marcos on 28/05/16.
//

#include "SelectionDrawing.h"

#define SIDE 90

bool SelectionDrawing::on_selection(uint id) {
    if (id){
        hide();
        setImage(sprites.get(id), SIDE, SIDE, false);
        show();
    } else {
        hide();
    }
    return true;
}

