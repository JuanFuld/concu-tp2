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

#include "Constantes.h"

class Archivo{

private:
	std::string ruta;
	std::fstream arch;
public:

	Archivo(std::string ruta);

	int abrir();
	int cerrar();

	std::string buscarRegistro (std::string clave);
	int agregarRegistro (std::string regNuevo);

};

#endif
