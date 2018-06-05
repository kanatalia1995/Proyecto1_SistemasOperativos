
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


void sendLog(char* message, char* meta){
    char title[150];
    strcpy(title,meta);
    char* res = strcat(title,message);
    logger(res);
}


void *sendMp3Stream(char *path){
    FILE* file;
    
    int size_send;
    // printf("path mp3%s\n", path  );
    if( access(path, F_OK) == -1 ){
        char metadata[] =  ERROR_OPEN_AUDIO_FILE;
        char * message = strcat(metadata, path);
        logger(message);
        size_send= strlen(ERROR_OPEN_AUDIO_FILE);
        // send(socket_num,&size_send,sizeof(int),0);
        send(socket_num, ERROR_OPEN_AUDIO_FILE,size_send, 0);
    }
    else{
        file = fopen(path,"rb");
        fseek(file, 0, SEEK_END);
        int length = ftell(file);
        // send(socket_num,&length,sizeof(int),0); // SEND SIZE FIRST NOTE:send all file information
        // printf("lenght file%d\n",length );
        char buffer[512] = {0};
        fseek(file, 0, SEEK_SET);
        while (!feof(file)){
            int rval = fread(buffer, 1, sizeof(512), file);
            send(socket_num, buffer, rval, 0);
            // printf("%d\n", rval);
        }
        sendLog("Audio was sent",SEND_AUDIO);
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

char *getName(char* json, char* value){
    cJSON *data = cJSON_Parse(json);
    if (data == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                return "ERROR PARSING FILE";
        }
    }
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data, value);
    cJSON *name_instance = cJSON_CreateString(name->valuestring);
    cJSON_Delete(data);
    return name_instance->valuestring;
}

