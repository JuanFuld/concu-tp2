/*
 * Archivo.h
 *
 *  Created on: Nov 12, 2014
 *      Author: juan
 */
#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include <fstream>

#include "../Mecanismos_Concu/Mensajes/Mensaje.h"
#include "../Constantes.h"

class Archivo{

private:
	std::string ruta;
	std::fstream arch;

	Mensaje parsear(std::string registro);
public:

	Archivo(std::string ruta);

	int abrir();
	int cerrar();

	Mensaje buscarRegistro (std::string clave);
	int agregarRegistro (std::string regNuevo);

};

#endif
