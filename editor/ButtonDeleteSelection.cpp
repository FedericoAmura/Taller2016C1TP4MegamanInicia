//
// Created by marcos on 28/05/16.
//

#include "ButtonDeleteSelection.h"

ButtonDeleteSelection::ButtonDeleteSelection() {
    set_label("delete");
}

bool ButtonDeleteSelection::on_selection(uint id) {
    if (id){
        show();
    } else {
        hide();
    }
    return true;
}



