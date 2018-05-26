#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "user.c"


#define BUZZ_SIZE 1024


void addNewUser(){
	char name[25];
	char pass[25];
	char path[25];
	char *userJson = NULL;

	printf("%s\n", "User Name: ");
	scanf("%s",name);
	printf("%s\n", "Password: ");
	scanf("%s",pass);
	printf("%s\n", "Information Path: ");
	scanf("%s",path);

	userJson = saveUserInformation(name,pass,path);
	if(userJson != NULL){
		printf("%s\n", userJson);
	}
	
}

int main(int argc, char *argv[])
{

	char str[] = "database/users/users.json";
	char user[] = "User1";
	char pass[] = "pass1";
	int *status = 0;
    char *string  = validateConnection("{\"user\": \"User1\" ,\"password\": \"pass1\" }");
    if(string == NULL){
    	printf("%s\n", "String == NULL");
    }else{
    	printf("%s\n",string);
    }
    // printf("%s\n",string);
    // char *pathUser = getPathUser(user,pass,string);
    // printf("%s\n",pathUser);
    int flag = 1;
    int selectedOption = 0;


    printf("-----***JukeOS Editor***-----\n");
    while(flag){
    	printf("Press the option: \n%s\n%s\n","Add new user: 1","Exit: 2");
    	scanf("%d",&selectedOption);
    	printf("%d\n",selectedOption );
    	switch(selectedOption) {
		   case 1:
		      addNewUser();
		      break; 
		   case 2 :
		      flag = 0;
		      break;
		   default : 
		   	printf("%s\n","Invalid option");
		}
    }
    return 0;
}