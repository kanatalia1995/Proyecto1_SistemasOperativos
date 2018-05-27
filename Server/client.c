// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "connections.c"
#include "tools.c"

void saveImageFile(int sock){
    send(sock,"{\"command\": \"GET_IMAGE\",\"path\":\"database/music/images/kissing_strangers.jpg\"}",strlen("{\"command\": \"GET_IMAGE\",\"path\":\"database/music/images/kissing_strangers.jpg\"}"),0);
    int size_image = 0;
    int valread = read(sock, &size_image,sizeof(int));

    char *buffer_image = malloc(256);
    FILE *file = fopen("database/music/images/kissing_strangerscopy.jpg", "wb");
    int rval;
    while ( size_image > 0){
        rval = read(sock, buffer_image, sizeof(buffer_image), 0);
        fwrite(buffer_image, 1, rval, file);
        size_image-=rval;
    }
    printf("%s\n","IMAGE was saved" );
    fclose(file);
    // valread = read(sock, buffer_image,size_image);
    // printf("%s\n", buffer_image );
    // saveImageFile(buffer_image,"database/music/images/kissing_strangerscopy.jpg");
    free(buffer_image);
}
void saveMp3File(int sock){
    char path[] = "{\"command\": \"GET_AUDIO\",\"path\":\"database/music/kissing_strangers.mp3\"}";
    send(sock, "{\"command\": \"GET_AUDIO\",\"path\":\"database/music/kissing_strangers.mp3\"}",strlen( "{\"command\": \"GET_AUDIO\",\"path\":\"database/music/kissing_strangers.mp3\"}"),0);
    int size_audio = 0;
    int valread = read(sock, &size_audio,sizeof(int));

    char *buffer_audio = malloc(256);
    FILE *file = fopen("database/music/kissing_strangerscopy.mp3", "wb");
    int rval;
    while ( size_audio > 0){
        rval = read(sock, buffer_audio, sizeof(buffer_audio), 0);
        fwrite(buffer_audio, 1, rval, file);
        size_audio-=rval;
    }
    printf("%s\n","AUDIO was saved" );
    fclose(file);
    // valread = read(sock, buffer_image,size_image);
    // printf("%s\n", buffer_image );
    // saveImageFile(buffer_image,"database/music/images/kissing_strangerscopy.jpg");
    free(buffer_audio);
}
int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, URL_SERVER, &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    char * dataInfo = "{\"user\": \"User1\" ,\"password\": \"pass1\" }"; 
    send(sock , dataInfo , strlen(dataInfo) , 0 );
    printf("From server: message was sent\n");
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    saveImageFile(sock);
    saveMp3File(sock);
    send(sock,"{\"command\": \"EXIT\"}",strlen("{\"command\": \"EXIT\"}"),0);
    // valread = read( sock , buffer, 1024);
    // printf("%s\n",buffer);
    return 0;
}