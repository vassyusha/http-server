#include "tcp_server.hpp"
#include <iostream>

TCPServer::TCPServer(int port): port(port){
    serverSocket = -1;
}

TCPServer::~TCPServer(){
    if(serverSocket != -1) close(serverSocket);
}

void TCPServer::start(){
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == -1){
        std::cerr << "failed to make the socket" << std::endl;
        return;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET; //используем адресацию IPv4
    addr.sin_port = htons(port); //будем слушать на переданном нам порте
    addr.sin_addr.s_addr = INADDR_ANY; //принимать сообщения от любого адреса в сети

    if(bind(serverSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1){
        std::cerr << "failed to bind" << std::endl;
        return;
    }
    if(listen(serverSocket, 10) == -1){
        std::cerr << "failed to start listening" << std::endl;
        return;
    }

    while(true){
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if(clientSocket == -1) {
            std::cerr << "failed to accept message" << std::endl;
            continue;
        }
        handleClient(clientSocket);
    }
}

void TCPServer::handleClient(int clientSocket){}