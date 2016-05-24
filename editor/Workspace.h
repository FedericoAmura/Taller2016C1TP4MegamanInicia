//
// Created by marcos on 23/05/16.
//

#ifndef MEGAMAN_WORKSPACE_H
#define MEGAMAN_WORKSPACE_H

#include <gtkmm/grid.h>
#include "Level.h"
#include "CellDrawer.h"
#include <vector>

using std::vector;

typedef unsigned int uint;

class Workspace : public Gtk::Grid {
public:
    Workspace(Level& level);

private:
    Level& level;
    vector<vector<CellDrawer*> > cells;

};


#endif //MEGAMAN_WORKSPACE_H
