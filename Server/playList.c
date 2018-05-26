#include <stdlib.h>
#include <unistd.h>
#include "cJSON.c"
#include <string.h>
#include <stdio.h>
#include "tools.c"

cJSON *createPlayList(char* pName, char* pPass,char* pPath){
    cJSON *name = cJSON_CreateString(pName);
    cJSON *pass = cJSON_CreateString(pPass);
    cJSON *path = cJSON_CreateString(pPath);

    cJSON *user = cJSON_CreateObject();
    cJSON_AddItemToObject(user, "name", name);
    cJSON_AddItemToObject(user, "password", pass);
    cJSON_AddItemToObject(user, "path", path);
    return user;
}

char *saveUserInformation(char* pName, char* pPass,char* pPath){
    cJSON *users = NULL;
    cJSON *user = NULL;
    char  *data = openJSONFile(DATABASE_USER);
    printf("data:    %s\n",data);
    cJSON *users_json = cJSON_Parse(data);
        char *string = cJSON_Print(users_json);
    printf("%s\n",string );
    user=  createUserJson(pName,pPass,pPath);
    users= cJSON_GetObjectItemCaseSensitive(users_json, "users");
    cJSON_AddItemToArray(users,user);
    if( saveJsonFile(cJSON_Print(users_json),DATABASE_USER) == 1){
        return cJSON_Print(user );
    }else{
        return NULL;
    }

}