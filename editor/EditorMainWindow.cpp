//
// Created by marcos on 03/06/16.
//

#include <iostream>
#include "EditorMainWindow.h"

EditorMainWindow::EditorMainWindow(Workspace& workspace)
        : manager(workspace) {
    //Init
    maximize();
    add(main_box);
    scrollable_workspace.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_NEVER);
    main_box.pack_start(scrollable_workspace, true, true);
    main_box.pack_end(editing_box, false, true);
    editing_box.set_size_request(300, -1);
    scrollable_workspace.add(manager);
    editing_box.pack_start(selector, true, true);
    editing_box.pack_end(selection_frame, false, true);
    selection_frame.add(selection_box);
    selection_drawing.set_halign(Gtk::ALIGN_CENTER);
    selection_box.pack_start(selection_drawing, true, false);
    selection_label.set_text("No element selected");
    selection_box.pack_end(selection_label, true, false);
    selection_box.pack_end(delete_button, false, false);
    show_all_children(true);
    selection_drawing.hide();
    delete_button.hide();

    //connect handlers
    manager.signal_selection().connect(sigc::mem_fun(selection_label, &SelectionLabel::on_selection));
    manager.signal_selection().connect(sigc::mem_fun(selection_drawing, &SelectionDrawing::on_selection));
    manager.signal_selection().connect(sigc::mem_fun(delete_button, &ButtonDeleteSelection::on_selection));
    delete_button.signal_clicked().connect(sigc::mem_fun(manager, &WorkspaceEventManager::on_delete));

    //Drag and drop activation
    std::vector<Gtk::TargetEntry> list_targets;
    list_targets.push_back(Gtk::TargetEntry("STRING"));
    manager.setDroppable(list_targets);
    selector.setDraggable(list_targets);
}



