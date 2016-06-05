#include <iostream>
#include "EntitySet.h"
#include "../common/SpriteDispenser.h"
#include "Workspace.h"
#include "EditorMainWindow.h"
#include "ChamberLevel.h"
#include "EditorApp.h"

int main(int argc, char *argv[]) {
    Glib::RefPtr<EditorApp> app = EditorApp::create();
    return app->run(argc, argv);
}
