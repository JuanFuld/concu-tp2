
#ifndef SERVIDOR_HPP_
#define SERVIDOR_HPP_

#include "../Mecanismos_Concu/Mensajes/Cola.h"
#include "../Mecanismos_Concu/Mensajes/Mensaje.h"
#include "../BaseDeDatos/BaseDeDatos.hpp"

using namespace std;

class Servidor {
	private:
		Cola<Mensaje>* colaArrivos;
		Cola<Mensaje>* colaEnvios;
		Mensaje peticionRecibida;
		Mensaje respuesta;
		BaseDeDatos* baseDeDatos;

		void parsear(string registro);
		int procesarConsulta();
		int procesarAgregado();
		int responder(int existe);

	public:
		Servidor();
		~Servidor();
		int procesarPedido();
};



#endif /* SERVIDOR_HPP_ */
