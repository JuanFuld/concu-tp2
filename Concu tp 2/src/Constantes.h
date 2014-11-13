#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include "string.h"

static const std::string ARCHIVO_COLA = "/etc";
static const std::string ARCHIVO_FLOCK = "./Locks/LockFile.h";
static const std::string ARCHIVO_SHMEM = "/etc";

static const int CLAVE_COLA = 10; 
static const int CLAVE_FLOCK = 11; 
static const int CLAVE_SHMEM = 12; 

static const int OP_PEDIDO = 1;
static const int OP_INGRESO = 2;
static const int OP_FINAL = 3;

//Dejar ID de PEDIDO menor al de AGREGAR!
static const int PEDIDO = 1; //tipo msj para pedir informacion
static const int AGREGAR = 2; //tipo msj para agregar un registro a la base de datos

static const unsigned int LONG_MAX_NOMBRE = 61 ;
static const unsigned int LONG_MAX_TELEFONO = 13;
static const unsigned int LONG_MAX_DIR = 120;

static const std::string RUTA_BASE_DE_DATOS = "BaseDeDatos.txt";
static const std::string SEPARADOR = ",";
static const std::string NEWLINE = "\n";
static const std::string SIN_RESULTADOS = "No hay entradas en la base de datos bajo ese nombre";
#endif /*CONSTANTES_H_*/
