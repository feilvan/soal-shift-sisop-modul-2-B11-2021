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
int satuAB();
int satuBCD(int a);
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
        if (time(NULL) == 1617960120)
        {
            child_id = fork();
        }

        if (child_id < 0)
        {
            exit(EXIT_FAILURE);
        }

        if (child_id == 0)
        {
            satuA();
        }
        else if (time(NULL) == 1617981720)
        {
            while ((wait(&status)) > 0);
            satuF();
        }
        sleep(1);
    }
}

int satuA ()
{
    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id < 0)
    {
        exit(EXIT_FAILURE);
    }

    // 1.a. Buat folder
    if (child_id == 0)
    {
        pid_t child_id_2;
        child_id_2 = fork();
        if (child_id_2 == 0)
        {
            pid_t child_id_3;
            child_id_3 = fork();
            if (child_id_3 == 0)
            {
                char *argv[] = {"mkdir", "Fylm", NULL};
                execv("/bin/mkdir", argv);
            }
            else
            {
                char *argv[] = {"mkdir", "Musyik", NULL};
                execv("/bin/mkdir", argv);
            }
        }
        else
        {
            char *argv[] = {"mkdir", "Pyoto", NULL};
            execv("/bin/mkdir", argv);
        }
    }
    else
    {
        while ((wait(&status)) > 0);
        satuAB();
    }
}

int satuAB ()
{
    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (child_id == 0)
    {
        pid_t child_id_2;
        int status_2;
        child_id_2 = fork();
        if (child_id_2 == 0)
        {
            satuBCD(2);
        }
        else
        {
            while ((wait(&status_2)) > 0);
            satuBCD(1);
        }
    }
    else
    {
        while ((wait(&status)) > 0);
        satuBCD(0);
    }
}

int satuBCD (int a)
{
    char fileMusik[] = {"Musik_for_Stevany.zip"};
    char fileFilm[] = {"Film_for_Stevany.zip"};
    char fileFoto[] = {"Foto_for_Stevany.zip"};
    char urlMusik[] = {"https://github.com/feilvan/sisop-general/raw/main/modul2/stevany/Musik_for_Stevany.zip"};
    char urlFilm[] = {"https://github.com/feilvan/sisop-general/raw/main/modul2/stevany/Film_for_Stevany.zip"};
    char urlFoto[] = {"https://github.com/feilvan/sisop-general/raw/main/modul2/stevany/Foto_for_Stevany.zip"};

    pid_t child_id;
    int status;
    child_id = fork();

    if (a == 0)
    {
        if (child_id < 0)
        {
            exit(EXIT_FAILURE);
        }

        if (child_id == 0)
        {
            pid_t child_id_2;
            int status_2;
            child_id_2 = fork();
            if (child_id_2 == 0)
            {
                char *argv[] = {"wget", "-q", "-nc", "--no-check-certificate", urlFilm, "-O", fileFilm, NULL};
                execv("/usr/bin/wget", argv);
            }
            else
            {
                while ((wait(&status_2)) > 0);
                char *argv[] = {"unzip", fileFilm, NULL};
                execv("/usr/bin/unzip", argv);
            }
        }
        else
        {
            while ((wait(&status)) > 0);
            // char *argv[] = {"mv", "FILM/*", "Fylm",  NULL};
            // execv("/usr/bin/mv", argv);
            char *argv[] = {"cp", "-R", "FILM/.", "Fylm",  NULL};
            execv("/usr/bin/cp", argv);
        }
    }

    if (a == 1)
    {
        if (child_id < 0)
        {
            exit(EXIT_FAILURE);
        }

        if (child_id == 0)
        {
            pid_t child_id_2;
            int status_2;
            child_id_2 = fork();
            if (child_id_2 == 0)
            {
                char *argv[] = {"wget", "-q", "-nc", "--no-check-certificate", urlFoto, "-O", fileFoto, NULL};
                execv("/usr/bin/wget", argv);
            }
            else
            {
                while ((wait(&status_2)) > 0);
                char *argv[] = {"unzip", fileFoto, NULL};
                execv("/usr/bin/unzip", argv);
            }
        }
        else
        {
            while ((wait(&status)) > 0);
            // char *argv[] = {"mv", "FOTO/*", "Pyoto",  NULL};
            // execv("/usr/bin/mv", argv);
            char *argv[] = {"cp", "-R", "FOTO/.", "Pyoto",  NULL};
            execv("/usr/bin/cp", argv);
        }
    }

    if (a == 2)
    {
        if (child_id < 0)
        {
            exit(EXIT_FAILURE);
        }

        if (child_id == 0)
        {
            pid_t child_id_2;
            int status_2;
            child_id_2 = fork();
            if (child_id_2 == 0)
            {
                char *argv[] = {"wget", "-q", "-nc", "--no-check-certificate", urlMusik, "-O", fileMusik, NULL};
                execv("/usr/bin/wget", argv);
            }
            else
            {
                while ((wait(&status_2)) > 0);
                char *argv[] = {"unzip", fileMusik, NULL};
                execv("/usr/bin/unzip", argv);
            }
        }
        else
        {
            while ((wait(&status)) > 0);
            // char *argv[] = {"mv", "MUSIK/*", "Musyik",  NULL};
            // execv("/usr/bin/mv", argv);
            char *argv[] = {"cp", "-R", "MUSIK/.", "Musyik",  NULL};
            execv("/usr/bin/cp", argv);
        }
    }
}

int satuF ()
{
    pid_t child_id;
    int status;
    child_id = fork();

    if (child_id < 0)
    {
        exit(EXIT_FAILURE);
    }

    if (child_id == 0)
    {
        char *argv[] = {"zip", "-r", "Lopyu_Stevany", "Fylm/", "Musyik/", "Pyoto/", NULL};
        execv("/usr/bin/zip", argv);
    }
    else
    {
        while ((wait(&status)) > 0);
        char *argv[] = {"rm", "-r", "FILM", "MUSIK", "FOTO", "Fylm", "Musyik", "Pyoto", NULL};
        execv("/usr/bin/rm", argv);
    }
}
