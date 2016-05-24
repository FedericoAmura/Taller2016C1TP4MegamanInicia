#include <gtkmm.h>
#include <iostream>
#include "EntitySet.h"
#include "../entities.h"
#include "SpriteDispenser.h"
#include "Workspace.h"

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
    Gtk::IconView* m_BackgroundView = NULL;
    refBuilder->get_widget("TileIcons", m_TilesView);
    refBuilder->get_widget("MobIcons", m_MobsView);
    refBuilder->get_widget("BackgroundIcons", m_BackgroundView);
    m_TilesView->set_item_width(ICON_WIDTH);
    m_MobsView->set_item_width(ICON_WIDTH);
    m_BackgroundView->set_item_width(ICON_WIDTH);
    EntitySet tiles(m_TilesView);
    EntitySet mobs(m_MobsView);
    EntitySet background(m_BackgroundView);
    vector<IconEntry> tile_entries = {
            IconEntry(BOSS_DOOR, sprites.get(BOSS_DOOR), "Boss Door"),
            IconEntry(CABLE_EDGE_0, sprites.get(CABLE_EDGE_0), "Cable Edge 1"),
            IconEntry(CABLE_EDGE_1, sprites.get(CABLE_EDGE_1), "Cable Edge 2"),
            IconEntry(CABLE_FLOOR_0, sprites.get(CABLE_FLOOR_0), "Cable Floor 1")
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
    vector<IconEntry> background_entries = {
            IconEntry(CAVE, sprites.get(CAVE), "Cave"),
            IconEntry(CAVE_EDGE, sprites.get(CAVE_EDGE), "Cave Edge"),
            IconEntry(PLANET, sprites.get(PLANET), "Planet"),
            IconEntry(MOSS_STONE, sprites.get(MOSS_STONE), "Moss Stone"),
            IconEntry(CLOUD, sprites.get(CLOUD), "Cloud"),
            IconEntry(CLOUD_EDGE, sprites.get(CLOUD_EDGE), "Cloud Edge")
    };
    tiles.fill(tile_entries);
    mobs.fill(mob_entries);
    background.fill(background_entries);

    //Workspace grid
    Gtk::ScrolledWindow* m_WorkspaceCanvas = NULL;
    refBuilder->get_widget("ScrollableWorkspace", m_WorkspaceCanvas);
    Level level(50);
    Workspace workspace(level);
    workspace.set_vexpand(true);
    m_WorkspaceCanvas->add(workspace);
    workspace.show();

    //Run
    if(appWindow) {
        app->run(*appWindow);
    }
    delete appWindow;
    return 0;
}