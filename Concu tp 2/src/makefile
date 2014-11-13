CC = g++
CFLAGS = -Wall -Wpedantic

INC = $(.) $(./Locks) $(./Cliente) $(./Memoria_Compartida) $(./Seniales) $(./Mensajes)
INC_PARAMS = $(foreach d, $(INC), -I$d)

MEM = ./Memoria_Compartida/MemoriaCompartida.h
CONST = Constantes.h
SIG = ./Seniales/SignalHandler.h
SIG2 = ./Seniales/SIGINT_Handler.h
MSJS = ./Mensajes/Cola.h
MSJS2 = ./Mensajes/Mensaje.h


DEPS_CLIENTE =  $(CONST)
DEPS_SERVER = $(CONST) $(SIG) $(SIG2) 

OBJClient = Cliente.o Archivo.o LockFile.o SignalHandler.o
OBJServer = Servidor.o Archivo.o LockFile.o SignalHandler.o

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

Cliente.o: Cliente/Cliente.cpp Cliente/Cliente.h Constantes.h Mensajes/Mensaje.h Mensajes/Cola.h Locks/LockFile.h Memoria_Compartida/MemoriaCompartida.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)

Servidor.o: Servidor/Servidor.cpp Servidor/Servidor.h Constantes.h Mensajes/Mensaje.h Mensajes/Cola.h Archivo.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)

Archivo.o: Archivo.cpp Archivo.h Constantes.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)

SignalHandler.o: ./Seniales/SignalHandler.cpp $(SIG) ./Seniales/EventHandler.h ./Seniales/SIGINT_Handler.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)

LockFile.o: ./Locks/LockFile.cpp ./Locks/LockFile.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_PARAMS)


.PHONY: cleanO clean

cleanO:
	rm *.o

clean:
	rm Client Server
