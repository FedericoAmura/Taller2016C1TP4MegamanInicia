#include "MyArea.h"

#include <gdkmm/general.h> // set_source_pixbuf()

Drawing::Drawing() {
}

void Drawing::setImage(const std::string &rutaImagen, const int width, const int height) {
	image = Gdk::Pixbuf::create_from_file(rutaImagen,width,height,1);
	if (image) {
		image = image->add_alpha(true,240,255,0);	//Saco ese amarillo horrible de fondo
		set_size_request(width, height);
	}
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
