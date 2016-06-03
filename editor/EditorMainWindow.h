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
#include "WorkspaceEventManager.h"
#include "Selector.h"
#include "SelectionLabel.h"
#include "SelectionDrawing.h"
#include "ButtonDeleteSelection.h"

class EditorMainWindow : public Gtk::ApplicationWindow {
public:
    EditorMainWindow(Workspace& workspace);

private:
    Gtk::HBox main_box;
    Gtk::ScrolledWindow scrollable_workspace;
    Gtk::VBox editing_box;
    WorkspaceEventManager manager;
    Selector selector;
    Gtk::Frame selection_frame;
    Gtk::VBox selection_box;
    SelectionDrawing selection_drawing;
    SelectionLabel selection_label;
    ButtonDeleteSelection delete_button;

};


#endif //MEGAMAN_EDITORMAINWINDOW_H
