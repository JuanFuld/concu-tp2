
#ifdef CLIENTE

#include <unistd.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include "../Constantes.h"
#include "Cliente.h"

bool longitudValida(string str, unsigned int longMax) {
	if (str.length() > longMax) {
		cout << "La información ingresada excede la longitud máxima permitida!" << endl;
		return false;
	}
	return true;
}

int tomarOperacion(int &operacion) {
	string op;
	do {
		cout << "Cliente: " << getpid() << endl;
		cout << "Ingrese la operacion a realizar" << endl;
		cout << OP_PEDIDO << ": Pedido de informacion" << endl;
		cout << OP_INGRESO << ": Ingreso de datos" << endl;
		cout << OP_FINAL << ": Fin del cliente" << endl;
		getline(cin, op);
		operacion = atoi(op.c_str());
	} while (operacion > OP_FINAL || operacion < OP_PEDIDO);

	return  0;
}

string tomarDatos(string mensaje) {
	string str;
	cout << mensaje + ":" << endl;
	getline(cin, str);
	return str;
}

int main(int argc, char** argv) {
	Cliente* cliente = new Cliente();
	if (cliente == NULL) {
		cout << "No se pudo crear el cliente." << endl;
		return 1;
	}
	if (!cliente->crear()) {
		cout << "El Servidor no ha sido abierto aún. Inténtelo más tarde." << endl;
		delete cliente;
		cliente = NULL;
		return 1;
	}

	int operacion = 0;
	string nombre = "";
	string telefono = "";
	string direccion = "";

	tomarOperacion(operacion);

	while (operacion != OP_FINAL) {
		switch (operacion) {
			case OP_PEDIDO:
				nombre = tomarDatos("Ingrese nombre a consultar");
				cliente->obtenerRegistro(nombre);
				break;

			case OP_INGRESO:
				nombre = tomarDatos("Ingrese nombre agregar a la base de datos");
				if (!longitudValida(nombre, LONG_MAX_NOMBRE))
					break;

				telefono = tomarDatos("Ingrese telefono");
				if (!longitudValida(telefono, LONG_MAX_TELEFONO))
					break;

				direccion = tomarDatos("Ingrese direccion");
				if (!longitudValida(direccion, LONG_MAX_DIRECCION))
					break;

				cliente->agregarRegistro(nombre, telefono, direccion);
				break;

			default:
				cout << "Operacion invalida, no pudo ser procesada" << endl;
				break;
		}
		tomarOperacion(operacion);
	}
	cout << "Cliente finalizado." << endl;
	delete cliente;
	cliente = NULL;
	return 0;
}

#endif

