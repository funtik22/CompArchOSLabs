#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <chrono>
#include <thread>

#define MAX_PROCESS 1
#define PORT 3457

int main()
{
    std::chrono::milliseconds timespan(1000);
    int connection_socket, server_socket;
    struct sockaddr_in addr;
    char message[] = "pong";
    char buf[sizeof(message)];
    int bytes_read;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0)
    {
        perror("Failed to create a socket");
        exit(1);
    }
    std::cout<<"Create server socket #"<<server_socket<<std::endl;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("The address or port could not be binded to the socket");
        close(server_socket);
        exit(2);
    }
    std::cout<<"Bind port: "<<PORT<<" to socket"<<std::endl;
    if(listen(server_socket, MAX_PROCESS) != 0){
        perror("Can't start to listen");
        close(server_socket);
        exit(3);
    }
    std::cout<<"Server is ready to listen"<<std::endl;
    while(1)
    {
        connection_socket = accept(server_socket, NULL, NULL);
        if(connection_socket < 0)
        {
            perror("Сonnection has not been confirmed");
            close(server_socket);
            exit(3);
        }
        std::cout<<"Connection accepted"<<std::endl;
        while(1)
        {
            bytes_read = recv(connection_socket, buf, sizeof(buf), 0);
            if(bytes_read!= sizeof(buf)) {
                std::cout<<"Failed to get a message";
                break;
            }
            std::cout<<"Server get a message: "<<buf<<std::endl;
            std::this_thread::sleep_for(timespan);
            int bytes_send = send(connection_socket, message, sizeof(message), 0);
            if (bytes_send != sizeof(message)){
                std::cout<<"Failed to send a message"<<std::endl;
                break;
            } 
            std::cout<<"Server send a message: "<<message<<std::endl;  
        }
        close(connection_socket);
    }
    close(server_socket);
    return 0;
}
