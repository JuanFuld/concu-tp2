#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>

#include "../Mecanismos_Concu/Mensajes/Cola.h"
#include "../Mecanismos_Concu/Mensajes/Mensaje.h"
#include "../Mecanismos_Concu/Locks/LockFile.h"
#include "../Mecanismos_Concu/Memoria_Compartida/MemoriaCompartida.h"

#include "../Constantes.h"

class Cliente {

	private:
		Mensaje mensaje; //Mensaje que envia
		int claveUnicaCliente;
		
		Cola<Mensaje>* cola;
		MemoriaCompartida<int>* coordClaveUnica;
		LockFile* lockClave;

	public:
		Cliente ();
		~Cliente();
		
		int pedirInformacion ( const std::string nombre );
		int esperarRespuesta();
		int agregarRegistro ( const std::string nombre, const std::string telefono, const std::string direccion );
		
};

#endif /* CLIENTE_H_ */
