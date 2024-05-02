#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct sockaddr_in address;
const int PORT = 8080; //Where the clients can reach at

/* htonl converts a long integer (e.g. address) to a network
representation */
/* htons converts a short integer (e.g. port) to a network
representation */


int main() {
    
    int server_fd, new_socket;
    int addrlen = sizeof(address);

    // HTTP header to the client in response to client request
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContentLength: 12\n\nHello world!";

    // Creating a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Cannot create socket");
        return 0;
    }

    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    // Naming the socket using bind
    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0) {
        perror("Bind failed");
        return 0;
    }

    // Allow listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("In listen");
        exit(0);
    }
    
    // Accept incoming connections
    while(1) {
        
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("In accept");
            exit(0);
        }

        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        printf("%s\n",buffer );
        
        if(valread < 0) {
            printf("No bytes are there to read");
        }
        
        printf("------------------Hello message sent-------------------\n");
        write(new_socket , hello , strlen(hello));

        close(new_socket);
    }
    
}