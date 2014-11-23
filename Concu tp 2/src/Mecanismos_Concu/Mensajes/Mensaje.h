#ifndef MENSAJES_H_
#define MENSAJES_H_

#include "../../Constantes.h"

struct Mensaje {
	long mtype;
	char nombre[LONG_MAX_NOMBRE];
	char telefono[LONG_MAX_TELEFONO];
	char direccion[LONG_MAX_DIRECCION];
	int status; // Estado (Existe, No Existe)
	int op;	// Operacion a realizar en la BD

};

#endif /* MENSAJES_H_ */
