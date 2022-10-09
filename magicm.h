#ifndef _MAGIC_H
#define _MAGIC_H

#define LOG_FORMAT(str) "\033[1m\e[1;35m" str "\033[0m"
#define LOG_FORMAT_ERROR(str) "\033[1m\e[1;35m" str

int server();
int client(char* socket_path);

#endif
