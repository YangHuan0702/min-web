#include <iostream>


#include <thread>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


int main() {


    int server_fd = socket(AF_INET,SOCK_STREAM,0);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
