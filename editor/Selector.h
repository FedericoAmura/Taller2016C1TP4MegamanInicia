//
// Created by marcos on 28/05/16.
//

#ifndef MEGAMAN_SELECTOR_H
#define MEGAMAN_SELECTOR_H

#include <vector>
#include <gtkmm/notebook.h>
#include <gtkmm/treeview.h>
#include <gtkmm/scrolledwindow.h>
#include "EntityIconView.h"
#include "WorkspaceEventManager.h"

using std::vector;

class Selector : public Gtk::Notebook {
public:
    Selector();
    void setDraggable(vector<Gtk::TargetEntry>& list_targets);
    void connect(WorkspaceEventManager* manager);

private:
    Gtk::Label m_TilesLabel;
    Gtk::Label m_MobsLabel;
    Gtk::ScrolledWindow m_TilesScrolled;
    Gtk::ScrolledWindow m_MobsScrolled;
    EntityIconView m_TilesView;
    EntityIconView m_MobsView;
    vector<Gtk::TargetEntry> list_targets;
};


#endif //MEGAMAN_SELECTOR_H
