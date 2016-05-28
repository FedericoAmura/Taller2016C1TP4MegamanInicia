//
// Created by marcos on 28/05/16.
//

#include <iostream>
#include "WorkspaceEventManager.h"

#define TILE_PXL 32
#define NO_SELECTION 0

WorkspaceEventManager::WorkspaceEventManager(Workspace &workspace)
    : workspace(workspace) {
        add(workspace);
        workspace.show();
        signal_button_press_event()
                .connect(sigc::mem_fun(*this, &WorkspaceEventManager::on_button_press));
        signal_drag_data_received()
                .connect(sigc::mem_fun(*this, &WorkspaceEventManager::on_drag_data_received));
        something_selected = false;
    }

bool WorkspaceEventManager::on_button_press(GdkEventButton *event) {
    uint xint = ((uint) event->x) / TILE_PXL;
    uint yint = ((uint) event->y) / TILE_PXL;
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
    if (!something_selected) {
        throw std::runtime_error("Nothing to delete");
    } else {
        if (!workspace.removeEntity(
                std::get<0>(selection),
                std::get<1>(selection))){
            throw std::runtime_error("Nothing to remove");
        }
        m_signal_selection.emit(NO_SELECTION);
    }
}

void WorkspaceEventManager::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext> &context,
                                                  int x, int y,
                                                  const Gtk::SelectionData &selection_data,
                                                  guint info, guint time) {
    return;
}









