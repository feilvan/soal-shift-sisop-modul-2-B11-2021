#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>

int satuA();
int satuBCD(int a);
int moveFoto();
int satuF();

int main ()
{
    pid_t pid, sid;
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    umask(0);
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
        chdir("/home/xa/modul2/soal1/");
        pid_t child_id;
        int status;
        if (time(NULL) == 1617960120){
            child_id = fork();
        }
        if (child_id < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id == 0){
            satuA();
        }
        else if (time(NULL) == 1617981720){
            while ((wait(&status)) > 0);
            satuF();
        }
        sleep(1);
    }
}

int satuA (){
    pid_t child_id;
    child_id = fork();
    if (child_id < 0){
        exit(EXIT_FAILURE);
    }
    if (child_id == 0){
        char *argv[] = {"mkdir", "Musyik", "Pyoto", "Fylm", NULL};
        execv("/bin/mkdir", argv);
    }
    else{
        pid_t child_id_2;
        int status_2;
        child_id_2 = fork();
        if (child_id_2 < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id_2 == 0){
            pid_t child_id_3;
            int status_3;
            child_id_3 = fork();
            if (child_id_3 < 0){
                exit(EXIT_FAILURE);
            }
            if (child_id_3 == 0){
                satuBCD(0);
            }
            else{
                while ((wait(&status_3)) > 0);
                satuBCD(1);
            }
        }
        else{
            while ((wait(&status_2)) > 0);
            satuBCD(2);
        }
    }
}

int satuBCD (int a)
{
    char fileMusik[] = {"Musik_for_Stevany.zip"};
    char fileFilm[] = {"Film_for_Stevany.zip"};
    char fileFoto[] = {"Foto_for_Stevany.zip"};
    char urlMusik[] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"};
    char urlFilm[] = {"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
    char urlFoto[] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};

    pid_t child_id;
    int status;
    child_id = fork();
    if (a == 0){
        if (child_id < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id == 0){
            pid_t child_id_2;
            int status_2;
            child_id_2 = fork();
            if (child_id_2 < 0){
                exit(EXIT_FAILURE);
            }
            if (child_id_2 == 0){
                char *argv[] = {"wget", "-q", "-nc", "--no-check-certificate", urlFilm, "-O", fileFilm, NULL};
                execv("/usr/bin/wget", argv);
            }
            else{
                while ((wait(&status_2)) > 0);
                char *argv[] = {"unzip", fileFilm, NULL};
                execv("/usr/bin/unzip", argv);
            }
        }
        else{
            while ((wait(&status)) > 0);
            char *argv[] = {"find", ".", "-name", "*.mp4", "-exec", "mv", "{}", "/home/xa/modul2/soal1/Fylm/", ";", NULL};
            execv("/usr/bin/find", argv);
        }
    }

    if (a == 1){
        if (child_id < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id == 0){
            pid_t child_id_2;
            int status_2;
            child_id_2 = fork();
            if (child_id_2 < 0){
                exit(EXIT_FAILURE);
            }
            if (child_id_2 == 0){
                char *argv[] = {"wget", "-q", "-nc", "--no-check-certificate", urlFoto, "-O", fileFoto, NULL};
                execv("/usr/bin/wget", argv);
            }
            else{
                while ((wait(&status_2)) > 0);
                char *argv[] = {"unzip", fileFoto, NULL};
                execv("/usr/bin/unzip", argv);
            }
        }
        else{
            while ((wait(&status)) > 0);
            moveFoto();
        }
    }

    if (a == 2){
        if (child_id < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id == 0)
        {
            pid_t child_id_2;
            int status_2;
            child_id_2 = fork();
            if (child_id_2 < 0){
                exit(EXIT_FAILURE);
            }
            if (child_id_2 == 0)
            {
                char *argv[] = {"wget", "-q", "-nc", "--no-check-certificate", urlMusik, "-O", fileMusik, NULL};
                execv("/usr/bin/wget", argv);
            }
            else{
                while ((wait(&status_2)) > 0);
                char *argv[] = {"unzip", fileMusik, NULL};
                execv("/usr/bin/unzip", argv);
            }
        }
        else{
            while ((wait(&status)) > 0);
            char *argv[] = {"find", ".", "-name", "*.mp3", "-exec", "mv", "{}", "/home/xa/modul2/soal1/Musyik/", ";", NULL};
            execv("/usr/bin/find", argv);
        }
    }
}

int moveFoto ()
{
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id < 0){
        exit(EXIT_FAILURE);
    }
    if (child_id == 0){
        pid_t child_id_2;
        int status_2;
        child_id_2 = fork();
        if (child_id_2 < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id_2 == 0){
            char *argv[] = {"find", ".", "-name", "*.jpg", "-exec", "mv", "{}", "/home/xa/modul2/soal1/Pyoto/", ";", NULL};
            execv("/usr/bin/find", argv);
        }
        else{
            char *argv[] = {"find", ".", "-name", "*.jpeg", "-exec", "mv", "{}", "/home/xa/modul2/soal1/Pyoto/", ";", NULL};
            execv("/usr/bin/find", argv);
        }
    }
    else{
        char *argv[] = {"find", ".", "-name", "*.png", "-exec", "mv", "{}", "/home/xa/modul2/soal1/Pyoto/", ";", NULL};
        execv("/usr/bin/find", argv);
    }
}

int satuF ()
{
    pid_t child_id;
    int status;
    child_id = fork();
    if (child_id < 0){
        exit(EXIT_FAILURE);
    }
    if (child_id == 0){
        char *argv[] = {"zip", "-r", "Lopyu_Stevany", "Fylm/", "Musyik/", "Pyoto/", NULL};
        execv("/usr/bin/zip", argv);
    }
    else{
        while ((wait(&status)) > 0);
        char *argv[] = {"rm", "-r", "FILM", "MUSIK", "FOTO", "Fylm", "Musyik", "Pyoto", NULL};
        execv("/usr/bin/rm", argv);
    }
}
