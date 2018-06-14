#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
// #include "cJSON.c"
#include "user.c"
#include "playList.c"
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
void addPlayList(){
	char name[25];
	char path[25];
	char *userJson = NULL;

	printf("%s\n", "PlayList Name: ");
	scanf("%s",name);
	printf("%s\n", "Path user owner: ");
	scanf("%s",path);

	userJson = savePlayList(name,path);
	if(userJson != NULL){
		printf("%s\n", userJson);
	}else{
		printf("%s\n", " Play list wasn't created" );
	}
}
void addMusicPlayList(){
	char path[200];
	int idPlayList;
	int idMusicAudio;

	printf("%s\n", "Path user owner: ");
	scanf("%s",path);
	printf("%s\n", "PID  play list: ");
	scanf("%d",&idPlayList);
	printf("%s\n", "PID  audio music: ");
	scanf("%d",&idMusicAudio);

	char *userJson = addMusicToPlayList(path,idPlayList,idMusicAudio);
	if(userJson != NULL){
		printf("%s\n", userJson);
	}else{
		printf("%s\n", "AudioMusic have not added into play list" );
	}
}
void addMusic(){
	/*
	"id" : 1,
		"title":	"kissStranger",
		"artist":	"DNCE",
		"path":	"database/music/kissing_strangers.mp3",
		"duration":	"03:22"*/
	char title[50];
	char artist[50];
	char path[200];
	char pathImage[200];
	char duration[10];

	printf("%s", "Title: ");
	scanf("%s",title);
	printf("%s", "Artist: ");
	scanf("%s",artist);
	printf("%s", "Path Image: ");
	scanf("%s",pathImage);
	printf("%s", "Path: ");
	scanf("%s",path);
	printf("%s", "Duration: ");
	scanf("%s",duration);
	char *result = addNewMusic(title,artist,pathImage,path,duration);
	if(result != NULL){
		printf("%s\n", result);
	}else{
		printf("%s\n", "AudioMusic have not added into music repository" );
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
    	printf("Press the option: \n%s\n%s\n","Add new user: 1 \n Add PlayList: 2 \n Add Music : 3 \n Add MusictoPlayList: 4","Exit: 3");
    	scanf("%d",&selectedOption);
    	printf("%d\n",selectedOption );
    	switch(selectedOption) {
		   case 1:
		      	addNewUser();
		     	break;
		    case 2 :
		     	addPlayList();
		     	break; 
		    case 3 :
		      	addMusic();
		     	break; 
		    case 4:
				addMusicPlayList();
		      	break; 
		   case  5:
		      	flag = 0;
		      	break;
		   default : 
		   	printf("%s\n","Invalid option");
		}
    }
    return 0;
}