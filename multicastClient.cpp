#include "SocketMulticast.h"
#include "Solicitud.h"
#include "PaqueteDatagrama.h"
#include "mensaje.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	char * ip = argv[1];
	int port = atoi( argv[2]);

	SocketMulticast socketMulticast = SocketMulticast(port);
	SocketDatagrama socketDatagrama(port + 100);
	// Solicitud solicitud = Solicitud();arg

	struct mensaje msj;
	msj.messageType = 1;
	msj.requestId = 2;
	msj.operationId = 3;

	int num[] = {1,2};
	msj.arguments[0] = 1;
	msj.arguments[0] = 2;
	
	PaqueteDatagrama package = PaqueteDatagrama();

	printf("UNIENDOSE %s\n",argv[1] );

	char *a;

	socketMulticast.unirseGrupo(argv[1]);

	while(true){
		socketMulticast.recibe(&package);
		socketDatagrama.envia(&package);
	}
	
	/* code */
	return 0;
}