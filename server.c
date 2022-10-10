#include "magicm.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

char* user_path();
void handle_connection(int sockfd);

char* user_path() {
    // This function should return /root/root.sock or /home/$USER/$USER.sock
    const char* home = getenv("HOME");
    const char* user = getenv("USER");

    if(home == NULL || user == NULL) {
        fprintf(stderr, LOG_FORMAT_ERROR("Could not create a path for UNIX_SOCKET: $USER or $HOME does not exists\n"));
        _exit(EXIT_FAILURE);
    }

    char* user_path = malloc(strlen(home) + strlen(user) + 6);
    sprintf(user_path, "%s/%s.sock", home, user);

    return user_path;
}

void handle_connection(int sockfd) {
    int connfd;
    char buffer[1024]; 
    char server_buffer[1024];
    printf(LOG_FORMAT("Magic server running!\n"));
    
    while(1) {
       if((connfd = accept(sockfd, NULL, NULL)) == -1) {
            perror(LOG_FORMAT_ERROR("Can't accept connection"));
            _exit(EXIT_FAILURE);
        } 
        printf(LOG_FORMAT("Connection received!\n"));
        fflush(stdout);
        bzero(buffer, sizeof(buffer));

        read(connfd, buffer, sizeof(buffer));
        // The strcmp here has a strange behavior, is returning 10 when the string match.
        if(!(strcmp(buffer, "default"))) {
            strcpy(server_buffer, LOG_FORMAT_SERVER("Hi, i am the Magic socket! I can provide anything about the user running the server. :)\n"));
            write(connfd, server_buffer, strlen(server_buffer));
        } else if(!(strcmp(buffer, "user"))) {
            sprintf(server_buffer, LOG_FORMAT_SERVER("%s\n"), user());
            write(connfd, server_buffer, strlen(server_buffer));
        } else {
            strcpy(server_buffer, LOG_FORMAT_SERVER("Unrecognized CLIENT FLAG.\n"));
            write(connfd, server_buffer, strlen(server_buffer));
        }
        bzero(buffer, sizeof(buffer));
    }
}

int server() {
    int sockfd;
    struct sockaddr_un unix_addr;
    const char* unix_path = user_path();

    if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror(LOG_FORMAT_ERROR("Can't create the socket"));
        _exit(EXIT_FAILURE);
    }
    printf(LOG_FORMAT("UNIX socket successfully created, file descriptor: %i\n"), sockfd);

    unix_addr.sun_family = AF_UNIX;
    strcpy(unix_addr.sun_path, unix_path);

    unlink(unix_path);

    if(bind(sockfd, (struct sockaddr*)&unix_addr, sizeof(unix_addr)) == -1) {
        perror(LOG_FORMAT_ERROR("Can't bind the socket"));
        _exit(EXIT_FAILURE);
    }
    printf(LOG_FORMAT("Socket path: %s\n"), unix_path);

    if(listen(sockfd, 20) == -1) {
        perror(LOG_FORMAT_ERROR("Can't listen socket file descriptor"));
        _exit(EXIT_FAILURE);
    }

    handle_connection(sockfd);
    return 0;
}


