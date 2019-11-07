#include "SocketMulticast.h"
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "mensaje.h"
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	SocketMulticast socketMulticast = SocketMulticast(atoi(argv[2]));
	SocketDatagrama socketDatagrama =  SocketDatagrama(6666);
	struct mensaje msj;
	msj.messageType = 1;
    msj.requestId = 1;
    msj.operationId = 10;

    strcpy(msj.arguments,"hola");

	PaqueteDatagrama packageMulicast  = PaqueteDatagrama(msj,argv[1], atoi(argv[2]));
	PaqueteDatagrama packageUnicast  = PaqueteDatagrama();
	suseconds_t microsegundos = 3000;
	unsigned char ttl = 1;
	time_t segundos = 3;
	int x ;
	
	for (;;){
		socketMulticast.envia(&packageMulicast,ttl);
		socketDatagrama.recibeTimeout(&packageUnicast,segundos,microsegundos);
		// x=socketDatagrama.recibe(&packageUnicast);

	}
	
	/* code */
	return 0;
}