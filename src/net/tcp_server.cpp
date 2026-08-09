#include "tcp_server.hpp"

TCPServer::TCPServer(int port): port(port){
    socketHandle = -1;
}

TCPServer::~TCPServer(){
    if(socketHandle != -1) close(socketHandle);
}
