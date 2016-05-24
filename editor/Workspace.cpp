//
// Created by marcos on 23/05/16.
//

#include <iostream>
#include "Workspace.h"
#include "../entities.h"

typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;

Workspace::Workspace(Level& level) : level(level) {
    Gdk::RGBA color;
    rgb_t rgb = level.getColor();
    color.set_rgba_u(256*rgb.r, 256*rgb.g, 256*rgb.b);
    uint width = level.getWidth();
    uint length = level.getLength();
    cells = vector<vector<CellDrawer*> >(width, vector<CellDrawer*>(length));
    for (uint i = 0; i < length; ++i){
        for (uint j = 0; j < width; ++j){
            CellDrawer* m_area = new CellDrawer();
            m_area->override_background_color(color);
            cells[j][i] = m_area;
            this->attach(*m_area, i, j, 1, 1);
        }
    }
    show_all_children();
}

