#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include <cstring>

static const std::string ARCHIVO_COLA = "/etc";

static const int CLAVE_COLA_1 = 10;
static const int CLAVE_COLA_2 = 12;

static const int OP_PEDIDO = 1;
static const int OP_INGRESO = 2;
static const int OP_FINAL = 3;

static const int CONSULTA = 1; //op para pedir informacion
static const int AGREGADO = 2; //op para agregar un registro a la base de datos
static const int RESPUESTA = 0;
static const int AGREGADO_OK = 3;
static const int AGREGADO_NOK = 3;

static const int NOEXISTE = 1;
static const int EXISTE = 0;

static const unsigned int LONG_MAX_NOMBRE = 61 ;
static const unsigned int LONG_MAX_TELEFONO = 13;
static const unsigned int LONG_MAX_DIRECCION = 120;

static const std::string RUTA_BASE_DE_DATOS = "BaseDeDatos.txt";
static const std::string SEPARADOR = ",";
static const std::string NEWLINE = "\n";

#endif /*CONSTANTES_H_*/
