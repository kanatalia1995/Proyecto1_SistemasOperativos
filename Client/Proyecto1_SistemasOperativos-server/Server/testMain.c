#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "user.c"
#include <id3v2lib.h>


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

	// char str[] = "database/users/users.json";
	// char user[] = "User1";
	// char pass[] = "pass1";
	// int *status = 0;
 //    char *string  = validateConnection("{\"user\": \"User1\" ,\"password\": \"pass1\" }");
 //    if(string == NULL){
 //    	printf("%s\n", "String == NULL");
 //    }else{
 //    	printf("%s\n",string);
 //    }
	// ID3v2_tag* tag = load_tag("file.mp3"); // Load the full tag from the file
	// if(tag == NULL)
	// {
	// 	tag = new_tag();
	// }
		
	// // Load the fields from the tag
	// ID3v2_frame* artist_frame = tag_get_artist(tag); // Get the full artist frame
	// // We need to parse the frame content to make readable
	// ID3v2_frame_text_content* artist_content = parse_text_frame_content(artist_frame); 
	// printf("ARTIST: %s\n", artist_content->data); // Show the artist info
		
	// ID3v2_frame* title_frame = tag_get_title(tag);
	// ID3v2_frame_text_content* title_content = parse_text_frame_content(title_frame);
	// printf("TITLE: %s\n", title_content->data);
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