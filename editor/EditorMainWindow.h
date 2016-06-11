//
// Created by marcos on 03/06/16.
//

#ifndef MEGAMAN_EDITORMAINWINDOW_H
#define MEGAMAN_EDITORMAINWINDOW_H


#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include <gtkmm/frame.h>
#include <gtkmm/builder.h>
#include "WorkspaceEventManager.h"
#include "Selector.h"
#include "SelectionLabel.h"
#include "SelectionDrawing.h"
#include "ButtonDeleteSelection.h"
#include "BackgroundComboBox.h"

class EditorMainWindow : public Gtk::ApplicationWindow {
public:
    EditorMainWindow(Workspace* main, Workspace* chamber);

private:
    SpriteDispenser sprites;
    Workspace* main;
    Workspace* chamber;

    //Widgets
    Gtk::HBox main_box;
    Gtk::ScrolledWindow scrollable_main;
    Gtk::ScrolledWindow scrollable_chamber;
    Gtk::VBox editing_box;
    Gtk::Label main_tab;
    Gtk::Label chamber_tab;
    BackgroundComboBox background_combo;
    Gtk::Notebook level_book;
    WorkspaceEventManager main_manager;
    WorkspaceEventManager chamber_manager;
    Selector selector;
    Gtk::Frame selection_frame;
    Gtk::VBox selection_box;
    SelectionDrawing selection_drawing;
    SelectionLabel selection_label;
    ButtonDeleteSelection delete_button;

    //Signal handlers:
    void on_combo_changed();
};


#endif //MEGAMAN_EDITORMAINWINDOW_H
