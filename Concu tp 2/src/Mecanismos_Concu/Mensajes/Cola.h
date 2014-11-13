#ifndef COLA_H_
#define COLA_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>
#include <errno.h>

template <class T> class Cola {
	private:
		key_t	clave;
		int		id;

	public:
		Cola(const std::string& archivo, const char letra);
		~Cola();
		int escribir(const T& dato) const;
		int leer(const int tipo, T* buffer) const;
		int destruir() const;
		bool existe();
};

template <class T> Cola<T>::Cola(const std::string& archivo, const char letra) {
	this->clave = ftok(archivo.c_str(), letra);
	if (this->clave == -1)
		perror("Error en ftok");

	this->id = msgget(this->clave, 0777 | IPC_CREAT);
	if (this->id == -1)
		perror("Error en msgget");
}

template <class T> Cola<T>::~Cola() { }

template <class T> int Cola<T>::destruir() const {
	return msgctl(this->id, IPC_RMID, NULL);
}

template <class T> int Cola<T>::escribir(const T& dato) const {
	return msgsnd(this->id, static_cast<const void*>(&dato), sizeof(T) - sizeof(long), 0);
}

template <class T> int Cola<T>::leer(const int tipo, T* buffer) const {
	return msgrcv(this->id, static_cast<void *>(buffer), sizeof(T) - sizeof(long), tipo, 0);
}

template <class T> bool Cola<T>::existe() {
	int msgid = msgget(this->clave, IPC_CREAT | IPC_EXCL | 0777);
	if (msgid == -1)
		return (EEXIST == errno);

	// Si la pudo crear, la elimino, no deberia ser creada (?):
	msgctl(msgid, IPC_RMID, NULL);
	return false;
}

#endif /* COLA_H_ */
