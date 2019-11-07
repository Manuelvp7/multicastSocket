#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include "PaqueteDatagrama.h"

class SocketDatagrama{
    public:
        SocketDatagrama(int);
        ~SocketDatagrama();
        int recibeTimeout(PaqueteDatagrama *p, time_t segundos, suseconds_t microsegundos);
        //Recibe un paquete tipo datagrama proveniente de este socket
        int recibe(PaqueteDatagrama * p);
        //Envía un paquete tipo datagrama desde este socket
        int envia(PaqueteDatagrama & p);
    private:
        struct sockaddr_in direccionLocal;
        struct sockaddr_in direccionForanea;
        int s; //ID socket
        struct timeval timeout;
};
