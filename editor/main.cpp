#include <iostream>
#include "EntitySet.h"
#include "../common/SpriteDispenser.h"
#include "Workspace.h"
#include "EditorMainWindow.h"
#include "ChamberLevel.h"

typedef Glib::RefPtr<Gtk::Application> App;

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    App app = Gtk::Application::create(argc, argv, "Editor.Megaman");

    string json_path = "simplex.json";
    Level main_level(json_path);
    Workspace main_ws(main_level);
    ChamberLevel chamber(json_path);
    Workspace chamber_ws(chamber);
    EditorMainWindow appWindow(main_ws, chamber_ws);

    //Run
    app->run(appWindow);

    //Descomentar para guardar cambios
    main_level.toJson(json_path);
    chamber.toJson(json_path);

    return 0;
}
