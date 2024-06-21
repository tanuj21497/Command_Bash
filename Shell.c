#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <pwd.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>


char cmds[8][20] = {"cd", "echo", "pwd", "ls", "cat", "date", "rm", "mkdir"};


void cdM(char **inst_arr){
    // printf("%s", inst_arr[2]);
    if(inst_arr[2]!=NULL){
        char buff_arr[PATH_MAX];
        char *new_dir_name = strtok(inst_arr[2], "\n"); 
        char *rl_pth = realpath(new_dir_name, buff_arr);
        if(rl_pth!= NULL){
            if(!chdir(rl_pth)){
                printf("Absolute name of working directory is: %s", buff_arr);
                char cdM_arr[300];
                char *arr = getcwd(cdM_arr, sizeof(cdM_arr));


            }
            else{
                perror("Error in directory name or command: ");
            }

        }
        else{
            perror("Real Path Error");
        }

    }
    else{

        printf("As no directory given, propagating to home directory ");
        chdir(getenv("HOME"));
        char cdM_arr[300];
        char *arr = getcwd(cdM_arr, sizeof(cdM_arr));
        printf("%s", cdM_arr);

        
    }
}


void cdN(char **inst_arr){
    if(inst_arr[2]!=NULL){
        char buff_arr[PATH_MAX];
        char name_pth[200];
        strcpy(name_pth, inst_arr[2]);
        char *new_dir_name = strtok(name_pth, "\n"); 
        // int *rl_pth = realpath(new_dir_name, buff_arr);
        if(!chdir(new_dir_name)){
            char cdM_arr[300];
            char *arr = getcwd(cdM_arr, sizeof(cdM_arr));
            printf("%s", arr);
        }
        else{
            perror("Error in directory name or command: ");
        }

    }
    else{
        printf("As no directory given, propagating to home directory ");
        chdir(getenv("HOME"));
        char cdM_arr[300];
        char *arr = getcwd(cdM_arr, sizeof(cdM_arr));
        printf("%s", cdM_arr);

        
    }
}

void cd(char **inst_arr){
    if(inst_arr[1]!=NULL){
        if(strcmp(inst_arr[1], "-M")==0){
            cdM(inst_arr);

        }
        else if(strcmp(inst_arr[1], "-N")==0){
            cdN(inst_arr);
        }
        else if(strcmp(inst_arr[1], "--help")==0){
            printf("This function is for chanding directory");
        }
        else if(strcmp(inst_arr[1], "-")==0){
            if(chdir("..")==0){
                char cd_arr[300];
                char *arr = getcwd(cd_arr, sizeof(cd_arr));
                printf("%s", cd_arr);

            }
            else{
                perror("Please write the right command ..");
            }
        }
        else{
            char name_pth[200];
            strcpy(name_pth, inst_arr[1]);
            char *new_dir_name = strtok(name_pth, "\n"); 
            if(chdir(new_dir_name)==0){
                char cd_arr[300];
                char *arr = getcwd(cd_arr, sizeof(cd_arr));
                printf("%s", cd_arr);


            }
            else{
                perror("Please write the right command directory");

            }

        }



    }
    else{
    printf("As no directory given, propagating to home directory ");
    chdir(getenv("HOME"));
    char cdM_arr[300];
    char *arr = getcwd(cdM_arr, sizeof(cdM_arr));
    printf("%s", cdM_arr);

    }
}


