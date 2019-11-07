#include "Solicitud.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define SOLICITUD 1

Solicitud::Solicitud(){
	socketlocal = new SocketDatagrama(0);
}

struct mensaje prepararMensaje(int doOperationId, char * arguments){
	struct mensaje msj;
	msj.messageType = SOLICITUD;
	msj.requestId = 1;
	msj.operationId = doOperationId;
	strcpy(msj.arguments,arguments);
	return msj;
}

char * Solicitud::doOperation(char * IP, int puerto, int doOperationId, char * arguments){
	struct mensaje msj;
	msj = prepararMensaje(doOperationId,arguments);
	PaqueteDatagrama package1 = PaqueteDatagrama(msj,IP,puerto);
	PaqueteDatagrama packageRecv;

	struct mensaje msj2 = package1.obtieneMensaje();
	printf("Enviando al server: %d,%d,%d, %s\n",msj2.messageType,msj2.requestId,msj2.operationId,package1.obtieneDatos() );	
	socketlocal->envia(package1);
	socketlocal->recibe(&packageRecv);

	char  a[10] = "abc";

	return a;
}