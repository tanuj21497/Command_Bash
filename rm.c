#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>


void rm(char *f){
    if(unlink(f)!=0){
        perror(f);
    }
}

void rmd(char *f){
    if(rmdir(f)!=0){
        perror(f);
    }
}
void rmv(char *f){
    if(!unlink(f)){
        printf("rm -v command removed %s", f);
    }
    else{
        perror(f);
    }
}

int main(int argc, char const *argv[])

{
    // char arg[100][100] = {"", "rm -d a"};
    char str[1024]="";
    strcat(str, argv[1]);


    // printf("%d", argc);
    for (int k = 2; k < argc; k++)
    {
        strcat(str, " ");
        strcat(str, argv[k]);
        
    }
    char *token = strtok(str, " ");
    token = strtok(NULL, " ");
    if(token==NULL){
        printf("No directories given to rm");
        return 1;
    }
    while(token!=NULL){
        if(token[0] == '-'){
            if(token[1]=='d'){
                token = strtok(NULL," ");
                rmd(token);
            }
            else if(token[1]=='v'){
                token = strtok(NULL," ");
                rmv(token);
            }
        }
        else{
            // token = strtok(NULL," ");
            // printf("yes");

            rm(token);
        }
        token = strtok(NULL," ");
        
    }
    return 0;
}
