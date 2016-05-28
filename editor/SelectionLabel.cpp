//
// Created by marcos on 28/05/16.
//

#include "SelectionLabel.h"
#include "../client/MyArea.h"
#include <string>

using std::string;

typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;

bool SelectionLabel::on_selection(uint id) {
    show();
    if (id) {
        hide();
    }
    return true;
}

