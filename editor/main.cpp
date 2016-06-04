#include <iostream>
#include "EntitySet.h"
#include "../common/SpriteDispenser.h"
#include "Workspace.h"
#include "EditorMainWindow.h"

typedef Glib::RefPtr<Gtk::Application> App;

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    App app = Gtk::Application::create(argc, argv, "Editor.Megaman");

    Level main_level("simplex.json");
    Workspace main_ws(main_level);
    Level chamber(20);
    Workspace chamber_ws(chamber);
    EditorMainWindow appWindow(main_ws, chamber_ws);

    //Run
    app->run(appWindow);

    //Descomentar para guardar cambios
    main_level.toJson("simplex.json");

    return 0;
}
