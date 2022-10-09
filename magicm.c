#include "magicm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int usage() {
    printf(LOG_FORMAT("Usage: magicm [server, client] [client? [socket path]] [client? [client flags]] [--help]\n"));
    _exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    switch(argc) {
        case 1:
            usage();
       case 2:
            if(strcmp(argv[1], "server")) {
                usage();
            }
            server();
       case 3:
            if(!(strcmp(argv[1], "client"))) {
                usage();
            }
            client(argv[2]);
    }

}
