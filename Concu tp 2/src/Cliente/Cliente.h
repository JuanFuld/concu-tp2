#ifndef CLIENTE_HPP_
#define CLIENTE_HPP_

#include "../Mecanismos_Concu/Mensajes/Cola.h"
#include "../Mecanismos_Concu/Mensajes/Mensaje.h"

using namespace std;

class Cliente {
	private:
		int id;
		Cola<Mensaje>* colaEnvios;
		Cola<Mensaje>* colaArrivos;
		Mensaje pedido; // que envia
		Mensaje respuesta; // que recibe
	public:
		Cliente();
		~Cliente();
		bool crear();
		void obtenerRegistro(const string nombre);
		void agregarRegistro(const string nombre, const string telefono, const string direccion);
};



#endif /* CLIENTE_HPP_ */
