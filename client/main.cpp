//============================================================================
// Name        : main.cpp
// Author      : Grupo
// Version     :
// Copyright   : Do not copy
// Description : Megaman Inicia Client
//============================================================================


#include <glibmm/refptr.h>
#include <gtkmm/application.h>
#include <syslog.h>
#include <exception>

#include "ClientWindow.h"

#define NO_ERROR 0

int main(int argc, char *argv[]) try {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "Megaman.Begins");

	ClientWindow win;

	app->run(win);

	return NO_ERROR;
} catch (const std::exception &e) {
	syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
	return 1;
} catch(...) {
	syslog(LOG_CRIT, "[Crit] Unknown error!");
	return 1;
}
