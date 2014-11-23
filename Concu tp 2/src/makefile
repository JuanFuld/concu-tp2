CC = g++
CFLAGS = -Wall -Wpedantic

INC = $(.) $(./Mecanismos_Concu/Cliente) $(./Mecanismos_Concu/Seniales) $(./Mecanismos_Concu/Mensajes)
INC_PARAMS = $(foreach d, $(INC), -I$d)

CONST = Constantes.h
SIG = ./Mecanismos_Concu/Seniales/SignalHandler.h
SIG2 = ./Mecanismos_Concu/Seniales/SIGINT_Handler.h
MSJS = ./Mecanismos_Concu/Mensajes/Cola.h
MSJS2 = ./Mecanismos_Concu/Mensajes/Mensaje.h

DEPS_CLIENTE =  $(CONST)
DEPS_SERVER = $(CONST) $(SIG) $(SIG2) 

OBJClient = Cliente.o BaseDeDatos.o
OBJServer = Servidor.o BaseDeDatos.o SignalHandler.o

EJEC = Cliente Servidor

#all: de que depende, que tiene que existir o no haber sido modificado... 
all: $(EJEC) cleanO

#make debug compila los #ifdefined DEBUG ... # endif
debug: CFLAGS += -DDEBUG
debug: $(EJEC) cleanO

Cliente: MCliente.o $(OBJClient)
	$(CC) $(CFLAGS) $< $(OBJClient) -o Client $(INC_PARAMS)

Servidor: MServidor.o $(OBJServer)
	$(CC) $(CFLAGS) $< $(OBJServer) -o Server $(INC_PARAMS)

MCliente.o: Cliente/main.cpp Cliente/Cliente.h $(DEPS_CLIENTE)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS) -DCLIENTE

MServidor.o: Servidor/main.cpp Servidor/Servidor.h $(DEPS_SERVER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS) -DSERVIDOR

Cliente.o: Cliente/Cliente.cpp Cliente/Cliente.h Constantes.h Mecanismos_Concu/Mensajes/Mensaje.h Mecanismos_Concu/Mensajes/Cola.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)

Servidor.o: Servidor/Servidor.cpp Servidor/Servidor.h Constantes.h Mecanismos_Concu/Mensajes/Mensaje.h Mecanismos_Concu/Mensajes/Cola.h ./BaseDeDatos/BaseDeDatos.hpp
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)

BaseDeDatos.o: ./BaseDeDatos/BaseDeDatos.cpp ./BaseDeDatos/BaseDeDatos.hpp Constantes.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)

SignalHandler.o: ./Mecanismos_Concu/Seniales/SignalHandler.cpp $(SIG) ./Mecanismos_Concu/Seniales/EventHandler.h ./Mecanismos_Concu/Seniales/SIGINT_Handler.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)


.PHONY: cleanO clean

cleanO:
	rm *.o

clean:
	rm Client Server