void echo(char **inst_arr, char *storage){
    if(strcmp(inst_arr[1],"-e")==0 && storage!=NULL){
        // printf("yrd\n");
        char c = '\c';
        char nu = '\w';
        int i=0;
        int flag =0;
        char d[100] = "";
        char e[100]= "";
        int j =0;
        while(storage[i] != '\0'){
            // printf("%c ", storage[i]);
            if(storage[i]== nu){
                // strcat(d[i], '\n');
                e[j] = '\n';
                j++;
                // printf("yes\n");
            }
            else{
                if(storage[i]!='\\'){
                    e[j] = storage[i];
                    j++;
                }

            }
            i++;
        }
        i=0;
        while(e[i] != '\0'){
            if(e[i]==c){
                flag=1;
                break;
            }

            d[i] = e[i];
            i++;


        }
        if(flag ==1){
            printf("%s", d);

        }
        else{
            printf("%s", e);

        }
    }
    else if(storage!=NULL){
        int i =0;
        printf("%s", storage);
        
    }
    else{
        chdir(getenv("HOME"));
        char cdM_arr[300];
        char *arr = getcwd(cdM_arr, sizeof(cdM_arr));
        printf("%s", cdM_arr);

    }
}
void pwdM(){
    char pwdM_arr[200];
    char *curr_wrk_dir = getcwd(pwdM_arr, sizeof(pwdM_arr));
    printf("%s", curr_wrk_dir);

}
void pwdN(){
    char buffer_array[PATH_MAX];
    char pwdM_arr[200];
    char *curr_wrk_dir = getcwd(pwdM_arr, sizeof(pwdM_arr));

    char *res = realpath(curr_wrk_dir, buffer_array);
    printf("%s", res);

}
void pwd(char **inst_arr){

    char name_pth[200];
    char pwd_arr[200];

    char *curr_wrk_dir = getcwd(pwd_arr, sizeof(pwd_arr));
    if(curr_wrk_dir==NULL){
        perror("cwd error in pwd: ");
        return;

    }

    if(inst_arr[1]!=NULL){
        strcpy(name_pth, inst_arr[1]);
        if(strcmp(inst_arr[1], "-M")==0){
            pwdM();
        }
        else if(strcmp(inst_arr[1], "-N")==0){
            pwdN();
        }
        else if(strcmp(inst_arr[1], "--help")==0){
            printf("This command is used to print current working directory");

        }

        

    }
    else{
        // printf("please give some directory for pwd command");
        printf("%s", curr_wrk_dir);

    }


}

// char *cmd_wo_at = malloc(500*sizeof(char)); 
// char cmd_wo_at1[500] = ""; 
char cmd_wo_at[100]= "";
char cmd_wo_at1[100] ="";
// int i =0 ;

void freett(char *arr){
    for (int i = 0; i < 100; i++)
    {
        arr[i]='\0';
    }
    

}

void *system_call(void *argv){

    // cmd_wo_at[500] = ""; 
    // cmd_wo_at1[500] = ""; 
    // printf("%s........system call wala\n", cmd_wo_at);
    if(system(cmd_wo_at) == -1){
        printf("System function failure");
        pthread_exit(0);
        return NULL;
    }

    // printf(:)
    pthread_exit(0);
    return NULL;
}

void thread_maker(char *terminal_command, char *adder){
    int i=0;
    while (terminal_command[i]!= '\0')
    {
        cmd_wo_at1[i] = terminal_command[i+3];
        i++;
    }

    strcat(cmd_wo_at, adder);
    strcat(cmd_wo_at, cmd_wo_at1);
    
    pthread_t new_thread;
    pthread_create(&new_thread, NULL, system_call, NULL);

    pthread_join(new_thread, NULL);
    freett(cmd_wo_at1);
    freett(cmd_wo_at);

}


