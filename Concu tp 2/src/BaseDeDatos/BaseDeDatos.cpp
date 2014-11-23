/*
 * BaseDeDatos.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: juan
 */

#include "BaseDeDatos.hpp"
#include <cstring>
#include <iostream>
using namespace std;

BaseDeDatos::BaseDeDatos(std::string ruta) {
	this->ruta = ruta;
}

int BaseDeDatos::abrir() {
	arch.open(ruta.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	if (!arch.is_open()) {
		cout << "Uhmm no pude abrir" << endl;
		return -1;
	}
	return 0;
}

int BaseDeDatos::cerrar() {
	arch.close();
	return 0;
}

string BaseDeDatos::obtenerRegistro(string clave) {
	string aux = "";
	string reg = "";
	string nombre;
	abrir();
	arch.seekg(0);
	while (getline(arch,aux)) {
		int posSeparador = aux.find(SEPARADOR);
		nombre = aux.substr(0,posSeparador);
		if (nombre.compare(clave) == 0) {
			reg = aux;
			break;
		}
	}
	cerrar();
	return reg;
}

int BaseDeDatos::agregarRegistro(std::string regNuevo) {
	// Si el registro no existe, lo agrego:
	if (obtenerRegistro(regNuevo.substr(0,regNuevo.find(SEPARADOR))).compare("") == 0) {
		abrir();
		arch << regNuevo;
		cerrar();
		return 0;
	}
	return -1;
}

BaseDeDatos::~BaseDeDatos() {
	ruta = "";
	cerrar();
}

