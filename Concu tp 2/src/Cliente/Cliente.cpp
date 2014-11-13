#include "Cliente.h"

Cliente::Cliente() {
	this->claveUnicaCliente = 0;
	this->coordClaveUnica = new MemoriaCompartida<int>();
	this->coordClaveUnica->crear(ARCHIVO_SHMEM, CLAVE_SHMEM);
	
	//obtiene su clave unica par alos mensajes y actualiza la memoria compartida al nuevo valor
	this->lockClave = new  LockFile(ARCHIVO_FLOCK);
	
	this->lockClave->tomarLock();
	this->claveUnicaCliente = coordClaveUnica->leer();
	if (this->claveUnicaCliente == 0) {
		//para inicializar fuera del rango que el servidor toma como mensajes hacia el
		this->claveUnicaCliente = 100;
	} else {
		this->claveUnicaCliente ++;
	}
	this->coordClaveUnica->escribir(claveUnicaCliente);
	this->lockClave->liberarLock();
		
	this->cola = new Cola<Mensaje>(ARCHIVO_COLA, CLAVE_COLA);
}

Cliente :: ~Cliente() {
	if (lockClave != NULL){
		delete lockClave;
		lockClave = NULL;
	}
	
	if (coordClaveUnica != NULL){
		coordClaveUnica->liberar();
		delete coordClaveUnica;
		coordClaveUnica = NULL;
	}

	if (cola != NULL){
		//this->cola->destruir();
		delete cola;
		cola = NULL;
	}
}


int Cliente::pedirInformacion (const std::string nombre) {
	if (!cola->existe()) {
		std::cout << "No se puede comunicar con el servidor. Posiblemente se cerró." << std::endl;
		return -1;
	}

	mensaje.mtype = PEDIDO;
	/*le paso a la base de datos:
	* a quien contestarle
	* el nombre de por quien pregunto
	*/
	mensaje.clave = claveUnicaCliente;
	strcpy(mensaje.nombre, nombre.c_str());
	
	cola->escribir(mensaje);
	
	return 0;
}

int Cliente :: esperarRespuesta (){
	if (!cola->existe()) {
		std::cout << "No se puede comunicar con el servidor. Posiblemente se cerró." << std::endl;
		return -1;
	}

	cola->leer(this->claveUnicaCliente, &mensaje);
	
	std::cout << "Mensaje recibido: " <<
			mensaje.nombre + SEPARADOR +
			mensaje.direccion + SEPARADOR +
			mensaje.telefono
			<< std::endl;
	
	return 0;
}

int Cliente::agregarRegistro(const std::string nombre, const std::string telefono, const std::string direccion) {
	if (!cola->existe()) {
		std::cout << "No se puede comunicar con el servidor. Posiblemente se cerró." << std::endl;
		return -1;
	}

	mensaje.mtype = AGREGAR;

	strcpy(mensaje.nombre, nombre.c_str());
	strcpy(mensaje.telefono, telefono.c_str());
	strcpy(mensaje.direccion, direccion.c_str());
	
	cola->escribir(mensaje);
	
	return 0;
}
