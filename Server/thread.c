
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
// #include <pthread.h>
// #include "cJSON.c"

// #include "message.c"
// #include "user.c"

typedef struct thread_data {
 char* data;
 int socket;
 int sockfd;
} tdata_t; 

int socket_num; //GLOBAL SOCKET VALUE


void *sendMp3Stream(char *path){
    FILE* file;
    char *buffer;
    char *buffer_message;
    if( access(path, F_OK) == -1 ){
        char metadata[] =  ERROR_OPEN_AUDIO_FILE;
        char * message = strcat(metadata, path);
        logger(message);
        send(socket_num, ERROR_OPEN_AUDIO_FILE,strlen(ERROR_OPEN_AUDIO_FILE), 0);
    }
    else{
        file = fopen(path,"rb");
        fseek(file, 0, SEEK_END);
        int length = ftell(file);
        send(socket_num,&length,sizeof(int),0); // SEND SIZE FIRST NOTE:send all file information
        printf("%d\n",length );
        fseek(file, 0, SEEK_SET);
        buffer = malloc (256);
        // buffer_message = malloc(strlen(GET_BYTES));
        // int val ;
        // int flag = 1;
        // while (flag){
        //     val = read( socket_num, buffer_message, strlen(GET_BYTES));
        //     printf("%s\n",buffer_message );
        //     if(strcmp(buffer_message,GET_BYTES)== 0){
        //         int rval = fread(buffer, 1, sizeof(256), file);
        //         send(socket_num, buffer, rval, 0);
        //     }
        //     if(feof(file)){
        //         flag = 0;
        //     }
            
        // }
        while (!feof(file)){
            int rval = fread(buffer, 1, sizeof(256), file);
            send(socket_num, buffer, rval, 0);
            printf("%d\n", rval);
        }
        fclose(file);
        // send(socket_num, buffer, length, 0);
    }
    free(buffer);
}


char *getCommandFromJson(char* json){
    cJSON *data = cJSON_Parse(json);
    if(data == NULL) return NULL;
    cJSON *command = cJSON_GetObjectItemCaseSensitive(data, "command");
    cJSON *command_instance = cJSON_CreateString(command->valuestring);
    cJSON_Delete(data);
    return command_instance->valuestring;
}

void sendImageData(char *path){
    FILE* file;
    char *buffer;
    if( access(path, F_OK) == -1 ){
        char metadata[] =  ERROR_OPEN_IMAGE;
        char * message = strcat(metadata, path);
        logger(message);
        send(socket_num, ERROR_OPEN_IMAGE,strlen(ERROR_OPEN_IMAGE), 0);
    }
    else{
        file = fopen(path,"rb");
        fseek(file, 0, SEEK_END);
        int length = ftell(file);
        send(socket_num,&length,sizeof(int),0);
        fseek(file, 0, SEEK_SET);
        buffer = malloc (256);
        /*FILE *file = fopen(filename, "rb");
            err_abort("Test");
            while (!feof(file))
            {
                int rval = fread(buf, 1, sizeof(buf), file);
                send(sock, buf, rval, 0);
            }
        */
        while (!feof(file)){
            int rval = fread(buffer, 1, sizeof(256), file);
            send(socket_num, buffer, rval, 0);
        }
        fclose(file);
        // send(socket_num, buffer, length, 0);
    }
    free(buffer);
}

char *getPath(char* json){
    cJSON *data = cJSON_Parse(json);
    if(data == NULL) return NULL;
    cJSON *path = cJSON_GetObjectItemCaseSensitive(data, "path");
    cJSON *path_instance = cJSON_CreateString(path->valuestring);
    cJSON_Delete(data);
    return path_instance->valuestring;
}


void *threadFunction(void *threadArg) {
    tdata_t *data = (tdata_t *) threadArg;
    // close(data->sockfd);
    char *user_json = data->data;
    socket_num = data->socket;
    int flag = 1;
    int valread;
    char buffer[124] = {0};
    // printf("%s\n",user_json );
    send(socket_num , user_json, strlen(user_json) , 0 ); //Send all user information
    while(flag){
        valread = read( socket_num, buffer, 124);
        char* command = getCommandFromJson(buffer);
        if (command== NULL){
           send(socket_num ,INVALID_OPTION_FORMAT, strlen(INVALID_OPTION_FORMAT), 0 ); 
        }else {
            //EXIT
            if (strcmp(command, EXIT) == 0) {
                flag = 0;
            }
            //IMAGEFILE
            else if(strcmp(command,GET_IMAGE) == 0){
                char* image_path = getPath(buffer);
                if(image_path == NULL){
                    send(socket_num ,IMAGE_NOT_FOUND, strlen(IMAGE_NOT_FOUND), 0 );
                }else{
                    sendImageData(image_path);
                }
            }
            //AUDIO FILE
            else if(strcmp(command,GET_AUDIO) == 0){
                char* audio_path = getPath(buffer);
                if(audio_path == NULL){
                    send(socket_num ,AUDIO_NOT_FOUND, strlen(AUDIO_NOT_FOUND), 0 );
                }else{
                    sendMp3Stream(audio_path);
                }
            }else {
                send(socket_num ,UNKNOW_OPTION, strlen(UNKNOW_OPTION), 0 );
            }
        }
        
    }
    free(user_json);
    close(socket_num);
}

