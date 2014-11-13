#include "Servidor.h"

Servidor::Servidor() {
	cola = new Cola<Mensaje>(ARCHIVO_COLA, CLAVE_COLA);
	baseDeDatos = new Archivo(RUTA_BASE_DE_DATOS);
	if (baseDeDatos != NULL)
		baseDeDatos->abrir();
	//TODO aca y en el cliente ver si, o como, inicializar los mensajes
}

Servidor::~Servidor() {
	if (cola != NULL) {
		cola->destruir();
		delete cola;
		cola = NULL;
	}
	if (baseDeDatos != NULL) {
		baseDeDatos->cerrar();
		delete baseDeDatos;
		baseDeDatos = NULL;
	}
}


int Servidor::procesarPedido() {
	if (cola == NULL) {
		std::cout << "Cola era NULL" << std::endl;
		return -1;
	}

	//lee alguna peticion, con prioridad a los pedidos de informacion
	//esto obliga que pedido tenga un numero menor a agregar
	//todo preguntar si es valido
	if (cola->leer(-AGREGAR, &peticionRecibida) == -1) {
		std::cout << "Error de algun tipo al leer en la cola" << std::endl;
		return -1;
	}

	switch (peticionRecibida.mtype) {
		case PEDIDO:
			procesarPedidoInfo();
			break;
		case AGREGAR:
			procesarAgregado();
			break;
		default:
			std::cout << "El servidor recibió un mensaje inválido, no será procesado." << std::endl;
			//todo guardar mensaje en arch errores
			std::cout << peticionRecibida.mtype << std::endl;
			return -1;
	}
	return 0;
}

//TODO this . o -> por TODOS lados
int Servidor::procesarPedidoInfo() {
	if (cola == NULL) {
		std::cout << "Cola era NULL" << std::endl;
		return -1;
	}

	//obtiene el numero de cliente para saber a quien contestarle
	int numeroCliente = peticionRecibida.clave;
	//obtiene nombre a buscar en la base de datos
	std::string nombreABuscar = peticionRecibida.nombre;

	//obtiene la informacion requerida de la base de datos
	Mensaje respuesta = baseDeDatos->buscarRegistro(nombreABuscar);
	if (respuesta == NULL) {
		// TODO: No se encontro el registro
		return -1;
	}

	//responde
	int res = responder(numeroCliente, respuesta);
	// TODO: control de errores aca

	return 0;
}

int Servidor::responder(int numeroCliente, Mensaje& respuesta) {
	respuesta.mtype = numeroCliente; // TODO: seguro es en el mtype?
	return cola->escribir(respuesta);
}

int Servidor :: procesarAgregado(){
	//parsea el mensaje recibido
	std::string textoPeticion = peticionRecibida.nombre + SEPARADOR +
			peticionRecibida.direccion + SEPARADOR + peticionRecibida.telefono + NEWLINE;

	baseDeDatos->agregarRegistro(textoPeticion);

	return 0;
}


