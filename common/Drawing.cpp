#include "Drawing.h"

#include <gdkmm/general.h> // set_source_pixbuf()
#include <syslog.h>
#include <exception>
#include <iostream>

Drawing::Drawing() :
	width(0),
	height(0),
	percent(0) {
}

void Drawing::setImage(const std::string &path, const int width, const int height, bool flip) {
	image = Gdk::Pixbuf::create_from_file(path,width,height,0);
	ruta = path;
	if (!image) return;
	if (flip) image = image->flip(true);
	this->width = width;
	this->height = height;
	set_size_request(width, height);
}

Drawing::~Drawing() {
}

bool Drawing::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	if (!image) return false;

	Gtk::Allocation allocation = get_allocation();
	const int allocationWidth = allocation.get_width();
	const int allocationHeight = allocation.get_height();
	if (allocationWidth==0 || allocationHeight==0) return false;

	try {
		//Dibujo la imagen de fondo
		cr->save();
		try{Gdk::Cairo::set_source_pixbuf(cr,image);}catch(...){}
		cr->paint();
		cr->restore();

		if (percent != 0) {
			cr->save();
			cr->set_line_width(width);
			cr->set_source_rgb(0.337, 0.612, 0.117);
			cr->move_to(width/2,height);
			cr->line_to(width/2,height*(1-(float)percent/100));
			cr->stroke();
			cr->restore();
		}
	} catch (const std::exception &e) {
		syslog(LOG_CRIT, "[Crit] on_draw - Error!: %s", e.what());
	} catch(...) {
		syslog(LOG_CRIT, "[Crit] on_draw - Unknown error!");
	}

	return true;
}

void Drawing::setPercent(int percent) {
	this->percent = percent;
}
