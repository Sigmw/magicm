#include "magicm.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int client(char* socket_path, char* client_flag) {
    int sockfd, connfd;
    struct sockaddr_un unix_addr;

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if((sockfd == -1)) {
        perror(LOG_FORMAT_ERROR("Can't create socket"));
        _exit(EXIT_FAILURE);
    }
    
    unix_addr.sun_family = AF_UNIX;
    strcpy(unix_addr.sun_path, socket_path);

    printf(LOG_FORMAT("Client connecting to %s...\n"), socket_path);
    if((connfd = connect(sockfd, (struct sockaddr*)&unix_addr, sizeof(unix_addr))) == -1) {
        perror(LOG_FORMAT_ERROR("Can't connect to socket"));
        _exit(EXIT_FAILURE);
    }

    
    return 0;
}
