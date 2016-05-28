//
// Created by marcos on 23/05/16.
//

#include <iostream>
#include <gdkmm.h>
#include "Workspace.h"
#include "../entities.h"

#define TILE_PXL 32

typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;
typedef drawing_map_t::iterator p_iter;

Workspace::Workspace(Level& level) : level(level) {
    resize();
    for (uint i = 0; i < level.getWidth() ; ++i){
        for (uint j = 0; j < level.getLength() ; ++j){
            uint id = level.getEntity(i, j);
            if (id != 0) {
                pair<uint, uint> position = std::make_pair(i, j);
                Drawing* drawing = new Drawing();
                drawing->setImage(sprites.get(id), TILE_PXL, TILE_PXL);
                drawings[position] = drawing;
                put(*drawing,
                    std::get<0>(position) * TILE_PXL,
                    std::get<1>(position) * TILE_PXL);
                drawing->show();
            }
        }
    }
}

void Workspace::resize() {
    set_size_request(level.getLength()*TILE_PXL, level.getWidth()*TILE_PXL);
}

Workspace::~Workspace() {
    for (p_iter it = drawings.begin(); it != drawings.end(); ++it){
        delete it->second;
    }
}

bool Workspace::addElement(uint x, uint y, uint id) {
    //Add to model
    prototype_t element;
    element.x = x;
    element.y = y;
    element.id = id;
    if (level.addEntity(element)){
        //Add to view
        pair<uint, uint> position = std::make_pair(x, y);
        Drawing* drawing = new Drawing();
        drawing->setImage(sprites.get(id), TILE_PXL, TILE_PXL);
        drawings[position] = drawing;
        put(*drawing,
            std::get<0>(position) * TILE_PXL,
            std::get<1>(position) * TILE_PXL);
        drawing->show();
        return true;
    } else {
        return false;
    }

}

bool Workspace::removeEntity(uint x, uint y) {
    //Remove from model
    if (level.removeEntity(x, y)){
        //Remove from view
        std::pair<uint, uint> position = std::make_pair(x, y);
        Drawing* drawing = drawings[position];
        drawings.erase(position);
        delete drawing;
        return true;
    } else {
        return false;
    }

}

void Workspace::on_button_clicked(GdkEventButton* button_event) {
    std::cout << "Hello world" << std::endl;
}

uint Workspace::getId(uint x, uint y) {
    return level.getEntity(x, y);
}





