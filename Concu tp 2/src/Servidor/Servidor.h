
#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>

#include "../Mecanismos_Concu/Mensajes/Mensaje.h"
#include "../Mecanismos_Concu/Mensajes/Cola.h"
#include "../BaseDeDatos/Archivo.h"

#include "../Constantes.h"

class Servidor {

	private:
		Cola<Mensaje>* cola;
		Mensaje peticionRecibida;
		Archivo* baseDeDatos;

		int procesarPedidoInfo();
		int procesarAgregado();
		int responder(int numeroCliente, Mensaje& respuesta);

	public:
		Servidor ();
		~Servidor ();

		int procesarPedido();

};

#endif /* SERVIDOR_H_ */
