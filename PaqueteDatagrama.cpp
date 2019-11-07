#include "PaqueteDatagrama.h"
using namespace std;

PaqueteDatagrama::PaqueteDatagrama(struct mensaje msj1, char* ipAddress,int port ){
	
	strcpy(ip,ipAddress);
	puerto = port;
	msj = msj1;
   	
}

PaqueteDatagrama::PaqueteDatagrama(){
}

char* PaqueteDatagrama::obtieneDireccion(){
   return ip;
}

int PaqueteDatagrama::obtienePuerto(){
   return puerto;
}

char * PaqueteDatagrama::obtieneDatos(){
   return msj.arguments;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
   return strlen(msj.arguments);
}

struct mensaje PaqueteDatagrama::obtieneMensaje(){
	return msj;
}

void PaqueteDatagrama::inicializaArgumentosMensaje(char * args){
	strcpy(msj.arguments,args );
}

void PaqueteDatagrama::inicializaIP(char* ip1){

	strcpy(ip,ip1);

}
void PaqueteDatagrama::inicializaPuerto(int port){

	puerto = port;

}

