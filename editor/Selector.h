//
// Created by marcos on 28/05/16.
//

#ifndef MEGAMAN_SELECTOR_H
#define MEGAMAN_SELECTOR_H


#include <gtkmm/notebook.h>

class Selector : public Gtk::Notebook {
public:
    Selector();
private:
    Gtk::Label m_TilesLabel;
    Gtk::Label m_MobsLabel;
    Gtk::IconView m_TilesView;
    Gtk::IconView m_MobsView;
};


#endif //MEGAMAN_SELECTOR_H
