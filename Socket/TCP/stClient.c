// ----------------------------------------------
// Filename: stClient.c
// Author:   Chansya
// Date:     March 24, 2015
// ----------------------------------------------

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char *argv[])
{
    struct sockaddr_in stSockAddr;
    int pton, bytes;
    int socketFD = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    char buffer[BUFSIZ+1];

    if(-1 == socketFD){
        perror("error: create socket failed");
        return 1;
    }

    bzero(&stSockAddr, sizeof(stSockAddr));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port   = htons(1107);
    pton = inet_pton(AF_INET, "111.2.1.161", &stSockAddr.sin_addr);  //convert IPv4 and IPv6 addresses from text to binary form
    //inet_pton(int AF, const char *src, void *dst);

    if(0 > pton){
        perror("error: inet_pton first parameter is not a valid address family");
        close(socketFD);
        return pton;
    }
    else if(0 == pton){
        perror("error: inet_pton second parameter is not a valid ip address");
        close(socketFD);
        return pton;
    }

    if(!connect(socketFD, (struct sockaddr*)&stSockAddr, sizeof(stSockAddr))){
        printf("==== Connection success!\n");
    }
    else{
        perror("error");
        switch(errno){
            case ECONNREFUSED:
                break;  //connection refused
            case ENETUNREACH:
                break;  //unknown route
            case EINTR:
                break;  //connection timed out
            default:
                perror("error: connection failed");
                break;
        }
    }

    while((bytes = read(socketFD, buffer, BUFSIZ)) > 0){
        write(1, buffer, bytes);
    }

    (void) shutdown(socketFD, SHUT_RDWR);

    close(socketFD);
    return 0;
}