int  getNameInteger(char* json, char* value){
    cJSON *data = cJSON_Parse(json);
    if (data == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                return -1 ;
        }
    }
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data, value);
    cJSON *name_instance = cJSON_CreateNumber(name->valueint);
    cJSON_Delete(data);
    return name_instance->valueint;
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
    socket_num = data->socket;

    int valread;
    int init ;
    int size_send = 1024;
    int try =3;

    printf("size send %d\n",size_send );
    char buffer_command[size_send];
    valread = read( socket_num,buffer_command, size_send);
    // printf("data : %s\n", buffer_command );
    char* command = getCommandFromJson(buffer_command);
    printf("command : %s\n", command );
    sendLog(command,COMMAND);

    if (command == NULL){
        size_send= strlen(INVALID_OPTION_FORMAT);
        send(socket_num ,INVALID_OPTION_FORMAT, size_send, 0 ); 
    }else {
        if(strcmp(command,LOGIN)==0){
            char* pathUser = validateUser(buffer_command);
            sendLog(pathUser,USER_INIT);
            if (pathUser == NULL){
                printf(INVALID_USER);//LOg
                int errorSize = strlen(INVALID_USER);
                // send(socket_num ,&errorSize , sizeof(int) , 0 );
                send(socket_num , INVALID_USER , errorSize, 0 );
                sendLog("No found path",INVALID_USER);
            }else{
                char *user_json = getUserInformation(pathUser);
                 if(user_json == NULL){
                    printf("%s\n", "Error open user json");
                    send(socket_num , ERROR_USER_INFORMATION , strlen(ERROR_USER_INFORMATION), 0 );
                 }else{
                    //LOG MESSAGE 
                    char title[50] = USER_INIT;
                    char *message = strcat(title,getUserName(user_json));
                    logger(message);
                    printf("%s\n", user_json);
                    send(socket_num ,user_json,strlen(user_json) , 0 ); //Send all user information
                 }
                
            }
        }
        //IMAGEFILE
        else if(strcmp(command,GET_IMAGE) == 0){
            char* image_path = getPath(buffer_command);
            if(image_path == NULL){
                size_send= strlen(IMAGE_NOT_FOUND);
                // send(socket_num,&size_send,sizeof(int),0);
                send(socket_num ,IMAGE_NOT_FOUND, size_send, 0 );
            }else{
                sendImageData(image_path);
            }
        }
        //AUDIO FILE
        else if(strcmp(command,GET_AUDIO) == 0){
            char* audio_path = getPath(buffer_command);
            sendLog(audio_path,SEND_AUDIO);
            if(audio_path == NULL){
                size_send= strlen(AUDIO_NOT_FOUND);
                // send(socket_num,&size_send,sizeof(int),0);
                send(socket_num ,AUDIO_NOT_FOUND, size_send, 0 );
            }else{
                sendMp3Stream(audio_path);
            }
        }
        //CREATE NEW USER PLAY LIST
        else if(strcmp(command,CREATE_PLAYLIST) == 0){
            char* playListName = getName(buffer_command,"playListName");
            char* path = getName(buffer_command,"path");
            // char* path = getPathUserString(nameUser,get)
            if(playListName == NULL){
                // size_send= strlen(PLAYLIST_NAME_ERROR);
                // send(socket_num,&size_send,sizeof(int),0);
                sendLog("Empty play list name",CREATE_PLAYLIST );
                send(socket_num ,PLAYLIST_NAME_ERROR, size_send, 0 );
            }else{
                char *result = savePlayList(playListName,path);
                if (result == NULL) {
                    size_send= strlen(PLAYLIST_CREATE_ERROR);
                    // send(socket_num,&size_send,sizeof(int),0);

                    send(socket_num ,PLAYLIST_CREATE_ERROR, size_send, 0 );
                    sendLog(PLAYLIST_CREATE_ERROR,CREATE_PLAYLIST );
                     //LOGGER
                }else{
                    size_send= strlen(result);
                    // send(socket_num,&size_send,sizeof(int),0);
                    send(socket_num ,result, size_send, 0 );
                    sendLog("Play List was created",CREATE_PLAYLIST );
                }
                
            }
        }
        //GET_ALL_SONGS
        else if (strcmp(command,GET_ALL_SONGS) == 0){
            char* music = openJSONFile("database/music/musicLibrary.json");
            if(music == NULL){
                
                size_send= strlen(ERROR_OPEN_MUSIC_FILE);
                    // send(socket_num,&size_send,sizeof(int),0);
                send(socket_num ,ERROR_OPEN_MUSIC_FILE, size_send, 0 );
                sendLog("Database error",ERROR_OPEN_MUSIC_FILE );
            }else{
                size_send= strlen(music);
                    // send(socket_num,&size_send,sizeof(int),0);
                // printf("%s\n", music  );
                send(socket_num ,music, size_send, 0 ); 
                sendLog("Consult sucessful",GET_ALL_SONGS );  

            }         
        }
        /*
        json.put("command", "MATCH_MUSIC_PLAYLIST");
        json.put("music", JSON.musicToJson(music));
        json.put("path", user);
        json.put("playListId", id);*/
        else if(strcmp(command,MATCH_MUSIC_PLAYLIST) == 0){
            int music = getNameInteger(buffer_command,"musicId");
            char* path = getName(buffer_command,"path");
            int playListId= getNameInteger(buffer_command,"playListId");
            printf("%s %d %d\n", path,music,playListId );
            if (music == -1 && playListId == -1){
                size_send= strlen(INVALID_DATA);
                    // send(socket_num,&size_send,sizeof(int),0);
                send(socket_num ,INVALID_DATA, size_send, 0 );
                sendLog(" was not sent music or play data",INVALID_DATA ); 
            }else{
                char* result = addMusicToPlayList(path,playListId,music);
                if(result == NULL ){
                    size_send= strlen(INVALID_DATA);
                    // send(socket_num,&size_send,sizeof(int),0);
                    send(socket_num ,INVALID_DATA, size_send, 0 );
                    sendLog("Error occur when try to match music",INVALID_DATA ); 
                }else{
                    size_send= strlen(result);
                    // send(socket_num,&size_send,sizeof(int),0);
                    send(socket_num ,result, size_send, 0 );
                    sendLog(result,MATCH_MUSIC_PLAYLIST); 
                }            
            }

        }
        else {
            send(socket_num ,UNKNOW_OPTION, strlen(UNKNOW_OPTION), 0 );
        }
        
            // buffer = {0};
    }
    end:
    // free(threadArg);
        close(socket_num);
    // pthread_exit((void*) threadArg); 
}

