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
#include "EditorMainWindow.h"

typedef Glib::RefPtr<Gtk::Application> App;

using std::cerr;
using std::endl;

int main(int argc, char *argv[]) {
    App app = Gtk::Application::create(argc, argv, "Editor.Megaman");

    Level new_level("simplex.json");
    Workspace workspace(new_level);
    EditorMainWindow appWindow(workspace);

    //Run
    app->run(appWindow);

    //Descomentar para guardar cambios
    new_level.toJson("simplex.json");

    return 0;
}
