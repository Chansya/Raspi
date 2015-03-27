// ----------------------------------------------
// Filename: stServer.c
// Author:   Chansya
// Date:     March 24, 2015
// ----------------------------------------------

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <arpa/inet.h>

#define BACKLOG 10

int main(int argc, char *argv[])
{
    struct sockaddr_in stServAddr;
    int socketFD = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);   //return an integer number(File Descriptor, FD)
    time_t t;
    struct tm *tm;
    FILE *client;

    if(-1 == socketFD){
        perror("error create socket failed.");
        return 1;
    }

    memset(&stServAddr, 0, sizeof(stServAddr));

    stServAddr.sin_family      = AF_INET;            //Address Family
    stServAddr.sin_port        = htons(1107);        //host to network short, clients connect to this port
    stServAddr.sin_addr.s_addr = htonl(INADDR_ANY);  //host to network long, autoselect IP address(INADDR_ANY)

    if(-1 == bind(socketFD, (struct sockaddr*)&stServAddr, sizeof(stServAddr))){
        perror("error: bind failed");
        close(socketFD);
        return 0;
    }

    if(-1 == listen(socketFD,BACKLOG)){
        perror("error: listen failed");
        close(socketFD);
        return 0;
    }

    while(1){
        int connectFD = accept(socketFD, NULL, NULL);

        if(0 > connectFD){
            perror("error: accept failed");
            return 4;
        }

        if ((client = fdopen(connectFD, "w")) == NULL) {
            perror("error: fdopen failed");
            return 5;
        }

        if(0 > (t = time(NULL))){
            perror("error: time failed");
            return 6;
        }

        tm = gmtime(&t);
        fprintf(client, "%.4i-%.2i-%.2i %.2i:%.2i:%.2i \n",
                tm->tm_year + 1990,
                tm->tm_mon + 1,
                tm->tm_mday,
                tm->tm_hour+8,
                tm->tm_min,
                tm->tm_sec);

        fclose(client);
        close(connectFD);
    }

    close(socketFD);
    return 0;
}
