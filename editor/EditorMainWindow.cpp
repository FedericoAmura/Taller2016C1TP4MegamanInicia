//
// Created by marcos on 03/06/16.
//

#include <iostream>
#include "EditorMainWindow.h"

EditorMainWindow::EditorMainWindow(Workspace* main, Workspace* chamber)
        : main(main),
          chamber(chamber),
          background_combo(sprites),
          main_manager(main),
          chamber_manager(chamber) {
    //Init
    maximize();
    add(main_box);
    scrollable_main.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_NEVER);
    scrollable_chamber.set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_NEVER);
    main_box.pack_start(level_book, true, true);
    level_book.set_tab_pos(Gtk::POS_LEFT);
    main_tab.set_angle(90);
    chamber_tab.set_angle(90);
    main_tab.set_text("Main");
    chamber_tab.set_text("Chamber");
    level_book.append_page(scrollable_main, main_tab);
    level_book.append_page(scrollable_chamber, chamber_tab);
    scrollable_main.add(main_manager);
    scrollable_chamber.add(chamber_manager);
    main_box.pack_end(editing_box, false, false);
    editing_box.set_size_request(200, -1);
    editing_box.pack_start(background_combo, false, false);
    editing_box.pack_start(selector, true, true);
    editing_box.pack_end(selection_frame, false, false);
    selection_frame.add(selection_box);
    selection_drawing.set_halign(Gtk::ALIGN_CENTER);
    selection_box.pack_start(selection_drawing, false, false);
    selection_label.set_text("No element selected");
    selection_box.pack_end(selection_label, false, false);
    selection_box.pack_end(delete_button);
    show_all_children(true);
    selection_drawing.hide();
    delete_button.hide();

    //connect handlers
    main_manager.signal_selection().connect(sigc::mem_fun(selection_label, &SelectionLabel::on_selection));
    main_manager.signal_selection().connect(sigc::mem_fun(selection_drawing, &SelectionDrawing::on_selection));
    main_manager.signal_selection().connect(sigc::mem_fun(delete_button, &ButtonDeleteSelection::on_selection));
    delete_button.signal_clicked().connect(sigc::mem_fun(main_manager, &WorkspaceEventManager::on_delete));
    chamber_manager.signal_selection().connect(sigc::mem_fun(selection_label, &SelectionLabel::on_selection));
    chamber_manager.signal_selection().connect(sigc::mem_fun(selection_drawing, &SelectionDrawing::on_selection));
    chamber_manager.signal_selection().connect(sigc::mem_fun(delete_button, &ButtonDeleteSelection::on_selection));
    delete_button.signal_clicked().connect(sigc::mem_fun(chamber_manager, &WorkspaceEventManager::on_delete));
    selector.connect(&main_manager);
    selector.connect(&chamber_manager);
    level_book.signal_switch_page().connect(sigc::mem_fun(main_manager, &WorkspaceEventManager::on_switch_page));
    level_book.signal_switch_page().connect(sigc::mem_fun(chamber_manager, &WorkspaceEventManager::on_switch_page));
    background_combo.signal_changed().connect(sigc::mem_fun(*this, &EditorMainWindow::on_combo_changed) );

    //Drag and drop activation
    std::vector<Gtk::TargetEntry> list_targets;
    list_targets.push_back(Gtk::TargetEntry("STRING"));
    main_manager.setDroppable(list_targets);
    chamber_manager.setDroppable(list_targets);
    selector.setDraggable(list_targets);

    //Background init
    string background = background_combo.getSelected();
    main->setBackground(background);
    chamber->setBackground(background);
}

void EditorMainWindow::on_combo_changed() {
    main->setBackground(background_combo.getSelected());
    chamber->setBackground(background_combo.getSelected());
}



