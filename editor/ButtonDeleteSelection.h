//
// Created by marcos on 28/05/16.
//

#ifndef MEGAMAN_BUTTONDELETESELECTION_H
#define MEGAMAN_BUTTONDELETESELECTION_H


#include <gtkmm/button.h>

class ButtonDeleteSelection : public Gtk::Button {
public:
    ButtonDeleteSelection();
    bool on_selection(uint id);
};


#endif //MEGAMAN_BUTTONDELETESELECTION_H
