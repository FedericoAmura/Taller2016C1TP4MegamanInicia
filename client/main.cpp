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
#include <glog/logging.h>

#include "ClientWindow.h"

#define NO_ERROR 0

int main(int argc, char *argv[]) try {
	//seteo direcciones de los archivos log
	google::SetLogDestination(google::INFO,"log/cliente/client.INFO");
	google::SetLogDestination(google::ERROR,"log/cliente/client.ERROR");
	google::SetLogDestination(google::FATAL,"log/cliente/client.FATAL");
	FLAGS_logbuflevel=-1;//escribe los mensajes al instante
	google::InitGoogleLogging(argv[0]);//inicializa logger

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
