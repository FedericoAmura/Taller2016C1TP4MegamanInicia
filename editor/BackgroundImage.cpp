//
// Created by marcos on 11/06/16.
//

#include <gdkmm.h>
#include "BackgroundImage.h"

void BackgroundImage::setImage(const std::string& path, const int width, const int height) {
    image = Gdk::Pixbuf::create_from_file(path);
    if (!image) return;
    setSize(width, height);
}

bool BackgroundImage::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    if (!image) return false;

    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr,image);
    cr->paint();
    cr->restore();

    return true;
}

void BackgroundImage::setSize(const int width, const int height) {
    set_size_request(width, height);
}

int BackgroundImage::getLength() {
    return image->get_width();
}



