//
// Created by marcos on 28/05/16.
//

#include <iostream>
#include "WorkspaceEventManager.h"

#define NO_SELECTION 0

typedef const Glib::RefPtr<Gdk::DragContext> DragContext;
typedef const Gtk::SelectionData SelectData;

using Gtk::TargetEntry;

WorkspaceEventManager::WorkspaceEventManager(Workspace &workspace)
    : workspace(workspace) {
        add(workspace);
        workspace.show();
        signal_button_press_event()
                .connect(sigc::mem_fun(*this, &WorkspaceEventManager::on_button_press));
        signal_drag_data_received()
                .connect(sigc::mem_fun(*this, &WorkspaceEventManager::on_drag_data_received));
        signal_selection().connect(sigc::mem_fun(*this, &WorkspaceEventManager::on_selection));
        something_selected = false;
    }

bool WorkspaceEventManager::on_button_press(GdkEventButton *event) {
    const int screen_width = workspace.getScreenWidth();
    uint xint = ((uint) event->x) / screen_width;
    uint yint = ((uint) event->y) / screen_width;
    if (!workspace.validPosition(xint, yint)) {
        return false;
    }
    uint id = workspace.getId(xint, yint);
    m_signal_selection.emit(id);
    if (id) {
        selection = std::make_pair(xint, yint);
        something_selected = true;
    } else {
        something_selected = false;
    }
    return true;
}

type_signal_selection WorkspaceEventManager::signal_selection() {
    return m_signal_selection;
}

void WorkspaceEventManager::on_delete() {
    if (!something_selected) return;
    if (!workspace.removeEntity(
                std::get<0>(selection),
                std::get<1>(selection))){
        throw std::runtime_error("Nothing to delete");
    }
    m_signal_selection.emit(NO_SELECTION);
}

void WorkspaceEventManager::on_drag_data_received(DragContext&, int x, int y,
                                                  SelectData& selection_data,
                                                  guint, guint) {
    const int screen_width = workspace.getScreenWidth();
    uint xint = ((uint) x) / screen_width;
    uint yint = ((uint) y) / screen_width;
    if (!workspace.validPosition(xint, yint)) return;
    uint id = (uint) atoi(selection_data.get_text().c_str());
    workspace.addElement(xint, yint, id);
}

void WorkspaceEventManager::setDroppable(vector<TargetEntry>& list_targets) {
    this->list_targets = list_targets;
    drag_dest_set(list_targets);

}

void WorkspaceEventManager::on_enlarge() {
    workspace.enlargeLevel();
}

void WorkspaceEventManager::on_shorten() {
    workspace.shortenLevel();
}

bool WorkspaceEventManager::on_selection(uint id) {
    something_selected = false;
    return true;
}























