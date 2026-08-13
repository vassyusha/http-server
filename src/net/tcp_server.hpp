#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class TCPServer{
    int port;
    int serverSocket = -1;
    
    void handleClient(int clientSocket);

public:
    TCPServer(int port);
    ~TCPServer();

    void start();
};