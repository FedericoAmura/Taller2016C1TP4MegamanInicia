//
// Created by marcos on 28/05/16.
//

#ifndef MEGAMAN_WORKSPACEEVENTMANAGER_H
#define MEGAMAN_WORKSPACEEVENTMANAGER_H

#include <gtkmm/eventbox.h>
#include <vector>
#include "Workspace.h"

using std::vector;
using std::pair;

typedef sigc::signal<bool, uint> type_signal_selection;

class WorkspaceEventManager : public Gtk::EventBox {
public:
    WorkspaceEventManager(Workspace* workspace);
    ~WorkspaceEventManager();
    void setDraggable(std::vector<Gtk::TargetEntry>& listTargets);
    void setDroppable(std::vector<Gtk::TargetEntry>& listTargets);
    type_signal_selection signal_selection();
    void on_delete();
    bool on_selection_change(uint id);
    void on_switch_page(Gtk::Widget*, guint);

private:
    Workspace* workspace;
    SpriteDispenser sprites;
    bool something_selected;
    pair<uint, uint> selection;
    vector<Gtk::TargetEntry> list_targets;

protected:
    type_signal_selection m_signal_selection;
    uint input_selection;

    //handlers
    bool on_button_press(GdkEventButton* event);
    void on_drag_begin(const Glib::RefPtr<Gdk::DragContext>& context);
    void on_drag_data_get(
            const Glib::RefPtr<Gdk::DragContext>&,
            Gtk::SelectionData& selection_data, guint, guint);
    void on_drag_data_received(
            const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
            const Gtk::SelectionData& selection_data, guint info, guint time);
    bool on_selection(uint id);
};


#endif //MEGAMAN_WORKSPACEEVENTMANAGER_H
