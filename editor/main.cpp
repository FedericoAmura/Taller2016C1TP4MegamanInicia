#include <gtkmm.h>
#include <iostream>
#include "EntitySet.h"
#include "../entities.h"
#include "SpriteDispenser.h"
#include "Workspace.h"
#include "WorkspaceEventManager.h"
#include "SelectionLabel.h"
#include "SelectionDrawing.h"
#include "ButtonDeleteSelection.h"

#define ICON_WIDTH 62

typedef Glib::RefPtr<Gtk::Builder> Builder;
typedef Glib::RefPtr<Gtk::Application> App;
typedef Glib::RefPtr<Gtk::ListStore> ListStore;
typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;
typedef Glib::RefPtr<Gtk::Layout> Layout;

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
    //Get the GtkBuilder-instantiated Window:
    refBuilder->get_widget("EditorWindow", appWindow);

    //Toolbox display
    SpriteDispenser sprites;
    Gtk::IconView* m_TilesView = NULL;
    Gtk::IconView* m_MobsView = NULL;
    refBuilder->get_widget("TileIcons", m_TilesView);
    refBuilder->get_widget("MobIcons", m_MobsView);
    m_TilesView->set_item_width(ICON_WIDTH);
    m_MobsView->set_item_width(ICON_WIDTH);
    m_TilesView->enable_model_drag_source(std::vector<Gtk::TargetEntry>());
    m_MobsView->enable_model_drag_source(std::vector<Gtk::TargetEntry>());
    EntitySet tiles(m_TilesView);
    EntitySet mobs(m_MobsView);
    vector<IconEntry> tile_entries = {
            IconEntry(STONE_WALL, sprites.get(STONE_WALL), "Wall"),
            IconEntry(SPIKE, sprites.get(SPIKE), "Spike"),
            IconEntry(STONE_LADDER, sprites.get(STONE_LADDER), "Ladder")
    };
    vector<IconEntry> mob_entries = {
            IconEntry(BUMBY, sprites.get(BUMBY), "Bumby"),
            IconEntry(MET, sprites.get(MET), "Met"),
            IconEntry(SNIPER, sprites.get(SNIPER), "Sniper"),
            IconEntry(JUMPING_SNIPER, sprites.get(JUMPING_SNIPER), "Jumping Sniper"),
            IconEntry(BOMBMAN, sprites.get(BOMBMAN), "Bombman"),
            IconEntry(FIREMAN, sprites.get(FIREMAN), "Fireman"),
            IconEntry(MAGNETMAN, sprites.get(MAGNETMAN), "Magnetman"),
            IconEntry(SPARKMAN, sprites.get(SPARKMAN), "Sparkman")
    };
    tiles.fill(tile_entries);
    mobs.fill(mob_entries);

    //Workspace grid
    Gtk::Viewport* m_Viewport = NULL;
    refBuilder->get_widget("WorkspaceView", m_Viewport);

    Level level("simplex.json");
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





    //Run
    if(appWindow) {
        app->run(*appWindow);
    }
    delete appWindow;
    return 0;
}