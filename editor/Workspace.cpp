//
// Created by marcos on 23/05/16.
//

#include <iostream>
#include <gdkmm.h>
#include "Workspace.h"
#include "../entities.h"

#define SIZE_TRANSFORM 15.5
#define EDGE 2

typedef Glib::RefPtr<Gdk::Pixbuf> Pixbuf;
typedef drawing_map_t::iterator p_iter;

Workspace::Workspace(Level& level)
        : level(level) {
    screen_width = (int) Gdk::screen_height()/SIZE_TRANSFORM;
    resize();
    for (uint i = 0; i < level.getLength() ; ++i){
        for (uint j = 0; j < level.getWidth() ; ++j){
            uint id = level.getEntity(i, j);
            if (id != 0) {
                pair<uint, uint> position = std::make_pair(i, j);
                Drawing* drawing = new Drawing();
                drawing->setImage(sprites.get(id), screen_width, screen_width);
                drawings[position] = drawing;
                put(*drawing,
                    std::get<0>(position) * screen_width,
                    std::get<1>(position) * screen_width);
                drawing->show();
            }
        }
    }
}

void Workspace::resize() {
    set_size_request(level.getLength()*screen_width, level.getWidth()*screen_width);
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
        drawing->setImage(sprites.get(id), screen_width, screen_width);
        drawings[position] = drawing;
        put(*drawing,
            std::get<0>(position) * screen_width,
            std::get<1>(position) * screen_width);
        drawing->show();
        resize();
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
        resize();
        return true;
    } else {
        return false;
    }
}

uint Workspace::getId(uint x, uint y) {
    return level.getEntity(x, y);
}

bool Workspace::validPosition(uint x, uint y) {
    return (x < level.getLength() && y < level.getWidth());
}















