#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080
#define MAX_CONNESSIONI 4
int main ()
{
    int serverSocket, bindStatus;
    struct sockaddr_in serverAddress;
    int clientSocket;
    struct sockaddr_in newAddress;
    char buffer[1024];
    char msg[13]="Hello Client";
    char status[6]=":exit";
    pid_t child;
    socklen_t addrSize;
    ssize_t nread;
    int i=21,j=11;
    // Creation of socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error during the creation of socket\n");
        exit(-1);
    }

    printf("Server socket has been created\n");

    memset(&serverAddress, '\0', sizeof(serverAddress));

    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Binding of socket 
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error during binding\n");
        exit(1);
    }
    printf("Bind to port %d\n", PORT);


    
    if (listen(serverSocket, MAX_CONNESSIONI) != -1) {
        printf("Listening . . .\n\n");
    }
    else {
        perror("Error during listening\n");
        exit(1);
    }


    while (1) {


        clientSocket = accept(serverSocket, (struct sockaddr*)&newAddress, &addrSize);
        if (clientSocket == -1) {
            exit(-1);
        }
        printf("%s:%d joined\n", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port));

        child = fork();
        if (child == 0) {

            close(serverSocket);

            while (1) {

                
                if ( (nread=recv(clientSocket, buffer, sizeof buffer - 1, 0)) <= 0) {
                    perror("Error in receiving data from server\n");
                }
                else {
                    buffer[nread] = '\0';
                }
                while(buffer[j]!='\0')
                {
                    msg[i]=buffer[j];
                    i++;
                    j++;
                }
                j=11;
                i=21;

                if (strncmp("exit",buffer,4) == 0) {
                    printf("%s:%d left\n", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port));
                    bzero(msg,13);
                    msg[13]="exit";
                    close(clientSocket);
                    break;
                }
                else {
                    printf("%s:%d wrote > : %s", inet_ntoa(newAddress.sin_addr), ntohs(newAddress.sin_port), buffer);
                    bzero(buffer,strlen(buffer));
                    send(clientSocket,msg, strlen(msg), 4);
                    
                    
                }

            }

        }

    }

    close(clientSocket);

    return 0;
}
