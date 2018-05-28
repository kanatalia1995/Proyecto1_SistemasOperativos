
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

typedef struct thread_data {
 char* data;
 char* path;
 int socket;
 int sockfd;
} tdata_t; 

int socket_num; //GLOBAL SOCKET VALUE


void *sendMp3Stream(char *path){
    FILE* file;
    
    int size_send;
    // printf("path mp3%s\n", path  );
    if( access(path, F_OK) == -1 ){
        char metadata[] =  ERROR_OPEN_AUDIO_FILE;
        char * message = strcat(metadata, path);
        logger(message);
        size_send= strlen(ERROR_OPEN_AUDIO_FILE);
        send(socket_num,&size_send,sizeof(int),0);
        send(socket_num, ERROR_OPEN_AUDIO_FILE,size_send, 0);
    }
    else{
        file = fopen(path,"rb");
        fseek(file, 0, SEEK_END);
        int length = ftell(file);
        send(socket_num,&length,sizeof(int),0); // SEND SIZE FIRST NOTE:send all file information
        // printf("lenght file%d\n",length );
        char buffer[256] = {0};
        fseek(file, 0, SEEK_SET);
        while (!feof(file)){
            int rval = fread(buffer, 1, sizeof(256), file);
            send(socket_num, buffer, rval, 0);
            // printf("%d\n", rval);
        }
        fclose(file);
    }
    // free(buffer);
}


char *getCommandFromJson(char* json){
    cJSON *data = cJSON_Parse(json);
    if (data == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                // free(data);
                return "ERROR PARSING FILE";
        }
    }
    cJSON *command = cJSON_GetObjectItemCaseSensitive(data, "command");
    cJSON *command_instance = cJSON_CreateString(command->valuestring);
    cJSON_Delete(data);
    return command_instance->valuestring;
}

void sendImageData(char *path){
    FILE* file;
    
    if( access(path, F_OK) == -1 ){
        char metadata[] =  ERROR_OPEN_IMAGE;
        char * message = strcat(metadata, path);
        logger(message);
        int size_send= strlen(ERROR_OPEN_IMAGE);
        send(socket_num,&size_send,sizeof(int),0);
        send(socket_num, ERROR_OPEN_IMAGE,size_send, 0);
    }
    else{
        file = fopen(path,"rb");
        fseek(file, 0, SEEK_END);
        int length = ftell(file);
        send(socket_num,&length,sizeof(int),0);
        fseek(file, 0, SEEK_SET);
        char buffer[256];
        while (!feof(file)){
            int rval = fread(buffer, 1, sizeof(256), file);
            send(socket_num, buffer, rval, 0);
        }
        fclose(file);
    }
}

char *getName(char* json){
    cJSON *data = cJSON_Parse(json);
    if (data == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                return "ERROR PARSING FILE";
        }
    }
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data, "name");
    cJSON *name_instance = cJSON_CreateString(name->valuestring);
    cJSON_Delete(data);
    return name_instance->valuestring;
}
char *getPath(char* json){
    cJSON *data = cJSON_Parse(json);
    if (data == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                return "ERROR PARSING FILE";
        }
    }
    cJSON *path = cJSON_GetObjectItemCaseSensitive(data, "path");
    cJSON *path_instance = cJSON_CreateString(path->valuestring);
    cJSON_Delete(data);
    return path_instance->valuestring;
}

//PLAY LIST SERVICE




void *threadFunction(void *threadArg) {
    tdata_t *data = (tdata_t *) threadArg;
    // close(data->sockfd);
    char *user_json = data->data;
    char *pathUser = data->path;
    if (pathUser == NULL){
        printf("%s\n", "error");
    }
    // printf("pathUser%s\n",pathUser );
    socket_num = data->socket;
    int flag = 1;
    int valread;
    // char buffer[1024] = {0};
    int sizeJson = strlen(user_json);
    int size_send;
    // printf("%s\n",user_json );
    send(socket_num ,&sizeJson, sizeof(int) , 0 );
    send(socket_num ,user_json,sizeJson , 0 ); //Send all user information
    while(flag){
        valread = read( socket_num,&size_send, sizeof(int));
        printf("size send %d\n",size_send );
        char buffer_command[size_send];
        valread = read( socket_num,buffer_command, size_send);
        printf("command : %s\n", buffer_command );
        char* command = getCommandFromJson(buffer_command);
        printf("command : %s\n", command );
        if (command== NULL){
            size_send= strlen(INVALID_OPTION_FORMAT);
            send(socket_num,&size_send,sizeof(int),0);
            send(socket_num ,INVALID_OPTION_FORMAT, size_send, 0 ); 
        }else {
            //EXIT
            if (strcmp(command, EXIT) == 0) {
                flag = 0;
            }
            //IMAGEFILE
            else if(strcmp(command,GET_IMAGE) == 0){
                char* image_path = getPath(buffer_command);
                if(image_path == NULL){
                    size_send= strlen(IMAGE_NOT_FOUND);
                    send(socket_num,&size_send,sizeof(int),0);
                    send(socket_num ,IMAGE_NOT_FOUND, size_send, 0 );
                }else{
                    sendImageData(image_path);
                }
            }
            //AUDIO FILE
            else if(strcmp(command,GET_AUDIO) == 0){
                char* audio_path = getPath(buffer_command);
                printf("asadsa%s\n",audio_path );
                if(audio_path == NULL){
                    size_send= strlen(AUDIO_NOT_FOUND);
                    send(socket_num,&size_send,sizeof(int),0);
                    send(socket_num ,AUDIO_NOT_FOUND, size_send, 0 );
                }else{
                    sendMp3Stream(audio_path);
                }
            }
            //CREATE NEW USER PLAY LIST
            else if(strcmp(command,CREATE_PLAYLIST) == 0){
                char* playListName = getName(buffer_command);
                if(playListName == NULL){
                    size_send= strlen(PLAYLIST_NAME_ERROR);
                    send(socket_num,&size_send,sizeof(int),0);
                    send(socket_num ,PLAYLIST_NAME_ERROR, size_send, 0 );
                }else{
                    char *result = savePlayList(playListName,pathUser);
                    if (result == NULL) {
                        size_send= strlen(PLAYLIST_CREATE_ERROR);
                        send(socket_num,&size_send,sizeof(int),0);
                        send(socket_num ,PLAYLIST_CREATE_ERROR, size_send, 0 );
                         //LOGGER
                    }else{
                        size_send= strlen(PLAYLIST_WAS_CREATED);
                        send(socket_num,&size_send,sizeof(int),0);
                        send(socket_num ,PLAYLIST_WAS_CREATED, size_send, 0 );
                    }
                    
                }
            }
            else {
                send(socket_num ,UNKNOW_OPTION, strlen(UNKNOW_OPTION), 0 );
            }
        }
        // buffer = {0};
        
    }
    // free(threadArg);
    close(socket_num);
}

