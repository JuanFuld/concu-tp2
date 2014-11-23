#include "Cliente.h"

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>

using namespace std;

Cliente::Cliente() {
	this->claveUnicaCliente = getpid();
	this->cola = new Cola<Mensaje>(ARCHIVO_COLA, CLAVE_COLA);
}

Cliente :: ~Cliente() {
	if (cola != NULL){
		delete cola;
		cola = NULL;
	}
}


int Cliente::pedirInformacion (const std::string nombre) {
	mensaje.mtype = PEDIDO;
	/*le paso a la base de datos:
	* a quien contestarle
	* el nombre de por quien pregunto
	*/
	mensaje.clave = claveUnicaCliente;
	strcpy(mensaje.nombre, nombre.c_str());
	
	cola->escribir(mensaje);
	
	return 0;
}

int Cliente :: esperarRespuesta (){
	cola->leer(this->claveUnicaCliente, &mensaje);
	
	cout << "Mensaje recibido: " <<
			mensaje.nombre + SEPARADOR +
			mensaje.direccion + SEPARADOR +
			mensaje.telefono
			<< endl;
	
	return 0;
}

int Cliente::agregarRegistro(const std::string nombre, const std::string telefono, const std::string direccion) {
	mensaje.mtype = AGREGAR;

	strcpy(mensaje.nombre, nombre.c_str());
	strcpy(mensaje.telefono, telefono.c_str());
	strcpy(mensaje.direccion, direccion.c_str());
	
	cola->escribir(mensaje);
	
	return 0;
}
