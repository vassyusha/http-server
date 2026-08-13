#include "tcp_server.hpp"

int main(){
    TCPServer server(8080);

    server.start();

    return 0;
}