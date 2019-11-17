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

int * PaqueteDatagrama::obtieneDatos(){
   return msj.arguments;
}

unsigned int PaqueteDatagrama::obtieneLongitud(){
   return (2*sizeof(int));
}

struct mensaje PaqueteDatagrama::obtieneMensaje(){
	return msj;
}

void PaqueteDatagrama::inicializaArgumentosMensaje(int args[]){
	msj.arguments[0]= args[0];
	msj.arguments[1]= args[1];

}

void PaqueteDatagrama::inicializaIP(char* ip1){

	strcpy(ip,ip1);

}
void PaqueteDatagrama::inicializaPuerto(int port){

	puerto = port;

}

