#include <gtkmm.h>
#include <iostream>
#include "EntitySet.h"
#include "../common/SpriteDispenser.h"
#include "Workspace.h"
#include "WorkspaceEventManager.h"
#include "SelectionLabel.h"
#include "SelectionDrawing.h"
#include "ButtonDeleteSelection.h"
#include "Selector.h"

typedef Glib::RefPtr<Gtk::Builder> Builder;
typedef Glib::RefPtr<Gtk::Application> App;
typedef Glib::RefPtr<Gtk::ListStore> ListStore;
typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    App app = Gtk::Application::create(argc, argv, "Level.Editor");
    //Load the GtkBuilder file and instantiate its widgets:
    Builder refBuilder = Gtk::Builder::create();
    Gtk::ApplicationWindow* appWindow = NULL;
    try {
        refBuilder->add_from_file("editor_main_window.glade");
    } catch(const Glib::FileError& ex) {
        cerr << "FileError: " << ex.what() << endl;
        return 1;
    } catch(const Glib::MarkupError& ex) {
        cerr << "MarkupError: " << ex.what() << endl;
        return 1;
    } catch(const Gtk::BuilderError& ex) {
        cerr << "BuilderError: " << ex.what() << endl;
        return 1;
    }
    //Instantiate app window
    refBuilder->get_widget("EditorWindow", appWindow);

    //Element selector display
    Gtk::Box* m_EditingArea = NULL;
    refBuilder->get_widget("Workspace", m_EditingArea);
    Selector selector;
    m_EditingArea->pack_end(selector, false, true);

    //Workspace grid
    Gtk::Viewport* m_Viewport = NULL;
    refBuilder->get_widget("WorkspaceView", m_Viewport);
    Level level("simplex.json");
    level.setBackgroundFile("../images/background1.jpg");
    Workspace workspace(level);
    WorkspaceEventManager manager(workspace);
    workspace.set_vexpand(true);
    m_Viewport->add(manager);
    manager.show();

    //Modifiers
    Gtk::Box* m_Box = NULL;
    refBuilder->get_widget("Modifiers", m_Box);
    SelectionLabel s_label;
    s_label.set_text("No element selected");
    manager.signal_selection().connect(sigc::mem_fun(s_label, &SelectionLabel::on_selection));
    m_Box->pack_start(s_label);
    s_label.show();
    SelectionDrawing s_drawing;
    manager.signal_selection().connect(sigc::mem_fun(s_drawing, &SelectionDrawing::on_selection));
    m_Box->pack_start(s_drawing);
    ButtonDeleteSelection s_button;
    manager.signal_selection().connect(sigc::mem_fun(s_button, &ButtonDeleteSelection::on_selection));
    s_button.signal_clicked().connect(sigc::mem_fun(manager, &WorkspaceEventManager::on_delete));
    m_Box->pack_start(s_button);
    Gtk::Button* plusButton = NULL;
    refBuilder->get_widget("plusButton", plusButton);
    Gtk::Button* lessButton = NULL;
    refBuilder->get_widget("lessButton", lessButton);
    plusButton->signal_clicked().connect(sigc::mem_fun(manager, &WorkspaceEventManager::on_enlarge));
    lessButton->signal_clicked().connect(sigc::mem_fun(manager, &WorkspaceEventManager::on_shorten));

    //Drag and drop activation
    std::vector<Gtk::TargetEntry> list_targets;
    list_targets.push_back(Gtk::TargetEntry("STRING"));
    manager.setDroppable(list_targets);
    selector.setDraggable(list_targets);

    //Run
    if(appWindow) {
        app->run(*appWindow);
    }

    //Descomentar para guardar cambios
    level.toJson("simplex.json");

    delete appWindow;
    return 0;
}
