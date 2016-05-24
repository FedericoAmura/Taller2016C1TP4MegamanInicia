//
// Created by marcos on 23/05/16.
//

#ifndef MEGAMAN_WORKSPACECELL_H
#define MEGAMAN_WORKSPACECELL_H

#include <gtkmm/drawingarea.h>
#include <string>
#include "SpriteDispenser.h"

using std::string;

class CellDrawer : public Gtk::DrawingArea {
private:
    Glib::RefPtr<Gdk::Pixbuf> image;
    SpriteDispenser sprites;
    uint side_len;

public:
    explicit CellDrawer();
    void setImage(const std::string &file, const int width, const int height);
    void setSize(const uint size);
    virtual ~CellDrawer() {};

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};


#endif //MEGAMAN_WORKSPACECELL_H
