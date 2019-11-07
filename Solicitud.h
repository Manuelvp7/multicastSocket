#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "mensaje.h"

class Solicitud{
	public:
		Solicitud();
		char * doOperation(char * IP, int puerto, int doOperationId, char * arguments);
		
	private:
		SocketDatagrama *socketlocal;
};