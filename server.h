#ifndef TP_SOCKET_SERVER_H
#define TP_SOCKET_SERVER_H

#endif //TP_SOCKET_SERVER_H

#include<stdio.h>
#include <sys/socket.h>
#include <malloc.h>
#include <string.h>
#include <netinet/in.h>

#define HOST "localhost"
#define PORT 8080
#define MAX_BUFFER_SIZE 1024
#define MAX_CONNECTIONS 5
#define MAX_PSEUDO_SIZE 20

void launch_server();

void connect_to_clients(char *host, int port, char *string, char **pString);
void create_socket_server(int *sock);
void bind_socket_server(int *sock, char *host, int port);
void send_data_server(int sock, char *message);
int receive_data_server(int sock, char *buffer);
int consume_buffer_server(char *buffer, int size, int offset);
