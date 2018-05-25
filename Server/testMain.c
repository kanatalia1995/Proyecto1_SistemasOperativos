#include <stdio.h>
#include "user.c"

#define BUZZ_SIZE 1024

int main(int argc, char *argv[])
{
	char str[] = "database/users/users.json";
	char user[] = "User1";
	char pass[] = "pass1";
	int *status = 0;
    char *string  = openJSONFile("database/users/users.json");
    // printf("%s\n",string);
    char *pathUser = getPathUser(user,pass,string);
    printf("%s\n",pathUser);
    return 0;
}