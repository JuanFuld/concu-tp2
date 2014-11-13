/*
 * Archivo.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: juan
 */

#include "Archivo.h"

Archivo :: Archivo(std::string ruta){
	this->ruta = ruta;
}

int Archivo :: abrir(){
	arch.open(ruta.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

	if (!arch.is_open()){
		return -1;
	}

	return 0;
}

int Archivo :: cerrar(){
	arch.close();
	return 0;
}

std::string Archivo :: buscarRegistro (std::string clave){
	std::string reg;
	std::string nombre;

	arch.seekg ( 0 );
	while ( getline (arch,reg) )
	{
		int posSeparador = reg.find(SEPARADOR);
		nombre = reg.substr(0,posSeparador);
		//todo asumo que nombre es una clave unica
		if (nombre.compare(clave) == 0){
			return reg;
		}

	}

	return SIN_RESULTADOS;
}

int Archivo ::  agregarRegistro (std::string regNuevo){

	arch << regNuevo;

	return 0;
}


