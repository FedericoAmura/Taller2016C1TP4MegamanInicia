/*
 * server_main.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: nicolas
 */

#include <stdlib.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <glog/logging.h>

#include "Server.h"

#define POS_PUERTO 1

/*crea el server y lo ejecuta, atrapando las excepciones que pueda tirar*/
int main(int argc, char* argv[]){
	//seteo direcciones de los archivos log
	google::SetLogDestination(google::INFO,"log/server/server.INFO");
	google::SetLogDestination(google::ERROR,"log/server/server.ERROR");
	google::SetLogDestination(google::FATAL,"log/server/server.FATAL");
	FLAGS_logbuflevel=-1;//escribe los mensajes al instante
	google::InitGoogleLogging(argv[0]);//inicializa logger
	if(argc==2)try{
		Server server(strtol(argv[POS_PUERTO], NULL, 10));
		server.correrServer();
	}catch(std::exception& e){
		LOG(FATAL) << e.what();
	}catch(std::runtime_error& e){
		LOG(FATAL) << e.what();
	}
	LOG(INFO)<<"programa server finalizado";
}



