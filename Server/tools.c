#include <stdio.h>
#include <stdlib.h>
#include <time.h>



//References
//https://stackoverflow.com/questions/5153677/reading-a-string-from-a-file
// https://stackoverflow.com/questions/8272319/how-can-i-return-file-contents-from-a-function

char *openJSONFile(char* path){
	    char *buffer = 0;
        long length;
        FILE *f = fopen (path, "r");
        if (f)
        {
            fseek (f, 0L, SEEK_END);
            length = ftell (f);
            printf("LENGTH%ld\n", length );
            fseek (f, 0L, SEEK_SET);
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

int saveJsonFile(char* file,char* path){
    FILE * file_ptr;
    file_ptr = fopen (path, "w+");
    if (file_ptr == NULL){
        return 0;
    }
    fprintf(file_ptr,"%s" ,file);
    fclose(file_ptr);
    return 1;
}

void logger(char* message){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %d-%d-%d %d:%d:%d   %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,message); 
}
