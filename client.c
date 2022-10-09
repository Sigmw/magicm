#include "magicm.h"
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int client(char* socket_path) {
    printf(LOG_FORMAT("Client connecting to %s...\n"), socket_path);
    printf(LOG_FORMAT("Client not implemented yet!\n"));
    return 0;
}
