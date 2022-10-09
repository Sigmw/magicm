#include "magicm.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int client(char* socket_path, char* client_flag) {
    int sockfd, connfd;
    struct sockaddr_un unix_addr;
    char buffer[1024];

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if((sockfd == -1)) {
        perror(LOG_FORMAT_ERROR("Can't create socket"));
        _exit(EXIT_FAILURE);
    }
    
    unix_addr.sun_family = AF_UNIX;
    strcpy(unix_addr.sun_path, socket_path);

    if((connfd = connect(sockfd, (struct sockaddr*)&unix_addr, sizeof(unix_addr))) == -1) {
        perror(LOG_FORMAT_ERROR("Can't connect to socket"));
        _exit(EXIT_FAILURE);
    }
    printf(LOG_FORMAT("Connected in: %s...\n"), socket_path);
    fflush(stdout);
    
    if(client_flag == NULL) {
        client_flag = "default";
    }
    write(sockfd, client_flag, strlen(client_flag));
    read(sockfd, buffer, sizeof(buffer)); 
    printf("%s", buffer);
    
    return 0;
}
