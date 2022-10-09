#ifndef _MAGIC_H
#define _MAGIC_H

#define LOG_FORMAT(str) "\033[1m\e[1;35m" str "\033[0m"
#define LOG_FORMAT_ERROR(str) "\033[1m\e[1;35m" str
#define LOG_FORMAT_SERVER(str) "\e[1;36m" str "\033[0m"

int server();
int client(char* socket_path, char* client_flag);

#endif
