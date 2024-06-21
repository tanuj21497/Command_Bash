#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>



void md(char *dir){
    if(mkdir(dir, 0777)==-1){
        perror("mkdir ");

    }
}

void mdV(char *dir){
    if(mkdir(dir, 0777)==-1){
        perror("mkdirv ");

    }
    else{
        printf("mkdir successfully created directory-> %s", dir);

    }
}

void mdM(char *dir, int m){
    if(mkdir(dir, m)==-1){
        perror("mkdirm ");

    }
}


int main(int argc, char const *argv[])
{
    // char arg[100][100] = {"", "mkdir a"}; 
    char str[1024] = "";
    strcat(str, argv[1]);


    // printf("%d", argc);
    for (int k = 2; k < argc; k++)
    {
        strcat(str, " ");
        strcat(str, argv[k]);
        
    }
    char *token = strtok(str, " ");
    token =strtok(NULL, " ");
    while(token!=NULL){

        if(token[0]=='-'){
            if(token[1]=='v'){
                token = strtok(NULL, " ");
                mdV(token);
            }
            else if(token[1]=='m' && token[2]== '='){
                if(strlen(token)<6){
                    printf("Give right input of mode: ");
                    return 1;
                }
                else if(strlen(token)==7){
                    char store[5];
                    for (int i = 3; i < 7; i++)
                    {
                        store[i-3] = token[i];   
                    }

                    int m = atoi(store);
                    if(m!=400 && m!=777 && m!=100 && m!=200){
                        printf("Mode invalid, please select from 0400, 0777, 0100 or 0200");
                        return 1;
                    }
                    token = strtok(NULL, " ");
                    mdM(token, m);

                    
                }
                else if(strlen(token)==6){
                    char store[4];
                    for (int i = 3; i < 6; i++)
                    {
                        store[i-3] = token[i];   
                    }
                    int m = atoi(store);
                    if(m!=400 && m!=777 && m!=100 && m!=200){
                        printf("Mode invalid, please select from 0400, 0777, 0100 or 0200");
                        return 1;
                    }
                    token = strtok(NULL, " ");
                    mdM(token, m);
                }
            }

        }
        else{
            md(token);
        }
        token = strtok(NULL, " ");
    }
    return 0;
}






