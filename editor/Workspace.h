//
// Created by marcos on 23/05/16.
//

#ifndef MEGAMAN_WORKSPACE_H
#define MEGAMAN_WORKSPACE_H
#include "Level.h"
#include "SpriteDispenser.h"
#include "../client/MyArea.h"
#include <vector>
#include <map>
#include <gtkmm/drawingarea.h>
#include <gtkmm/fixed.h>

using std::vector;
using std::pair;

typedef unsigned int uint;
typedef std::map<pair<uint, uint>, Drawing* > drawing_map_t;

class Workspace : public Gtk::Fixed {
public:
    Workspace(Level& level);
    ~Workspace();
    bool addElement(uint x, uint y, uint id);
    bool removeEntity(uint x, uint y);
    uint getId(uint x, uint y);
    void on_button_clicked(GdkEventButton* button_event);
private:
    Level& level;
    drawing_map_t drawings;
    SpriteDispenser sprites;
    Glib::RefPtr<Gdk::Pixbuf> background;
    void resize();

    //callbacks



protected:

};


#endif //MEGAMAN_WORKSPACE_H
