#include "Cliente.h"


Cliente :: Cliente () {
	
	this->claveUnicaCliente = 0;

	this->coordClaveUnica = new MemoriaCompartida<int>();
	this->coordClaveUnica->crear(ARCHIVO_SHMEM, CLAVE_SHMEM);
	
	//obtiene su clave unica par alos mensajes y actualiza la memoria compartida al nuevo valor
	this->lockClave = new  LockFile ( ARCHIVO_FLOCK );
	
	this->lockClave->tomarLock();
	this->claveUnicaCliente = coordClaveUnica->leer();
	if (this->claveUnicaCliente == 0){
		//para inicializar fuera del rango que el servidor toma como mensajes hacia el
		this->claveUnicaCliente = 100;
	}else{
		this->claveUnicaCliente ++;
	}
	this->coordClaveUnica->escribir(claveUnicaCliente);
	this->lockClave->liberarLock();
		

	this->cola = new Cola<Mensaje> ( ARCHIVO_COLA,CLAVE_COLA );
}

Cliente :: ~Cliente() {
	//TODO if ptr != null aca y tambien en los deletes de los otros metodos
	
	if (lockClave != NULL){
		delete this->lockClave;
		this->lockClave = NULL;
	}
	
	if (this->coordClaveUnica != NULL){
		this->coordClaveUnica->liberar();
		delete this->coordClaveUnica;
		this->coordClaveUnica = NULL;
	}

	if (this->cola != NULL){
		this->cola->destruir ();
		delete this->cola;
		this->cola = NULL;
	}
}


int Cliente :: pedirInformacion ( const std::string nombre ){
	//esto es por si alguien mas termino y borro la cola
	delete this->cola;
	this->cola = new Cola<Mensaje> ( ARCHIVO_COLA,CLAVE_COLA );


	this->mensaje.mtype = PEDIDO;
	
	/*le paso a la base de datos:
	* a quien contestarle
	* el nombre de por quien pregunto
	*/
	
	this->mensaje.clave = claveUnicaCliente;
	strcpy ( this->mensaje.nombre, nombre.c_str() );
	
	this->cola->escribir ( this->mensaje );
	
	return 0;
}

int Cliente :: esperarRespuesta (){
	//esto es por si alguien mas termino y borro la cola
	delete this->cola;
	this->cola = new Cola<Mensaje> ( ARCHIVO_COLA,CLAVE_COLA );

	this->cola->leer ( this->claveUnicaCliente, &this->mensaje );
	
	std::cout << "Mensaje recibido: " <<
			this->mensaje.nombre + SEPARADOR +
			this->mensaje.direccion + SEPARADOR +
			this->mensaje.telefono
			<< std::endl;
	
	return 0;
}

int Cliente :: agregarRegistro ( const std::string nombre, const std::string telefono, const std::string direccion ){
	//esto es por si alguien mas termino y borro la cola
	delete this->cola;
	this->cola = new Cola<Mensaje> ( ARCHIVO_COLA,CLAVE_COLA );

	this->mensaje.mtype = AGREGAR;

	strcpy ( this->mensaje.nombre, nombre.c_str() );
	strcpy ( this->mensaje.telefono, telefono.c_str() );
	strcpy ( this->mensaje.direccion, direccion.c_str() );
	
	this->cola->escribir ( this->mensaje );
	
	return 0;
}
