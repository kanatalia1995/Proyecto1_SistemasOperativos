#include <stdlib.h>
#include <unistd.h>
// #include "cJSON.c"
#include <string.h>
#include <stdio.h>
// #include "tools.c"
// #include "tools.c"
//Init empty play list

#define MUSIC_URL "database/music/musicLibrary.json"

cJSON * createMusic(int pId,char *ptitle,char *partist,char *pPathImage,char *ppath, char *pduration){
    cJSON *id = cJSON_CreateNumber(pId);
    cJSON *title = cJSON_CreateString(ptitle);
    cJSON *artist = cJSON_CreateString(partist);
    cJSON *path = cJSON_CreateString(ppath);
    cJSON *pathImage = cJSON_CreateString(pPathImage);
    cJSON *duration  = cJSON_CreateString(pduration); 
    cJSON *music = cJSON_CreateObject();
    cJSON_AddItemToObject(music, "id", id);
    cJSON_AddItemToObject(music, "title", title);
    cJSON_AddItemToObject(music, "artist", artist);
    cJSON_AddItemToObject(music, "pathImage", pathImage);
    cJSON_AddItemToObject(music, "path", path);
    cJSON_AddItemToObject(music, "duration", duration);
    return music;
}

char *addNewMusic(char *ptitle,char *partist,char *pPathImage, char *ppath, char *pduration){
    char * data = NULL;
    char *message = NULL;
    if ( (data = openJSONFile(MUSIC_URL))== NULL) return NULL;

    cJSON *musicList = cJSON_Parse(data);
    if (musicList == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                // free(data);
                return "ERROR PARSING FILE";
        }
    }
    cJSON *musicArray = cJSON_GetObjectItemCaseSensitive(musicList, "musicList");
    cJSON *music = createMusic(cJSON_GetArraySize(musicArray)+1,ptitle,partist,pPathImage,ppath,pduration);
    cJSON_AddItemToArray(musicArray,music);
    if(saveJsonFile(cJSON_Print(musicList),MUSIC_URL) == 1) message = "MUSIC WAS CREATED SUCCESFULLY";
    else message = "MUSIC WAS NOT SAVED";
    cJSON_Delete(musicList);
    return message;
}

cJSON *getAudioData(int pId){
    char * data = NULL;
    if ( (data = openJSONFile(MUSIC_URL))== NULL) return NULL;

    cJSON *musicList = cJSON_Parse(data);
    if (musicList == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                // free(data);
                return NULL;
        }
    }
    cJSON *musicArray = cJSON_GetObjectItemCaseSensitive(musicList, "musicList");
    cJSON *music = NULL;
    cJSON_ArrayForEach(music, musicArray){
        cJSON *id = cJSON_GetObjectItemCaseSensitive(music, "id");
        if(cJSON_IsNumber(id)){
            if (id->valueint == pId){
                // free(data);
                return music;
            }
        }
    }
    // free(data);
    cJSON_Delete(musicList);
    return NULL;

}
char *getAudioImagePath(int pId){
    char * data = NULL;
    if ( (data = openJSONFile(MUSIC_URL))== NULL) return NULL;

    cJSON *musicList = cJSON_Parse(data);
    if (musicList == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                // free(data);
                return NULL;
        }
    }
    cJSON *musicArray = cJSON_GetObjectItemCaseSensitive(musicList, "musicList");
    cJSON *music = NULL;
    cJSON_ArrayForEach(music, musicArray){
        cJSON *id = cJSON_GetObjectItemCaseSensitive(music, "id");
        if(cJSON_IsNumber(id)){
            if (id->valueint == pId){
                cJSON *path = cJSON_GetObjectItemCaseSensitive(music,"pathImage");
                cJSON *stringPath = cJSON_CreateString(path->valuestring);
                cJSON_Delete(musicList);
                return stringPath->valuestring;
            }
        }
    }
    // free(data);
    cJSON_Delete(musicList);
    return NULL;

}
char *getAudioPath(int pId){
    char * data = NULL;
    if ( (data = openJSONFile(MUSIC_URL))== NULL) return NULL;

    cJSON *musicList = cJSON_Parse(data);
    if (musicList == NULL){
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL){
                fprintf(stderr, "Error before: %s\n", error_ptr);
                // log
                // free(data);
                return NULL;
        }
    }
    cJSON *musicArray = cJSON_GetObjectItemCaseSensitive(musicList, "musicList");
    cJSON *music = NULL;
    cJSON_ArrayForEach(music, musicArray){
        cJSON *id = cJSON_GetObjectItemCaseSensitive(music, "id");
        if(cJSON_IsNumber(id)){
            if (id->valueint == pId){
                cJSON *path = cJSON_GetObjectItemCaseSensitive(music,"path");
                cJSON *stringPath = cJSON_CreateString(path->valuestring);
                cJSON_Delete(musicList);
                return stringPath->valuestring;
            }
        }
    }
    // free(data);
    cJSON_Delete(musicList);
    return NULL;

}