//
// Created by marcos on 11/06/16.
//

#ifndef MEGAMAN_BACKGROUNDIMAGE_H
#define MEGAMAN_BACKGROUNDIMAGE_H

#include <gtkmm/drawingarea.h>

class BackgroundImage : public Gtk::DrawingArea {
private:
    Glib::RefPtr<Gdk::Pixbuf> image;

public:
    explicit BackgroundImage() {};
    BackgroundImage(const BackgroundImage&){}
    void setSize(const int width, const int height);
    void setImage(const std::string &path, const int width, const int height);
    virtual ~BackgroundImage() {};
    int getLength();

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};


#endif //MEGAMAN_BACKGROUNDIMAGE_H
