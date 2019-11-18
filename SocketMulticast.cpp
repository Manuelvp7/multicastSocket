#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <net/if.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include "SocketMulticast.h"

using namespace std;

SocketMulticast::SocketMulticast(int port){
    //s = socket(AF_INET, SOCK_DGRAM, 0);
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int reuse = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1) {
        printf("Error al llamar a la función setsockopt\n");
        exit(0);
    }
    // unsigned char TTL = "1";
    struct sockaddr_in direccionLocal;
    bzero((char *)&direccionLocal, sizeof(direccionLocal));
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(port);
    bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketMulticast::~SocketMulticast(){
    shutdown(s, SHUT_RDWR);
}

int SocketMulticast::recibe(PaqueteDatagrama *p){

    struct sockaddr_in direccionForanea;
    int num[2];
    unsigned int lData = sizeof(direccionForanea);
    int responseStatus = recvfrom(s, (char*)num, 2*sizeof(int), 0, (struct sockaddr *)&direccionForanea, &lData);
    
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in* ip = (struct sockaddr_in*)&direccionForanea;
    struct in_addr ipAdd = ip->sin_addr;
    unsigned short ipPort = ip->sin_port;
    inet_ntop(AF_INET, &ipAdd, str, INET_ADDRSTRLEN);
    printf("numero 1 %d\n",num[0] );

    p->inicializaArgumentosMensaje(num);


    printf("RECIBIENDO MENSAJE DE: IP: %s  ", str);
    printf("Puerto: %d ", (int) ntohs(ip->sin_port));
    printf("OPERACION: %d + %d  \n\n",num[0],num[1] );

    p->inicializaIP(inet_ntoa(direccionForanea.sin_addr));
    p->inicializaPuerto(ntohs(direccionForanea.sin_port)+100);
    //printf("multicast recibe recvfrom(%d,%d+%d,%d,%s,%d,)\n",s,num[0],num[1], p->obtieneLongitud(),p->obtieneDireccion(),p->obtienePuerto() );
    return 1;
}

int SocketMulticast::envia(PaqueteDatagrama * p, unsigned char ttl){

    int validator  = setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &ttl, sizeof(ttl));
    if (validator<0){
        printf("An error has occurred\n Exiting...");
        exit(0);
    }else{
        //printf("Emmiter is up and running\n Sending messages ");
    }   

    struct sockaddr_in direccionForanea;
    int enviado;
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p->obtieneDireccion());
    direccionForanea.sin_port = htons(p->obtienePuerto());
    unsigned int lData = sizeof(direccionForanea);
    printf("Enviando operacion a: %s %d\n", p->obtieneDireccion(),p->obtienePuerto());
    // printf("multicast envia sendto(%d,%s,%d,%s,%d,)\n",s,p->obtieneDatos(), p->obtieneLongitud(),p->obtieneDireccion(),p->obtienePuerto() );
    enviado = sendto(s, p->obtieneDatos(), p->obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, lData);
    return enviado;
}

void SocketMulticast::unirseGrupo(char * multicastIP){

    struct ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(multicastIP);
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicast, sizeof(multicast)) < 0){
         printf("ERROR AL UNIRSE AL GRUPO MULTICAST \n");
         exit(0);
     } 

}
void SocketMulticast::salirseGrupo(char * multicastIP){

    struct ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(multicastIP);
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicast, sizeof(multicast));

}