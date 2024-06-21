#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <dirent.h>
#include <stdlib.h>
#include<string.h>
#include <grp.h>




void ls(char f_name[500]){
    struct dirent **file_names;
    
    if(strlen(f_name)==0){
        int args = scandir(".", &file_names, NULL, alphasort);
        if(args<0){
            perror("scandir");
            
        }
        else{
            int i =0;
            while(i<args){
                if(file_names[i]->d_name[0]!='.'){
                    printf("%s ", file_names[i]->d_name);
                }
                free(file_names[i++]);

            }
            free(file_names);
            printf("\n");

        }
    }
    else{
        int args = scandir(f_name, &file_names, NULL, alphasort);
        if(args<0){
            perror("scandir");
            
        }
        else{
            int i =0;
            while(i<args){
                if(file_names[i]->d_name[0]!='.'){
                    printf("%s ", file_names[i]->d_name);
                }
                free(file_names[i++]);

            }
            free(file_names);
            printf("\n");

        }
    }
}

void lsA(char f_name[500]){
    struct dirent **file_names;
    
    if(strlen(f_name)==0){
        int args = scandir(".", &file_names, NULL, alphasort);
        if(args<0){
            perror("scandir");
            
        }
        else{
            int i =0;
            while(i<args){
                printf("%s ", file_names[i]->d_name);
                free(file_names[i++]);

            }
            free(file_names);
            printf("\n");

        }
    }
    else{
        int args = scandir(f_name, &file_names, NULL, alphasort);
        if(args<0){
            perror("scandir");
            
        }
        else{
            int i =0;
            while(i<args){
                printf("%s ", file_names[i]->d_name);
                
                free(file_names[i++]);

            }
            free(file_names);
            printf("\n");

        }
    }
}

void ls_1(char f_name[500]){
    struct dirent **file_names;
    
    if(strlen(f_name)==0){
        int args = scandir(".", &file_names, NULL, alphasort);
        if(args<0){
            perror("scandir");
            
        }
        else{
            int i =0;
            while(i<args){
                if(file_names[i]->d_name[0]!='.'){
                    printf("%s %ju", file_names[i]->d_name, (__uintmax_t)file_names[i]->d_ino);
                    printf("\t");
                }
                free(file_names[i++]);

            }
            free(file_names);
            printf("\n");

        }
    }
    else{
        int args = scandir(f_name, &file_names, NULL, alphasort);
        if(args<0){
            perror("scandir");
            
        }
        else{
            int i =0;
            while(i<args){
                if(file_names[i]->d_name[0] != '.'){
                    printf("%s %ju", file_names[i]->d_name, (__uintmax_t)file_names[i]->d_ino);
                    printf("\t");
                }
                free(file_names[i++]);

            }
            free(file_names);
            printf("\n");

        }
    }


}

int main(int argc, char const *argv[]){
    // char arg[100][100] ={"", "ls -1"};
    // int ar =2;
    char str[1024] = "";
    strcat(str, argv[1]);


    // printf("%d", argc);
    for (int k = 2; k < argc; k++)
    {
        strcat(str, " ");
        strcat(str, argv[k]);
        
    }
    // printf("%s", str);

    char ident[100]= "";
    char f_name[1000] = "";
    // printf("%s haan", argv[1]);
    if(argc>1){
        char *token = strtok(str, " ");

        if(strcmp(token,"ls")==0){
            // printf("yes");
            token = strtok(NULL, " ");
            // printf("%s", token);
            if(token!=NULL){
                if(token[0]=='-'){
                    strcpy(ident, token);
                    token = strtok(NULL, " ");
                    if(token!=NULL){
                        strcpy(f_name , token);
                    }

                }
                else{
                    strcpy(f_name , token);
                }
            }

        }
        else{
            printf("wrong command name");
            return 1;
        }

    

        if(ident[0]== '\0'){
            ls(f_name);
        }
        else if(ident[1] == 'a'){
            lsA(f_name);
        }
        else if(ident[1]=='1'){
            ls_1(f_name);
        }
    }
    else{
        printf("wrong command");
        return 1;
    }
    return 0;
    
}