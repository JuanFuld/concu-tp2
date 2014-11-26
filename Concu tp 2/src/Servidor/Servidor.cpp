#include "Servidor.h"
#include "../Constantes.h"
#include <cstring>

using namespace std;

Servidor::Servidor() {
	colaArribos = new Cola<Mensaje>();
	if (colaArribos != NULL) {
		colaArribos->crear(ARCHIVO_COLA,CLAVE_COLA_1);
	}
	colaEnvios = new Cola<Mensaje>();
	if (colaEnvios != NULL) {
		colaEnvios->crear(ARCHIVO_COLA,CLAVE_COLA_2);
	}
	baseDeDatos = new BaseDeDatos(RUTA_BASE_DE_DATOS);

}

Servidor::~Servidor() {
	if (colaArribos != NULL) {
		colaArribos->destruir(); // Solo el Servidor la destruye
		delete colaArribos;
		colaArribos = NULL;
	}
	if (colaEnvios != NULL) {
		colaEnvios->destruir(); // Solo el Servidor la destruye
		delete colaEnvios;
		colaEnvios = NULL;
	}
	if (baseDeDatos != NULL) {
		baseDeDatos->cerrar();
		delete baseDeDatos;
		baseDeDatos = NULL;
	}
}


int Servidor::procesarPedido() {

	std::cout << "Esperando pedido..." << endl;

	if (colaArribos->leer(0, &peticionRecibida) == -1) {
		std::cout << "Error al leer en la cola o interrupcion del servidor" << std::endl;
		return -1;
	}

	respuesta.mtype = peticionRecibida.mtype; // Responde a quien lo contacto
	strcpy(respuesta.nombre, peticionRecibida.nombre);

	switch (peticionRecibida.op) {
		case CONSULTA:
			procesarConsulta();
			break;
		case AGREGADO:
			procesarAgregado();
			break;
		default:
			std::cout << "El servidor recibió una operación invalida, no será procesado." << std::endl;
			std::cout << peticionRecibida.op << std::endl;
			return -1;
	}
	return 0;
}

void Servidor::parsear(string registro) {
	//parsea el registro recibido y carga el resultado en this.respuesta
	string tel, dir;

	int posSeparador = registro.find(SEPARADOR);
	int posSeparador2 = registro.rfind(SEPARADOR);

	dir = registro.substr(posSeparador + 1, posSeparador2 - posSeparador - 1 );
	tel = registro.substr(posSeparador2 + 1);

	strcpy(respuesta.direccion, dir.c_str());
	strcpy(respuesta.telefono, tel.c_str());
}

int Servidor::procesarConsulta() {
	//obtiene nombre a buscar en la base de datos
	string nombreABuscar = peticionRecibida.nombre;

	cout << "Recibida operación CONSULTA del Cliente: " << peticionRecibida.mtype << endl;
	cout << "Mensaje recibido: "<< endl;
/*	cout << "    mtype:  " << peticionRecibida.mtype << endl;
	cout << "    op:     " << peticionRecibida.op << endl;
	cout << "    status: " << peticionRecibida.status << endl;*/
	cout << "    Nombre: " << peticionRecibida.nombre << endl;
/*	cout << "    Dir:    " << peticionRecibida.direccion << endl;
	cout << "    Tel:    " << peticionRecibida.telefono << endl;*/

	//obtiene la informacion requerida de la base de datos
	int existe = NOEXISTE;
	string registro = baseDeDatos->obtenerRegistro(nombreABuscar);
	if (!registro.compare("") == 0) {
		existe = EXISTE;
		parsear(registro);
	}

	//responde
	if (responder(existe) == -1) {
		cout << "Error al intentar responder al Cliente " << peticionRecibida.mtype << endl;
		return -1;
	}

	return 0;
}

int Servidor::responder(int existe) {
	respuesta.status = existe;
	respuesta.op = RESPUESTA;

	cout << "Respondiendo al Cliente: " << respuesta.mtype << endl;

	return colaEnvios->escribir(respuesta);
}

int Servidor::procesarAgregado() {
	cout << "Recibida operación AGREGADO del Cliente: " << peticionRecibida.mtype << endl;
	cout << "Mensaje recibido: "<< endl;

	cout << "    Nombre: " << peticionRecibida.nombre << endl;
	cout << "    Dir:    " << peticionRecibida.direccion << endl;
	cout << "    Tel:    " << peticionRecibida.telefono << endl;

	string textoPeticion = peticionRecibida.nombre + SEPARADOR +
			peticionRecibida.direccion + SEPARADOR + peticionRecibida.telefono + NEWLINE;

	int existe = NOEXISTE;
	if (baseDeDatos->agregarRegistro(textoPeticion) == -1) {
		existe = EXISTE;
		cout << "El Cliente " << peticionRecibida.mtype << " intentó agregar un registro ya existente." << endl;
	}
	if (responder(existe) == -1) {
		cout << "Error al intentar responder al Cliente " << peticionRecibida.mtype << endl;
		return -1;
	}
	return 0;
}
