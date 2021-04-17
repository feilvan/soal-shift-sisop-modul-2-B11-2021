#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

int main()
{
    char path[100];

        id_t child_id;
        int status=0;

        child_id = fork();

        if (child_id < 0) {
            exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
        }

        if (child_id == 0) {
            // this is child
            char *argv[] = {"unzip", "pets.zip", "*.jpg", "-d", "petshop", NULL};
            execv("/bin/unzip", argv);
        } else {
        // this is parent
            while(wait(&status) > 0);
            listFilesRecursively("petshop");
        }
    return 0;
}

void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token, *str, hewan[1000];
    
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            str = dp->d_name;
            token = strtok(str, ";_");
            int i=0;
            if(token != NULL){
                if(i==0||i==3){
                    if(fork() == 0){
                        snprintf(hewan, sizeof hewan, "petshop/%s", token);
                        char *argv[] = {"mkdir", "-p", hewan, NULL};
                        execv("/bin/mkdir", argv);
                    }     
                }
                token = strtok(NULL, ";_");
                i++;
            }
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);  
            }
        }
       closedir(dir);
    }
