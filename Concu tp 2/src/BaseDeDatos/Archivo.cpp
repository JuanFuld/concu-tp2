/*
 * Archivo.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: juan
 */

#include "Archivo.h"

Archivo::Archivo(std::string ruta) {
	this->ruta = ruta;
}

int Archivo::abrir() {
	arch.open(ruta.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	if (!arch.is_open()) {
		return -1;
	}
	return 0;
}

int Archivo::cerrar() {
	arch.close();
	return 0;
}

Mensaje Archivo::parsear(std::string reg) {
	Mensaje registro;

	//parsea el registro recibido
	std::string nombre,tel,dir;

	int posSeparador = reg.find(SEPARADOR);
	int posSeparador2 = reg.rfind(SEPARADOR);

	nombre = reg.substr(0,posSeparador);
	dir = reg.substr(posSeparador + 1, posSeparador2 - posSeparador - 1 );
	tel = reg.substr(posSeparador2 + 1);

	strcpy(registro.nombre, nombre.c_str());
	strcpy(registro.direccion, dir.c_str());
	strcpy(registro.telefono, tel.c_str());

	return registro;
}

Mensaje Archivo::buscarRegistro(std::string clave) {
	std::string reg;
	std::string nombre;

	arch.seekg(0);
	while (getline(arch,reg)) {
		int posSeparador = reg.find(SEPARADOR);
		nombre = reg.substr(0,posSeparador);
		//todo asumo que nombre es una clave unica
		if (nombre.compare(clave) == 0) {
			return parsear(reg);
		}
	}
	return NULL;
}

int Archivo::agregarRegistro(std::string regNuevo) {
	arch << regNuevo;
	return 0;
}


