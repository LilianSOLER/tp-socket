

#ifndef TP_SOCKET_CLIENT_H
#define TP_SOCKET_CLIENT_H

#endif //TP_SOCKET_CLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define DEFAULT_HOST "localhost"
#define DEFAULT_PORT 8080

#define MAX_BUFFER_SIZE 1024

void launch_client();

void connect_to_server(char *host, int port, char *string);
void create_socket_client(int *sock);
void bind_socket_client(int *sock, char *host, int port);
void send_data_client(int sock, char *message);
int receive_data_client(int sock, char *buffer);
int consume_buffer_client(char *buffer, int size, int offset);
