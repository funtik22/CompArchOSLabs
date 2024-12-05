#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <chrono>
#include <thread>

#define PORT 3457

int main(){
   
   std::chrono::milliseconds timespan(1000);

   char message[] = "ping";
   char buf[sizeof(message)];	

   struct sockaddr_in addr;
	
   int client_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (client_socket < 0){
   	perror("Failed to create a socket");
      exit(1);
   }
   std::cout<<"Create client socket #"<<client_socket<<std::endl;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);
   addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
   if(connect(client_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0){
      bool isConnect = false;
      for(int i = 0; i<5; i++){
         std::cout<<"try to connect..."<<std::endl;
         if(connect(client_socket, (struct sockaddr *)&addr, sizeof(addr)) >= 0){
            isConnect = true;
            break;
         }
         std::this_thread::sleep_for( std::chrono::milliseconds(5000));
      }
      if(!isConnect){
   	   perror("Failed to connect to server");
	      exit(2);
      }
   }
   std::cout<<"Connect to server port: "<<PORT<<std::endl;

   while(1){
      int bytes_send = send(client_socket, message, sizeof(message), 0);
      if (bytes_send != sizeof(message)){
         std::cout<<"Failed to send a message"<<std::endl;
         break;
      } 
      std::cout<<"Client send: "<<message<<std::endl;
      std::this_thread::sleep_for(timespan);
      int bytes_read = recv(client_socket, buf, sizeof(message), 0);
      if(bytes_read != sizeof(buf)) {
            std::cout<<"Failed to get a message";
            break;
      }
      std::cout<<"Client get: "<<buf<<std::endl;
      std::cout<<"========================================="<<std::endl;
   }
   close(client_socket);
}

