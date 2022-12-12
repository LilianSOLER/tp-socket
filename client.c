#import "client.h"

int main(int argc, char *argv[]){
    char *host = DEFAULT_HOST;
    int port = DEFAULT_PORT;
    char *buffer = malloc(MAX_BUFFER_SIZE);

    if (argc == 3) {
        host = argv[1];
        port = (int) argv[2];
    } else if (argc != 1) {
        printf("Usage: %s [host] [port] (default: localhost 8080) \r \n", argv[0]);
        return 1;
    }

    printf("Host: %s \r \n", host);
    printf("Port: %s \r \n", port);

    connect_to_server(host, port, buffer);

    return 0;
}

void launch_client() {
    // ask for host and port
    char *host = malloc(MAX_BUFFER_SIZE);
    int port = 0;
    printf("Host: ");
    scanf("%s", host);
    printf("Port: ");
    scanf("%d", &port);

    main(3, (char *[]){"client", host, (char *) port});
}

void connect_to_server(char *host, int port, char *buffer) {
    printf("Connecting to %s:%d \r \n", host, port);

    // create socket
    int sock;
    create_socket_client(&sock);

    // bind socket to port
    bind_socket_client(&sock, host, port);

    send_data_client(sock, "Hello server!");

    for (int i = 0; i < 100 ; ++i) {

        send_data_client(sock, &"Message from client" [ i]);

        int len = receive_data_client(sock, buffer);

        if (len > 0) {
            printf("Received: %s \r \n", buffer);
        }

        // sleep for a random amount of time
        sleep(rand() % 5);

        len = consume_buffer_client(buffer, len, 0);

        if (len > 0) {
            printf("Remaining: %s \r \n", buffer);
        }

        // sleep for a random amount of time
        sleep(rand() % 5);
    }

    // close socket
    shutdown(sock, 2);
}

void create_socket_client(int *sock) {
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if (*sock < 0) {
        printf("Error creating socket \r \n");
        return;
    }
}

void bind_socket_client(int *sock, char *host, int port) {
    int bind;
    struct sockaddr_in client;
    client.sin_addr.s_addr = inet_addr(host);
    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    bind = connect(*sock, (struct sockaddr *) &client, sizeof(client));
    if (bind < 0) {
        printf("Error binding socket to port \r \n");
        return;
    }
}

void send_data_client(int sock, char *message) {
    int sent = send(sock, message, strlen(message), 0);
    if (sent < 0) {
        printf("Error sending data \r \n");
        return;
    }
}

int receive_data_client(int sock, char *buffer) {
    int received = recv(sock, buffer, 255, 0);
    if (received < 0) {
        printf("Error receiving data \r \n");
        return -1;
    }
    return received;
}

int consume_buffer_client(char *buffer, int size, int offset) {
    for (int i = 0; i < size; ++i) {
        buffer[i] = 0;
    }

}
