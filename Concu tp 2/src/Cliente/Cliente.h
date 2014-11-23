#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <string>
#include "../Mecanismos_Concu/Mensajes/Cola.h"
#include "../Mecanismos_Concu/Mensajes/Mensaje.h"
#include "../Constantes.h"

using namespace std;

class Cliente {
	private:
		Mensaje mensaje; //Mensaje que envia
		int claveUnicaCliente;
		Cola<Mensaje>* cola;

	public:
		Cliente ();
		~Cliente();
		int pedirInformacion(const string nombre);
		int esperarRespuesta();
		int agregarRegistro(const string nombre, const string telefono, const string direccion);
};

#endif /* CLIENTE_H_ */
