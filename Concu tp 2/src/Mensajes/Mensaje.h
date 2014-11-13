#ifndef MENSAJES_H_
#define MENSAJES_H_

#include "../Constantes.h"

typedef struct Mensaje {
	long mtype;
	int clave;
	char nombre[LONG_MAX_NOMBRE];
	char telefono[LONG_MAX_TELEFONO];
	char direccion[LONG_MAX_DIR];
};

#endif /* MENSAJES_H_ */
