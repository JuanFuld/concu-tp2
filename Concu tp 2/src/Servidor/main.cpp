#ifdef SERVIDOR

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <stdlib.h>

#include "../Seniales/SIGINT_Handler.h"
#include "../Seniales/SignalHandler.h"

#include "Servidor.h"
#include "../Constantes.h"

using namespace std;

int main (int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler :: getInstance()->registrarHandler ( SIGINT,&sigint_handler );

	Servidor servidor;

	while ( sigint_handler.getGracefulQuit() == 0 ) {

		servidor.procesarPedido();

	}

//	servidor.persistir();

	SignalHandler :: destruir ();
	return 0;
}

#endif





