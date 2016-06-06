//
// Created by marcos on 23/05/16.
//

#ifndef MEGAMAN_WORKSPACE_H
#define MEGAMAN_WORKSPACE_H
#include "Level.h"
#include "../common/SpriteDispenser.h"
#include "../common/Drawing.h"
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
    Workspace(Level* level);
    ~Workspace();
    void replaceLevel();
    void replaceLevel(string file);
    bool addElement(uint x, uint y, uint id);
    bool removeEntity(uint x, uint y);
    uint getId(uint x, uint y);
    bool validPosition(uint x, uint y);
    const int getScreenWidth() {return screen_width;}
    void save(string file_name);

private:
    Level* level;
    drawing_map_t drawings;
    SpriteDispenser sprites;
    int screen_width;
    Glib::RefPtr<Gdk::Pixbuf> background;

    void clean();
    void resize();
    void refresh();
    void renew();
};


#endif //MEGAMAN_WORKSPACE_H
