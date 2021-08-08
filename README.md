# JEC-IndProj-Team21

In this project we have created a simple server-client program using socket programming.

Socket Programming->

It helps us to connect a client to a server. Client is message sender and receiver and server is just a listener that works on data sent by client.

Socket programming is started by socket library


SERVER code

# Import socket module
## import socket
sockfd = socket(AF_INET,socket.SOCK_STREAM,0)

    AF_INET refers to address family ipv4
    SOCK_STREAM meaning TCP protocol



    clientsocket = socket()
        It simply creates a new socket using the given address family,socket type and protocol number.
    port = 8080
       
        We binded our server to the specified port. Passing an empty string means that the server can listen to incoming connections from other computers as well. If we would have passed 127.0.0.1 then it would have listened to only those calls made within the local computer.
    listen(sockfd,4)
        Server can connect to 4 clients, 5th or more clients are rejected.
    accept()
        Return new socket object c and address
    close(clientsocket)
        Marks the socket closed, all future operaions on socket will be failed.





Client Code

# Import socket module
## import socket


def Main():
   

    # Define the port on which you want to connect
    PORT = 8080

    clientsocket = socket(AF_INET,SOCK_STREAM,0)

    # connect to server on local computer
    connect(clientsocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress))

    # message you send to server
    message = Hello 
    while True:

        # message sent to server
        send(clientsocket,buffer,sizeof(buffer),0)

        # messaga received from server
        recv(clientsocket,buffer,sizeof(buffer-1),0)

        # print the received message
        # here it would be a reverse of sent message
        print('Received from the server :%s',buffer)

        
    # close the connection
    close(clientsocket)







