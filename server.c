#include <arpa/inet.h>
#include "server.h"

int main(int argc, char *argv[]){
    char *host = HOST;
    int port = PORT;
    char *buffer = malloc(MAX_BUFFER_SIZE);
    // create an array of string to stock pseudo of client connected
    char **clients = malloc(MAX_CONNECTIONS * sizeof(char *));
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        clients[i] = malloc(MAX_PSEUDO_SIZE);
    }


    if (argc == 3) {
        host = argv[1];
        port = (int) argv[2];
    } else if (argc != 1) {
        printf("Usage: %s [host] [port] (default: localhost 8080) \r \n", argv[0]);
        return 1;
    }

    printf("Host: %s \r \n", host);
    printf("Port: %d \r \n", port);

    connect_to_clients(host, port, buffer, clients);
}

void launch_server() {
    // ask for host and port
    char *host = malloc(MAX_BUFFER_SIZE);
    int port = 0;
    printf("Host: ");
    scanf("%s", host);
    printf("Port: ");
    scanf("%d", &port);

    main(3, (char *[]){"server", host, (char *) port});
}

void connect_to_clients(char *host, int port, char *buffer, char **clients) {
    int sock;
    create_socket_server(&sock);

    bind_socket_server(&sock, host, port);

    listen(sock, MAX_CONNECTIONS);
    // accept connection
    int client_sock;
    struct sockaddr_in client;
    int c = sizeof(struct sockaddr_in);
    client_sock = accept(sock, (struct sockaddr *) &client, (socklen_t *) &c);
    if (client_sock < 0) {
        perror("accept failed");
        return;
    }
    printf("Connection accepted \r \n");
    // receive pseudo
    int len = receive_data_server(client_sock, buffer);
    if (len > 0) {
        printf("Received: %s \r \n", buffer);
    }
    // send pseudo to all clients
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (clients[i] != NULL) {
            send_data_server(client_sock, clients[i]);
        }
    }
    // add pseudo to clients array
    for (int i = 0; i < MAX_CONNECTIONS; ++i) {
        if (clients[i] == NULL) {
            clients[i] = buffer;
            break;
        }
    }
    // send message to all clients
    while (1) {
        len = receive_data_server(client_sock, buffer);
        if (len > 0) {
            printf("Received: %s \r \n", buffer);
        }
        consume_buffer_server(buffer, len, 0);
        for (int i = 0; i < MAX_CONNECTIONS; ++i) {
            if (clients[i] != NULL) {
                send_data_server(client_sock, buffer);
            }
        }
    }
}


void create_socket_server(int *sock) {
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*sock < 0) {
        printf("Error creating socket \r \n");
        return;
    }
}

void bind_socket_server(int *sock, char *host, int port) {
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(host);
    server.sin_port = htons(port);

    if (bind < 0) {
        printf("Error binding socket to port \r \n");
        return;
    }
}

void send_data_server(int sock, char *message) {
    int sent = send(sock, message, strlen(message), 0);
    if (sent < 0) {
        printf("Error sending data \r \n");
        return;
    }
}

int receive_data_server(int sock, char *buffer) {
    int received = recv(sock, buffer, 255, 0);
    if (received < 0) {
        printf("Error receiving data \r \n");
        return -1;
    }
    return received;
}

int consume_buffer_server(char *buffer, int size, int offset) {
    for (int i = 0; i < size; ++i) {
        buffer[i] = buffer[i + offset];
    }
    return size - offset;
}

