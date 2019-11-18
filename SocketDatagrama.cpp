#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring> 
#include "SocketDatagrama.h"

using namespace std;

SocketDatagrama::SocketDatagrama(int port){ 
    s = socket(AF_INET, SOCK_DGRAM, 0);
    int reuse = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1) {
        printf("Error al llamar a la función setsockopt\n");
        exit(0);
    }
    bzero((char *)&direccionLocal, sizeof(direccionLocal));

    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(port);
    bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama(){
    shutdown(s, SHUT_RDWR);
}

int SocketDatagrama::envia(PaqueteDatagrama *p){
    int enviado;
    int num[2];
    num[0] = p->obtieneDatos()[0];
    num[1] = p->obtieneDatos()[1];

    // printf("datos[0] = %d\n", p->obtieneDatos()[0]);
    // printf("datos[1] = %d\n", p->obtieneDatos()[1]);
    int res = num[0]+num[1];
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p->obtieneDireccion());
    direccionForanea.sin_port = htons(p->obtienePuerto());
    unsigned int lData = sizeof(direccionForanea);
    printf("RESPONDER A: %s %d res = %d\n\n",p->obtieneDireccion(),htons(direccionForanea.sin_port),res );
    enviado = sendto(s,( char*)&res, sizeof(int), 0, (struct sockaddr *)&direccionForanea, lData);
    return enviado;

    
}


int SocketDatagrama::recibe(PaqueteDatagrama *p){

    printf("REVIBIENFO\n");
    
    int respuesta;
    unsigned int lData = sizeof(direccionForanea);

    int responseStatus = 0;
    if(recvfrom(s, (char*)&respuesta, sizeof(int), 0, (struct sockaddr *)&direccionForanea, &lData)<0){
        printf("ERROR\n");
        exit(1);
    }

    int num[] = {respuesta};

    printf("FIN DE RECIBIR\n");
    p->inicializaArgumentosMensaje(num);
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in* ip = (struct sockaddr_in*)&direccionForanea;
    struct in_addr ipAdd = ip->sin_addr;
    unsigned short ipPort = ip->sin_port;
    inet_ntop(AF_INET, &ipAdd, str, INET_ADDRSTRLEN);
    printf("IP: %s  \n", str);
    printf("Puerto: %d \n", (int) ntohs(ip->sin_port));
    printf(" %d\n",p->obtieneDatos()[0] );
    p->inicializaIP(inet_ntoa(direccionForanea.sin_addr));
    p->inicializaPuerto(ntohs(direccionForanea.sin_port));

    return responseStatus;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama *p, time_t segundos, suseconds_t microsegundos){

    char str[INET_ADDRSTRLEN];
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;

    unsigned int lData = sizeof(direccionForanea);
    int respuesta = 0;
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    int i = recvfrom(s, (char*)&respuesta, sizeof(int), 0, (struct sockaddr *) &direccionForanea, &lData);
    printf("LA respuesta  ES %d\n",respuesta );
    int num[2] = {respuesta,0};
    
    
    struct sockaddr_in * ip = (struct sockaddr_in*)&direccionForanea;
    struct in_addr ipAdd = ip->sin_addr;
    unsigned short ipPort = ip->sin_port;
    inet_ntop(AF_INET, &ipAdd, str, INET_ADDRSTRLEN);

    p->inicializaIP(inet_ntoa(direccionForanea.sin_addr));
    p->inicializaPuerto(ntohs(direccionForanea.sin_port));
    p->inicializaArgumentosMensaje(num);

    printf("IP: %s  ", str);
    printf("Puerto: %d ", (int) ntohs(ip->sin_port));
    printf(" %d\n",respuesta );

    return i;
}