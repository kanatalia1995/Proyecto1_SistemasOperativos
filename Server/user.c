#include <stdlib.h>
#include <unistd.h>
#include "cJSON.c"
#include <string.h>
// #include "cJSON.h"


// typedef struct 
// {
// 	int id;
// 	char* name;
// 	PlayList *playlist;
// 	int playListCounter;
// 	int state; 
// } User ;


// User newUser(int pId, char* pName,int pState,PlayList *pPlayList,int pPlayListCounter)
// {
// 	User user;
// 	user.id = pId;
// 	user.name = pName;
// 	user.state = pState;

// 	user.playListCounter = pPlayListCounter;
// 	user.playlist = pPlayList;//(PlayList *)malloc(sizeof(PlayList)*user.playListCounter)
// 	return User;
// }

// void addUserPlayList(User* pUser ,PlayList pPLayLIst){
// 		pUser->playListCounter++;
// 		pUser->playList= (PlayList *)realloc(pUser.playList,sizeof(PlayList)* pUser.playListCounter);
// 		pUser->playlist[pUser.playListCounter-1] = &pPLayLIst; // Copy the playList Information 
// 		return 1;
// 	}
// }
// PlayList getPlayList(User pUser, char* pPlayName){
// 	for(int i = 0; i>= pUser.playListCounter; i++){
// 		if (pUser.playlist[i].name == pPlayName ){
// 			return pUser.playlist[i];
// 		}
// 	}
// 	return 0;
// }

#define BUFFER_SIZE 1024
//https://stackoverflow.com/questions/5153677/reading-a-string-from-a-file
// https://stackoverflow.com/questions/8272319/how-can-i-return-file-contents-from-a-function

char *openJSONFile(char* path){
	char *buffer = 0;
        long length;
        FILE *f = fopen (path, "r");
        if (f)
        {
            fseek (f, 0, SEEK_END);
            length = ftell (f);
            fseek (f, 0, SEEK_SET);
            buffer = malloc (length);
            if (buffer)
            {
                fread (buffer, 1, length, f);
            }
            fclose (f);
        }
        // printf("JSON FILE%s\n",buffer);
        return buffer;
}


char *getPathUser(char* pUserName,char* pUserPass,char* data){
	cJSON *user_json = cJSON_Parse(data);
	const cJSON *users = NULL;
	const cJSON *user = NULL;
	cJSON *path = NULL; 
	char *pathString = NULL;
	users = cJSON_GetObjectItemCaseSensitive(user_json, "users");
    cJSON_ArrayForEach(user, users)
    {

        cJSON *name = cJSON_GetObjectItemCaseSensitive(user, "name");
        cJSON *password = cJSON_GetObjectItemCaseSensitive(user, "password");

        if ((strcmp(name->valuestring,pUserName) == 0) && (strcmp(password->valuestring,pUserPass)==0))
        {
            
    
            path = cJSON_GetObjectItemCaseSensitive(user, "path");
            cJSON *pathS = cJSON_CreateString(path->valuestring);
            pathString = pathS->valuestring;
            // printf("%s\n", pathString);
            goto end;
        }
    }
	end:
	    cJSON_Delete(user_json);
	    // printf("%s\n", pathString);
	    return pathString;
}


