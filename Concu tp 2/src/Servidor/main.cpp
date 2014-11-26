
#ifdef SERVIDOR

#include <iostream>
#include "Servidor.h"
#include "../Mecanismos_Concu/Seniales/SignalHandler.h"
#include "../Mecanismos_Concu/Seniales/SIGINT_Handler.h"

using namespace std;

int main (int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	Servidor* servidor = new Servidor();
	if (servidor == NULL) {
		cout << "No se pudo crear el servidor." << endl;
		return 1;
	}

	cout << "Servidor iniciado." << endl;

	while(sigint_handler.getGracefulQuit() == 0) {
		servidor->procesarPedido();
	}

	cout << "Servidor terminado." << endl;

	SignalHandler::destruir();

	delete servidor;
	servidor = NULL;

	return 0;
}

#endif





