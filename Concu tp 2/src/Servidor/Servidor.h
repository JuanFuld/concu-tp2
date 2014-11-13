
#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>

#include "../Mensajes/Mensaje.h"
#include "../Mensajes/Cola.h"
#include "../Archivo.h"

#include "../Constantes.h"

class Servidor {

	private:
		Cola<Mensaje>* cola;
		Mensaje peticionRecibida;
		Mensaje respuesta;
		Archivo* baseDeDatos;

		int procesarPedidoInfo();
		int procesarAgregado();

	public:
		Servidor ();
		~Servidor ();

		int procesarPedido();

};

#endif /* SERVIDOR_H_ */