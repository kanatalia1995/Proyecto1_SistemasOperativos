#include <stdlib.h>
#include <unistd.h>
#include "cJSON.c"
#include <string.h>
#include <stdio.h>
#include "tools.c"
// #include "cJSON.h"

#define DATABASE_USER "database/users/users.json"
#define USER_PATH  "database/users/"



char *getPathUser(char* pUserName,char* pUserPass,char* data){
	cJSON *user_json = cJSON_Parse(data);
    if (user_json == NULL) return NULL;
	const cJSON *users = NULL;
	const cJSON *user = NULL;
	cJSON *path = NULL; 
	char *pathString = NULL;
	users = cJSON_GetObjectItemCaseSensitive(user_json, "users");
    cJSON_ArrayForEach(user, users)
    {

        cJSON *name = cJSON_GetObjectItemCaseSensitive(user, "name");
        cJSON *password = cJSON_GetObjectItemCaseSensitive(user, "password");
        printf("%s\n",pUserName );
        if(cJSON_IsString(name) && cJSON_IsString(password)){
            if ((strcmp(name->valuestring,pUserName) == 0) && (strcmp(password->valuestring,pUserPass)==0))
            {
                
                path = cJSON_GetObjectItemCaseSensitive(user, "path");
                cJSON *pathS = cJSON_CreateString(path->valuestring);
                pathString = pathS->valuestring;
                printf("%s\n", pathString);
                goto end;
            }
        }
    }
	end:
	    cJSON_Delete(user_json);
        free(data);
        if(pathString == NULL) return NULL;
	    printf("%s\n", pathString);
	    return pathString;
}
int sanitizeUserInformation(char* param, char *pUser, char *pPass){
    cJSON *user_json = cJSON_Parse(param);
    if (param == NULL){
        return 0;
    }
    cJSON *user = NULL;
    cJSON *pass = NULL;
    user = cJSON_GetObjectItemCaseSensitive(user_json, "user");
    pass = cJSON_GetObjectItemCaseSensitive(user_json, "password");
    if(!cJSON_IsString(user) || !cJSON_IsString(pass)){
        cJSON_Delete(user_json); // Only close memory when occur a error
        return 0;
    } 
    strcpy(pUser,user->valuestring);
    strcpy(pPass,pass->valuestring);
    printf("%s%s\n",pUser,pPass );
    return 1;

}

char * validateConnection(char *info){
    char *user = (char *)malloc(50);
    char *pass = (char *)malloc(50);
    if (!sanitizeUserInformation(info,user,pass)) return NULL;
    printf("%s%s\n",user,pass );
    char * users = openJSONFile(DATABASE_USER);
    if (users == NULL) return NULL;
    return getPathUser(user,pass,users);
}

cJSON *createUserJson(char* pName, char* pPass,char* pPath){
    cJSON *name = cJSON_CreateString(pName);
    cJSON *pass = cJSON_CreateString(pPass);
    cJSON *path = cJSON_CreateString(pPath);

    cJSON *user = cJSON_CreateObject();
    cJSON_AddItemToObject(user, "name", name);
    cJSON_AddItemToObject(user, "password", pass);
    cJSON_AddItemToObject(user, "path", path);
    return user;
}



cJSON *createUserFile(char* pName){

    //"id": "1",
  // "name": "User1",
  // "playListAccount": "1",
  // "playListArray":
    cJSON *id = cJSON_CreateString(pName);
    cJSON *name = cJSON_CreateString(pName);
    cJSON *playListAccount = cJSON_CreateNumber(0);
    cJSON *playListArray = cJSON_CreateArray();

    // printf("%s\n", "createUserFile");
    cJSON *user = cJSON_CreateObject();
    cJSON_AddItemToObject(user, "id", id);
    cJSON_AddItemToObject(user, "name", name);
    cJSON_AddItemToObject(user, "playListAccount", playListAccount);
    cJSON_AddItemToObject(user, "playListArray",playListArray);
    // printf("%s\n",cJSON_Print(user) );
    return user;
}

int saveUserFile(char* pName){
    // printf("%s\n", "saveUserFile");
    cJSON *user = createUserFile(pName);
    // printf("%s\n",cJSON_Print(user) );
    char aPath[] = USER_PATH; 
    char *path =  strcat(aPath,pName);
    path = strcat(path,".json");
    return saveJsonFile( cJSON_Print(user),path);
}

char *saveUserInformation(char* pName, char* pPass,char* pPath){
    cJSON *users = NULL;
    cJSON *user = NULL;
    char  *data = openJSONFile(DATABASE_USER);
    if (data == NULL){
        return data;
    }
    cJSON *users_json = cJSON_Parse(data);
    //  char *string = cJSON_Print(users_json); // printf("%s\n",string );
    user=  createUserJson(pName,pPass,pPath);
    users= cJSON_GetObjectItemCaseSensitive(users_json, "users");
    cJSON_AddItemToArray(users,user);
    if(saveUserFile(pName)== 1) {
        if(saveJsonFile(cJSON_Print(users_json),DATABASE_USER) == 1) return cJSON_Print(user);
        else return NULL;
    }else{
        return NULL;
    }
}
char *getUserInformation(char* path){
    return openJSONFile(path);
}

char *getUserName(char* data){
    cJSON *user_json = cJSON_Parse(data);
    if(user_json == NULL) return NULL;
    cJSON *userName = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    cJSON *name = cJSON_CreateString(userName->valuestring);
    cJSON_Delete(user_json);
    return name->valuestring;

}






