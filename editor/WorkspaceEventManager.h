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
    WorkspaceEventManager(Workspace& workspace);
    void setDroppable(std::vector<Gtk::TargetEntry>& listTargets);
    type_signal_selection signal_selection();
    void on_delete();
    void on_enlarge();
    void on_shorten();

private:
    Workspace& workspace;
    bool something_selected;
    pair<uint, uint> selection;
    vector<Gtk::TargetEntry> list_targets;

protected:
    type_signal_selection m_signal_selection;
    void on_drag_data_received(
            const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
            const Gtk::SelectionData& selection_data, guint info, guint time);

    //handlers
    bool on_button_press(GdkEventButton* event);

};


#endif //MEGAMAN_WORKSPACEEVENTMANAGER_H
