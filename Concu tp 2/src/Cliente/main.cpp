
#ifdef CLIENTE

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "../Constantes.h"
#include "Cliente.h"

bool longitudValida(std::string str, unsigned int longMax){

	if (str.length() > longMax){
		std::cout << "La información ingresada excede la longitud máxima permitida" << std::endl;
		return false;
	}

	return true;
}

int tomarOperacion(int& operacion){
	
	std::string op;

	do{
		std::cout << "Ingrese la operacion a realizar" << std::endl;
		std::cout << OP_PEDIDO << ": Pedido de informacion" << std::endl;
		std::cout << OP_INGRESO << ": Ingreso de datos" << std::endl;
		std::cout << OP_FINAL << ": Fin del cliente" << std::endl;
	
		getline(std::cin, op);
		operacion = atoi(op.c_str());
	}
	while (operacion != OP_PEDIDO && operacion != OP_INGRESO && operacion != OP_FINAL);

	return  0;
}



int main (int argc, char** argv) {
	
	// cliente
	int operacion = 0;
	std::string nombre = "";
	std::string telefono = "";
	std::string direccion = "";

	Cliente cliente;
			
	tomarOperacion(operacion);
	
	while (operacion != OP_FINAL){
				
		switch (operacion) {
	
			case OP_PEDIDO:
				std::cout << "Ingrese nombre a consultar";
				getline(std::cin, nombre);
			
				cliente.pedirInformacion (  nombre );
				cliente.esperarRespuesta();
				break;	
			
			case OP_INGRESO:
				std::cout << "Ingrese nombre agregar a la base de datos";
				getline(std::cin, nombre);
				
				if (! longitudValida (nombre, LONG_MAX_NOMBRE) ){
					break;
				}
				
				std::cout << "Ingrese telefono";
				getline(std::cin, telefono);
				
				if (! longitudValida (telefono, LONG_MAX_TELEFONO)){
					break;
				}
				
				std::cout << "Ingrese direccion";
				getline(std::cin, direccion);
				
				if (! longitudValida (telefono, LONG_MAX_DIR)){
					break;
				}			
			
				cliente.agregarRegistro ( nombre, telefono, direccion );
				break;	
				
			default:
				std::cout << "Operacion invalida, no pudo ser procesada" << std::endl;
				break;	
			
		}
				
		tomarOperacion(operacion);
	}

	return 0;
}

#endif

