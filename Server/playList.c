#include <stdlib.h>
#include <unistd.h>
// #include "cJSON.c"
#include <string.h>
#include <stdio.h>
#include "music.c"
// #include "tools.c"
//Init empty play list
cJSON *createPlayList(char* pName, double pId){
    cJSON *name = cJSON_CreateString(pName);
    cJSON *id = cJSON_CreateNumber(pId);
    cJSON *musicAccount = cJSON_CreateNumber(0);
    cJSON *musicJson  = cJSON_CreateArray(); // If no music was sent, create empty array 
    cJSON *user = cJSON_CreateObject();
    cJSON_AddItemToObject(user, "id", id);
    cJSON_AddItemToObject(user, "name", name);
    cJSON_AddItemToObject(user, "musicAccount", musicAccount);
    cJSON_AddItemToObject(user, "musicList", musicJson);
    return user;
}

char *savePlayList(char* pName, char* pPath){
    cJSON *user = NULL;
    cJSON *playList = NULL;
    cJSON *playListArray = NULL;
    cJSON *counter = NULL;
    char  *data = openJSONFile(pPath);
    // printf("data:    %s\n",data);

    user = cJSON_Parse(data);
    if (user == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                free(data);
                return NULL;
        }
    }
    // printf("%s\n",cJSON_Print(user) );
    playListArray= cJSON_GetObjectItemCaseSensitive(user, "playListArray");
    // counter = cJSON_GetObjectItemCaseSensitive(user, "playListAccount");
    // printf("%s\n",cJSON_Print(counter) );
    // counter->valuedouble += 1;

    playList =  createPlayList(pName,cJSON_GetArraySize(playListArray)+1);
    cJSON_AddItemToArray(playListArray,playList);
    if( saveJsonFile(cJSON_Print(user),pPath) == 1){
        char *string =  cJSON_Print(playList);
        // free(data);
        cJSON_Delete(user);
        // free(playList);
        return string;
    }else{
        // free(data);
        cJSON_Delete(user);
        // free(playList);
        return NULL;
    }

}
char *addMusicToPlayList(char *pPathUser,int playListId,double musicId){
    cJSON *musicData = NULL; 
    cJSON *user = NULL;
    cJSON *playListArray = NULL;
    musicData = getAudioData(musicId); 
    char  *data = openJSONFile(pPathUser);
    // printf("data:    %s\n",data);

    user = cJSON_Parse(data);
    if (user == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // free(data);
                return NULL;
        }
    }

    playListArray= cJSON_GetObjectItemCaseSensitive(user, "playListArray");
    cJSON *playList = NULL;
    cJSON_ArrayForEach(playList,playListArray){
        cJSON *id = cJSON_GetObjectItemCaseSensitive(playList, "id");
        if(cJSON_IsNumber(id)){
            if (id->valueint == playListId){
                cJSON *music  =  getAudioData(musicId);
                cJSON *musicList = cJSON_GetObjectItemCaseSensitive(playList, "musicList");
                cJSON_AddItemToArray(musicList,music);
                if( saveJsonFile(cJSON_Print(user),pPathUser) == 1){
                    // free(data);
                    cJSON_Delete(user);
                    // ;
                    return "MUSIC ADDED ";
                }else{
                    // free(data);
                    cJSON_Delete(user);
                    // free(playList);
                    return NULL;
                }
                return cJSON_Print (music);
            }
        }
    }
    // free(data);
    cJSON_Delete(user);
    return NULL;

}
