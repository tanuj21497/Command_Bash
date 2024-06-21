#include<stdio.h>
#include<time.h>
#include<errno.h>
#include<string.h>
#include<sysexits.h>
#include<stdlib.h>
#include<string.h>

void date(){
    time_t r = time(NULL);
    if(r==-1){
        perror("");
        return;
    }

    struct tm *p;
    p= localtime(&r);
    if(p!=NULL){
        printf("%s", asctime(p));
    }
}

void dater(){
    time_t r = time(NULL);
    if(r==-1){
        perror("");
        return;
    }

    struct tm *p;
    p= gmtime(&r);
    if(p!=NULL){
        printf("%s", asctime(p));
    }
}

void dateu(char *str){
    struct tm s;
    time_t t;
    char *token = strtok(str, "/");
    // printf("%s", token);
    s.tm_mday = atoi(token);
    token = strtok(NULL, "/");
    // printf("%s", token);

    s.tm_mon = atoi(token)-1;
    token = strtok(NULL, "/");
    
    
    s.tm_year = atoi(token)-1900;
    token = strtok(NULL, "/");
    s.tm_hour = atoi(token);
    token = strtok(NULL, "/");
    s.tm_min = atoi(token);
    token = strtok(NULL, "/");
    s.tm_sec = atoi(token);
    // token = strtok(NULL, "/");
    s.tm_isdst =0;

    t = mktime(&s);
    if(t==-1){
        perror("mktime: ");
        return;
    }
    else{
        printf("%s", ctime(&t));
    }

}


int main(int argc, char const *argv[])

{
    char str[1024] = "";

    for (int k = 1; k < argc; k++)
    {
        strcat(str, " ");
        strcat(str, argv[k]);
        
    }
    


    char *token =strtok(str, " ");
    token = strtok(NULL, " ");
    if(token!=NULL){
        if(token[0]=='-'&& token[1]=='r'){
            dater();

        }
        else if(token[0]=='-'&& token[1]=='u'){
            token = strtok(NULL, " ");
            if(strlen(token)<19 || strlen(token)>19){
                printf("Write in proper format DD/MM/YYYY/HH/MM/SS: ");
                return 1;
            }
            else{
                // printf("%s", token);
                dateu(token);

            }
        }
        else{
            printf("Error in command");
        }
    }
    else{
        date();
    }
    return 0;
}


