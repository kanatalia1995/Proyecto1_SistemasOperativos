
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
    char *buffer;
    char *buffer_message;
    // printf("path mp3%s\n", path  );
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
        // printf("lenght file%d\n",length );
        fseek(file, 0, SEEK_SET);
        buffer = malloc (256);
        while (!feof(file)){
            int rval = fread(buffer, 1, sizeof(256), file);
            send(socket_num, buffer, rval, 0);
            // printf("%d\n", rval);
        }
        fclose(file);
    }
    free(buffer);
}


char *getCommandFromJson(char* json){
    cJSON *data = cJSON_Parse(json);
    if (data == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                free(data);
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
        while (!feof(file)){
            int rval = fread(buffer, 1, sizeof(256), file);
            send(socket_num, buffer, rval, 0);
        }
        fclose(file);
    }
    free(buffer);
}

char *getName(char* json){
    cJSON *data = cJSON_Parse(json);
    if (data == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                free(data);
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
                free(data);
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
    char buffer[1024] = {0};
    int sizeJson = strlen(user_json);
    // printf("%s\n",user_json );
    send(socket_num ,&sizeJson, sizeof(int) , 0 );
    send(socket_num , user_json, strlen(user_json) , 0 ); //Send all user information
    while(flag){
        valread = read( socket_num, buffer, 1024);
        char* command = getCommandFromJson(buffer);
        // printf("command%s\n", command );
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
                printf("asadsa%s\n",audio_path );
                if(audio_path == NULL){
                    send(socket_num ,AUDIO_NOT_FOUND, strlen(AUDIO_NOT_FOUND), 0 );
                }else{
                    sendMp3Stream(audio_path);
                }
            }
            //CREATE NEW USER PLAY LIST
            else if(strcmp(command,CREATE_PLAYLIST) == 0){
                char* playListName = getName(buffer);
                if(playListName == NULL){
                    send(socket_num ,PLAYLIST_NAME_ERROR, strlen(PLAYLIST_NAME_ERROR), 0 );
                }else{
                    char *result = savePlayList(playListName,pathUser);
                    if (result == NULL) {
                         send(socket_num ,PLAYLIST_CREATE_ERROR, strlen(PLAYLIST_CREATE_ERROR), 0 );
                         //LOGGER
                    }else{
                        send(socket_num ,PLAYLIST_WAS_CREATED, strlen(PLAYLIST_WAS_CREATED), 0 );
                    }
                    
                }
            }
            else {
                send(socket_num ,UNKNOW_OPTION, strlen(UNKNOW_OPTION), 0 );
            }
        }
        // buffer = {0};
        
    }
    free(user_json);
    close(socket_num);
}

