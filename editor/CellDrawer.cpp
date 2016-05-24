//
// Created by marcos on 23/05/16.
//

#include <gdkmm.h>
#include <giomm.h>
#include <iostream>
#include "CellDrawer.h"
#include "SpriteDispenser.h"
#include "../entities.h"

CellDrawer::CellDrawer() {
    try {
        image = Gdk::Pixbuf::create_from_file(sprites.get(SPARKMAN));
    } catch(const Gio::ResourceError& ex) {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    } catch(const Gdk::PixbufError& ex) {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }
    if (image){
        set_size_request(image->get_width(), image->get_height());
    }
}

void CellDrawer::setImage(const string& file, const int width, const int height) {
    side_len = 25;
    image = Gdk::Pixbuf::create_from_file(file,width,height,1);
    if (image) {
        set_size_request(side_len, side_len);
    }
}

void CellDrawer::setSize(const uint size) {
    image = image->scale_simple(size, size, Gdk::INTERP_BILINEAR);
}

bool CellDrawer::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    if (!image) {
        return false;
    }
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    Gdk::Cairo::set_source_pixbuf(cr, image, (width - image->get_width())/2, (height - image->get_height())/2);
    cr->paint();

    return true;
}