int main(){

    // char *cmd_wo_at = malloc(1024*sizeof(char)); 
    // char *cmd_wo_at1 =malloc(1024*sizeof(char));   
    // i=0;
    while(1==1){
        printf("$ ");
        char crnt_cmd[1024];


        char **crnt_cmd_arr = (char **)malloc(200*sizeof(char *));
        int n= scanf("%[^\n]%*c", crnt_cmd);
        char crnt_cmd_cpy[1024];
        strcpy(crnt_cmd_cpy, crnt_cmd);



        if(n!=0){
            char *token = strtok(crnt_cmd_cpy, " ");
            int size =0;
            int th_flag =0;
            if(strcmp(token, "&t")==0){
                th_flag=1;
                    // continue;
                token = strtok(NULL, " ");
            }
            // printf("%s", token);
            // printf("%d", th_flag);
            while(token !=NULL){
                
                crnt_cmd_arr[size] = (char*)malloc(200*sizeof(char));
                strcpy(crnt_cmd_arr[size], token);
                token = strtok(NULL, " ");
                size++;
            }  
            int cmd_index = -1;
            for (int i = 0; i < 8; i++)
            {
                if(strcmp(crnt_cmd_arr[0], cmds[i])==0){
                    cmd_index = i;
                    break;

                }

            }
            // printf("%d", cmd_index);
            // if(cmd_index==9){

            // }
            if(cmd_index==0){
                cd(crnt_cmd_arr);
            }
            else if(cmd_index==1){
                char storage[1024]= "";

                if(crnt_cmd_arr[1]!=NULL && strcmp(crnt_cmd_arr[1], "-e")==0){
                    int i =2;
                    // strcat(storage, crnt_cmd_arr[2]);
                    while(i<size){
                        strcat(storage, crnt_cmd_arr[i]);
                        if(i!=size-1){
                            strcat(storage, " ");
                        }
                        i++;
                    }
                }
                else if(crnt_cmd_arr[1]!=NULL){
                    int i =1;
                    // strcat(storage, crnt_cmd_arr[2]);
                    while(i<size){
                    strcat(storage, crnt_cmd_arr[i]);

                        if(i!=size-1){
                            strcat(storage, " ");
                        }
                        
                        i++;
                    }


                }
                
                echo(crnt_cmd_arr, storage);
            }
            else if(cmd_index==2){
                pwd(crnt_cmd_arr);
            }

            else if(cmd_index==3 && th_flag==0){
                // printf("yes");
                pid_t id;
                int proces;
                if ((id = fork()) == 0)
                {
                    execl("./ls", "./ls", crnt_cmd, NULL);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&proces);
                }

            }
            else if(cmd_index==4 && th_flag==0){
                pid_t id;
                int proces;
                if ((id = fork()) == 0)
                {
                    execl("./cat", "./cat", crnt_cmd, NULL);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&proces);
                }

            }
            else if(cmd_index==5 &&th_flag==0){
                pid_t id;
                int proces;
                if ((id = fork()) == 0)
                {
                    execl("./date", "./date", crnt_cmd, NULL);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&proces);
                }

            }
            else if(cmd_index==6 && th_flag==0){
                pid_t id;
                int proces;
                if ((id = fork()) == 0)
                {
                    execl("./rm", "./rm", crnt_cmd, NULL);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&proces);
                }

            }
            else if(cmd_index==7 && th_flag==0){
                pid_t id;
                int proces;
                if ((id = fork()) == 0)
                {
                    execl("./mkdir", "./mkdir", crnt_cmd, NULL);
                    exit(0);
                }
                else
                {
                    pid_t time;
                    time = wait(&proces);
                }

            }
            else if(th_flag==1){
                int cmd_index1 = -1;
                for (int i = 0; i < 8; i++)
                {
                    if(strcmp(crnt_cmd_arr[0], cmds[i])==0){
                        cmd_index1 = i;
                        break;

                    }

                }
                if(cmd_index1==3){
                    // printf("yes");
                    
                    thread_maker(crnt_cmd, "./ls ");

                }
                else if(cmd_index1==4){
                    thread_maker(crnt_cmd, "./cat ");


                }
                else if(cmd_index1==5){
                    thread_maker(crnt_cmd, "./date ");

                    
                }
                else if(cmd_index1==6){
                    thread_maker(crnt_cmd, "./rm ");

                    
                }
                else if(cmd_index1==7){
                    thread_maker(crnt_cmd, "./mkdir ");

                    
                }
                else{
                    printf("Wrong command for threads");
                }
            


            }
            else{
                printf("Command name not found");
            }
            
              
            

        }
        else{
            printf("Please run again, and assign input, there occurs a problem");
        }



    }
}








