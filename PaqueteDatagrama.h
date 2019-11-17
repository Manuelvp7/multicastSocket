#ifndef PAQUETEDATAGRAMA_H_
#define PAQUETEDATAGRAMA_H_
#include "mensaje.h"
#include <string.h>

class PaqueteDatagrama{
	public:
		PaqueteDatagrama(struct mensaje  msj1, char* ip1,int port );
		PaqueteDatagrama();
		int * obtieneDatos();
		char *obtieneDireccion();
		int obtienePuerto();
		unsigned int obtieneLongitud();
		struct mensaje obtieneMensaje();
		void inicializaIP(char*);
		void inicializaPuerto(int);
		void inicializaArgumentosMensaje(int args[]);

		//~PaqueteDatagrama();

	private:
		struct mensaje msj;
		char ip[16];
		int puerto;
};

#endif