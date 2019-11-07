#include "SocketMulticast.h"
#include "Solicitud.h"
#include "PaqueteDatagrama.h"
#include "mensaje.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	SocketMulticast socketMulticast = SocketMulticast(atoi(argv[2]));
	Solicitud solicitud = Solicitud();

	PaqueteDatagrama package = PaqueteDatagrama();

	printf("UNIENDOSE %s\n",argv[1] );

	char *a;

	socketMulticast.unirseGrupo(argv[1]);
	while(true){
		socketMulticast.recibe(&package);
		// printf("RESPONDER A: %s %d\n",package.obtieneDireccion(),package.obtienePuerto() );
		a = solicitud.doOperation(package.obtieneDireccion(),package.obtienePuerto(),1,"HOLA QUE PASO");
		//socketDatagrama.envia(package);

		
		//printf("HOLASSS\n");


	}
	
	/* code */
	return 0;
}