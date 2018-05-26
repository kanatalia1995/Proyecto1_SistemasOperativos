// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "message.c"
#include "user.c"
#include "connections.c"


typedef struct thread_data {
 char* data;
 int socket;
 int sockfd;
} tdata_t; 


void *threadFunction(void *threadArg) {
    tdata_t *data = (tdata_t *) threadArg;
    // close(data->sockfd);
    char *user_json = data->data;
    int  socket = data->socket;
    int flag = 1;
    int valread;
    char buffer[124] = {0};
    send(socket , user_json, strlen(user_json) , 0 ); //Send all user information
    while(flag){
        valread = read( socket, buffer, 124);
        if (strcmp(buffer, "exit") == 0) {
            flag = 0;
        } 
        else {
            send(socket ,UNKNOW_OPTION, strlen(UNKNOW_OPTION) , 0 );
        }
    }
}




int main(int argc, char const *argv[])
{
    int sockfd, newsockfd, portno, clilen,valread;
   char buffer[126];
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
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   int new_socket;
   
   while (1) {
        new_socket = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        //User validation
        valread = read( new_socket , buffer, 126); // receive user information like json;
        printf("%s\n",buffer );// INSERT LOG
        char *userPath = validateConnection(buffer);
        if (userPath == NULL){
            printf(INVALID_USER);//LOg
            send(new_socket , INVALID_USER , strlen(INVALID_USER) , 0 );
        }else{
            pthread_t thread_id;
            char *userInfo = getUserInformation(userPath);
            tdata_t *data = (tdata_t *) malloc(sizeof(tdata_t));
            data-> data= userInfo;
            data->socket = new_socket;
            data->sockfd = sockfd;
            pthread_create(&thread_id, NULL, threadFunction,(void *) data);
            char title[50] = USER_INIT;
            char *message = strcat(title,getUserName(userInfo));
            logger(message);
            close(sockfd);
        }  
    }
    
}

