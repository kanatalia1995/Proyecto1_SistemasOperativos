// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "cJSON.c"
#include "message.c"
#include "user.c"
#include "playList.c"
#include "connections.c"
#include "thread.c"


int main(int argc, char const *argv[])
{
   int sockfd, newsockfd, portno, clilen,valread;
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = PORT;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */
   
   listen(sockfd,20);
   clilen = sizeof(cli_addr);
   int new_socket;
   int errorSize;
   
   while (1) {
        new_socket = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (new_socket < 0){
          printf("Error created new socket\n");
        }else{
          printf("%s %d\n", "New user in socket: ",new_socket);
          pthread_t thread_id;
          tdata_t *data = (tdata_t *) malloc(sizeof(tdata_t));
          data->socket = new_socket;
          data->sockfd = sockfd;
          pthread_create(&thread_id, NULL, threadFunction,(void *) data);
        }
  }  

    
}

