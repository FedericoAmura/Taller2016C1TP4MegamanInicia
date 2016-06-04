#include "Drawing.h"

#include <gdkmm/general.h> // set_source_pixbuf()

Drawing::Drawing() {
}

void Drawing::setImage(const std::string &path, const int width, const int height, bool flip) {
	image = Gdk::Pixbuf::create_from_file(path,width,height,0);
	if (!image) return;
	if (flip) image = image->flip(true);
	set_size_request(width, height);
}

Drawing::~Drawing() {
}

bool Drawing::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
	if (!image) return false;

	//Dibujo la imagen de fondo
	cr->save();
	Gdk::Cairo::set_source_pixbuf(cr,image);
	cr->paint();
	cr->restore();

	return true;
}
