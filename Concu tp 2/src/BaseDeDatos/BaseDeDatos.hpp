/*
 * BaseDeDatos.h
 *
 *  Created on: Nov 12, 2014
 *      Author: juan
 */
#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include <fstream>

#include "../Mecanismos_Concu/Mensajes/Mensaje.h"
#include "../Constantes.h"

class BaseDeDatos {

private:
	std::string ruta;
	std::fstream arch;

public:

	BaseDeDatos(std::string ruta);
	~BaseDeDatos();
	int abrir();
	int cerrar();

	std::string obtenerRegistro(std::string clave);
	int agregarRegistro (std::string regNuevo);

};

#endif
