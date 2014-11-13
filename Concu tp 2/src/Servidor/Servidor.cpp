#include "Servidor.h"

Servidor :: Servidor (){

	cola = new Cola<Mensaje>(ARCHIVO_COLA, CLAVE_COLA);
	baseDeDatos = new Archivo (RUTA_BASE_DE_DATOS);
	baseDeDatos -> abrir();
//TODO aca y en el cliente ver si, o como, inicializar los mensajes
}

Servidor :: ~Servidor (){
//todo if ptr != null aca y tmb en los otros deletes
	cola->destruir();
	delete cola;

	baseDeDatos->cerrar();
	delete baseDeDatos;
}


int Servidor :: procesarPedido(){
	//por si alguien termina antes y borra la cola
	delete this->cola;
	this->cola = new Cola<Mensaje> ( ARCHIVO_COLA,CLAVE_COLA );

	//lee alguna peticion, con prioridad a los pedidos de informacion
	//esto obliga que pedido tenga un numero menor a agregar
	//todo preguntar si es valido
	int res = cola->leer(-AGREGAR, &peticionRecibida);

	if (res == -1){
		std::cout << "Error de algun tipo al leer en la cola" << std::endl;
		return -1;
	}

	if (peticionRecibida.mtype == PEDIDO){
		procesarPedidoInfo();
	}else if (peticionRecibida.mtype == AGREGAR){
		procesarAgregado();
	}else{
		std::cout << "El servidor recibio un mensaje invalido, no sera procesado." << std::endl;
		//todo guardar mensaje en arch errores
		std::cout << peticionRecibida.mtype << std::endl;
		return -1;
	}

	return 0;
}
//TODO this . o -> por TODOS lados
int Servidor :: procesarPedidoInfo(){
	//por si alguien termina antes y borra la cola
	delete this->cola;
	this->cola = new Cola<Mensaje> ( ARCHIVO_COLA,CLAVE_COLA );


	//obtiene el numero de cliente para saber a quien contestarle
	int numeroCliente = peticionRecibida.clave;
	//obtiene nombre a buscar en la base de datos
	std::string nombreABuscar = peticionRecibida.nombre;

	//obtiene la informacion requerida de la base de datos
	std::string textoRespuesta = baseDeDatos->buscarRegistro(nombreABuscar);

	//parsea el registro recibido
	std::string nombre,tel,dir;

	int posSeparador = textoRespuesta.find(SEPARADOR);
	int posSeparador2 = textoRespuesta.rfind(SEPARADOR);

	nombre = textoRespuesta.substr(0,posSeparador);
	dir = textoRespuesta.substr(posSeparador + 1, posSeparador2 - posSeparador - 1 );
	tel = textoRespuesta.substr(posSeparador2 + 1);

	//responde
	this->respuesta.mtype = numeroCliente;
	strcpy ( this->respuesta.nombre, nombre.c_str() );
	strcpy ( this->respuesta.telefono, tel.c_str() );
	strcpy ( this->respuesta.direccion, dir.c_str() );

	this->cola->escribir ( this->respuesta );

	return 0;
}

int Servidor :: procesarAgregado(){
	//parsea el mensaje recibido
	std::string textoPeticion = peticionRecibida.nombre + SEPARADOR +
			peticionRecibida.direccion + SEPARADOR + peticionRecibida.telefono + NEWLINE;

	baseDeDatos->agregarRegistro(textoPeticion);

	return 0;
}


