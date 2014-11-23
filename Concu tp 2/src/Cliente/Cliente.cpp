#include "Cliente.h"
#include "../Constantes.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;

Cliente::Cliente() {
	colaEnvios = new Cola<Mensaje>();
	colaArribos = new Cola<Mensaje>();
	id = getpid();
}

Cliente::~Cliente() {
	if (colaEnvios != NULL) {
		// La cola la libera el Servidor
		delete colaEnvios;
		colaEnvios = NULL;
	}
	if (colaArribos != NULL) {
		// La cola la libera el Servidor
		delete colaArribos;
		colaArribos = NULL;
	}
}

bool Cliente::crear() {
	// Si el Servidor fue lanzado, entonces creo las colas:
	if (colaEnvios->existe(ARCHIVO_COLA, CLAVE_COLA)) {
		colaEnvios->crear(ARCHIVO_COLA, CLAVE_COLA);
		if (colaArribos->existe(ARCHIVO_COLA, CLAVE_COLA)) {
			colaArribos->crear(ARCHIVO_COLA, CLAVE_COLA);
			return true;
		}
		return false;
	}

	// Si el Servidor no fue lanzado, las colas no existen
	return false;
}

void Cliente::obtenerRegistro(const string nombre) {
	pedido.mtype = id; // Para que el Servidor sepa a quien contestarle
	pedido.op = CONSULTA;
	strcpy(pedido.nombre, nombre.c_str()); // Por quien pregunto

	if (colaEnvios->escribir(pedido) == -1) {
		cout << "Error al intentar contactar al Servidor" << endl;
		return;
	}
	cout << "Consulta enviada" << endl;
	/*
	cout << "   mtype:  " << pedido.mtype << endl;
	cout << "   op:     " << pedido.op << endl;
	cout << "   Nombre: " << pedido.nombre << endl;
	*/

	cout << "Esperando respuesta..." << endl;
	if (colaArribos->leer(id, &respuesta) == -1) {
		cout << "Error al intentar escuchar al Servidor" << endl;
		return;
	}

	if (respuesta.op != RESPUESTA) {
		cout << "Se esperaba una respuesta del Servidor." << endl;
		return;
	}

	if (respuesta.status == NOEXISTE) {
		cout << "No existe el registro con clave '" << nombre << "' en la base de datos." << endl;
		return;
	}

	cout << "Mensaje recibido:" << endl;
	/*
	cout << "   mtype:     " << respuesta.mtype << endl;
	cout << "   op:        " << respuesta.op << endl;
	cout << "   status:    " << respuesta.status << endl;
	*/
	cout << "   Nombre:    " << respuesta.nombre << endl;
	cout << "   Direccion: " <<	respuesta.direccion << endl;
	cout << "   Telefono:  " << respuesta.telefono << endl;
}

void Cliente::agregarRegistro(const string nombre, const string telefono, const string direccion) {
	pedido.mtype = id;
	pedido.op = AGREGADO;
	strcpy(pedido.nombre, nombre.c_str());
	strcpy(pedido.telefono, telefono.c_str());
	strcpy(pedido.direccion, direccion.c_str());

	if (colaEnvios->escribir(pedido) == -1) {
		cout << "Error al intentar conectar con el Servidor" << endl;
		return;
	}

	cout << "Mensaje enviado:" << endl;
	/*
	cout << "   mtype:     " << pedido.mtype << endl;
	cout << "   op:        " << pedido.op << endl;
	cout << "   status:    " << pedido.status << endl;
	*/
	cout << "   Nombre:    " << pedido.nombre << endl;
	cout << "   Direccion: " <<	pedido.direccion << endl;
	cout << "   Telefono:  " << pedido.telefono << endl;

	cout << "Esperando confirmacion..." << endl;
	if (colaArribos->leer(id, &respuesta) == -1) {
		cout << "Error al intentar escuchar al Servidor" << endl;
		return;
	}

	if (respuesta.op != RESPUESTA) {
		cout << "Se esperaba una respuesta del Servidor." << endl;
		return;
	}

	if (respuesta.status == EXISTE) {
		cout << "No se pudo agregar el nuevo registro. Causa:" << endl;
		cout << "   El registro ya se encuentra" << endl;
		return;
	}

	cout << "Registro agregado!" << endl;
}
