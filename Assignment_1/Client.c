#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080


int main ()
{
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[1024];
    ssize_t nread;
    char status[6]=":exit";

    // Creation of socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("[-]Error during the creation of socket\n");
        exit(-1);
    }
    printf("[+]Client socket has been created\n");


    memset(&serverAddress, '\0', sizeof(serverAddress));

    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connection
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error on the connection\n");
        exit(-1);
    }
    printf("[+]Connected to Server\n");
    printf("[+]Use exit to logout\n");

    while (1) {

        printf("> Send : ");     
        
        fgets(buffer,1023,stdin);



        if (send(clientSocket, buffer, strlen(buffer), 0) == -1) {
            perror("Error in sending");
            exit(1);
        }
        

        if(strncmp("exit",buffer,4) == 0) {
            
            printf("Disconnected from Server\n");
            close(clientSocket);
            exit(0);
        }
        bzero(buffer,1024);
      
        if ( (nread=recv(clientSocket, buffer, sizeof buffer - 1, 0)) <= 0) {
            perror("Error in receiving data from server\n");
        }
        else {
            buffer[nread] = '\0';
            printf("> Recieved : %s \n", buffer);
            bzero(buffer,1024);
        }

    }

    close(clientSocket);

    return 0;
}
