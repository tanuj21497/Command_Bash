#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>


extern int errno;


void pf(char *f_name){
    int file_descriptor = open(f_name, O_RDONLY);
    if(file_descriptor<0){
        perror("File not found: ");
        return;
    }
    int size;
    char reading_char;

    while ((size = read(file_descriptor, &reading_char, 1))){
        if(size<0){
            perror("Read Error: ");
            return;
        }

        if(write(STDIN_FILENO, &reading_char, 1)<0){
            if(errno!=EINTR){
                perror("Write Error ");
                return;
            }
        }
    }
    if(close(file_descriptor)<0){
        perror("Close Error: ");
        return;
    }
        
    
}

void pfd(char *f_name){
    char dollar[3] = "##";
    int file_descriptor = open(f_name, O_RDONLY);
    if(file_descriptor<0){
        perror("File not found: ");
        return;
    }
    int size;
    char reading_char;

    while ((size = read(file_descriptor, &reading_char, 1))){
        if(size<0){
            perror("Read Error: ");
            return;
        }
        if(reading_char == '\n'){
            if(write(STDIN_FILENO, dollar, 2)<0){
                if(errno!=EINTR){
                    perror("Write Error: ");
                    return;
                }
            }
        }

        if(write(STDIN_FILENO, &reading_char, 1)<0){
            if(errno!=EINTR){
                perror("Write Error: ");
                return;
            }
        }
    }
    if(close(file_descriptor)<0){
        perror("Close Error: ");
        return;
    }
        
    
}

void pfn(char *f_name){
    char dollar[3] = "##";
    int file_descriptor = open(f_name, O_RDONLY);
    if(file_descriptor<0){
        perror("File not found: ");
        return;
    }
    int size;
    char reading_char;
    int i =1;
    char buf[10];
    int flag =0;

    while ((size = read(file_descriptor, &reading_char, 1))){
        if(size<0){
            perror("Read Error: ");
            return;
        }

        if(i==1 || flag==1){
            sprintf(buf, "%d)", i);
            if(write(STDIN_FILENO, buf, 2)<0){
                if(errno!=EINTR){
                    perror("Write Error: ");
                    return;
                }
            }
            flag=0;
            i++;
        }

        if(reading_char == '\n'){
            flag=1;
        }

        if(write(STDIN_FILENO, &reading_char, 1)<0){
            if(errno!=EINTR){
                perror("Write Error: ");
                return;
            }
        }
    }
    if(flag==1){
        sprintf(buf, "%d)", i);
        if(write(STDIN_FILENO, buf, 2)<0){
            if(errno!=EINTR){
                perror("Write Error: ");
                return;
            }
        }
        flag=0;

    }
    if(close(file_descriptor)<0){
        perror("Close Error: ");
        return;
    }
        
    
}

int main(int argc, char const *argv[])
{
    // char arg[100][100] = {"", "cat hey.txt tan.txt"};
    // printf("yes");
    char str[1024] = "";
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
        printf("Please write some file name alongwith command name");
        return 1;
    }
            // printf("yes");

    while(token!=NULL){
        // printf("%s", token);
        if(token[0]=='-' && token[1]=='d'){
            token = strtok(NULL, " ");
            pfd(token);
        }
        else if(token[0]=='-' && token[1]=='n'){
            token = strtok(NULL, " ");
            pfn(token);
        }
        else{
            // printf("yes");
            pf(token);
        }
        token = strtok(NULL, " ");
    }
    return 0;
}


