//
// Created by marcos on 28/05/16.
//

#ifndef MEGAMAN_SELECTIONLABEL_H
#define MEGAMAN_SELECTIONLABEL_H


#include <gtkmm/label.h>
#include "SpriteDispenser.h"

class SelectionLabel : public Gtk::Label {
public:
    bool on_selection(uint id);
};


#endif //MEGAMAN_SELECTIONLABEL_H
