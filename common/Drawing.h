#ifndef GTKMM_EXAMPLE_SCREENAREA_H
#define GTKMM_EXAMPLE_SCREENAREA_H

#include <cairomm/context.h>
#include <cairomm/refptr.h>
#include <gdkmm/pixbuf.h>
#include <glibmm/refptr.h>
#include <gtkmm/drawingarea.h>
#include <string>

class Drawing : public Gtk::DrawingArea {
private:
	Glib::RefPtr<Gdk::Pixbuf> image;
	std::string ruta;
	int width;
	int height;
	int percent;

public:
	explicit Drawing();
	virtual ~Drawing();

	void setImage(const std::string &path, const int width, const int height, bool flip = false);
	void setPercent(int percent);

protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

#endif // GTKMM_EXAMPLE_SCREENAREA_H
