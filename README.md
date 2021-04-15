# soal-shift-sisop-modul-2-B11-2021

Anggota kelompok :
* 05111940000181 - Cliffton Delias Perangin Angin
* 05111940000095 - Fuad Elhasan Irfani
* 05111940000107 - Sabrina Lydia Simanjuntak

## Soal 1
#### 1. Sebelum ke 1a buat daemon dahulu agar program berjalan di background
Untuk pembuatan daemon sama seperti di materi modul2
```c
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
        // program utama nantinya ditulis disini
        sleep(1);
    }
}
```

#### 1.a. Buat folder "Musyik" untuk mp3, "Fylm" untuk mp4, dan "Pyoto" untuk jpg.
Karena nantinya di 1.e. diminta agar program bisa menjalankan task pada waktu tertentu, maka disini saya buat fork. Child akan menjalankan 1.a dan parent akan menjalankan 1.f.
```c
        chdir("/home/xa/modul2/soal1/");
        pid_t child_id;
        int status;
        if (time(NULL) == 1617960120) // untuk 1.e. akan dijelaskan di penjelasan nomor tersebut
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
        else if (time(NULL) == 1617981720) // untuk 1.f. akan dijelaskan di penjelasan nomor tersebut
        {
            while ((wait(&status)) > 0);
            satuF();
        }
```
Untuk membuat tiga folder tersebut saya melakukan fork, lalu pada child proccessnya di-fork lagi, dan pada child proccessnya juga di-fork lagi (total tiga kali fork). Dengan ini saya bisa melakukan empat proccess: tiga untuk membuat folder, dan satu untuk lanjut ke step berikutnya
```c
int satuA ()
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
        satuAB(); // lanjut ke step berikutnya
    }
}
```
Membuat folder bisa menggunakan exec mkdir. Jalankan di semua proccess kecuali parent proccess yang pertama.
```c
char *argv[] = {"mkdir", "Fylm", NULL};
execv("/bin/mkdir", argv);
```

#### 1.b,c,d. Download zip untuk film, musik, dan foto dari link yang tersedia; lalu ekstrak zip yang telah didownload; kemudian pindahkan ke folder yang telah dibuat di 1.a
B, C, dan D saya gabung jadi satu proccess karena berdasarkan preview yang ada pada soal setelah zip terdownload langsung diekstrak dan dipindah sebelum download zip selanjutnya. Jika B, C, dan D dipisah maka program akan mendownload semua zip terlebih dahulu, lalu mengekstrak semuanya, dan memindahkannya ke folder. Langkah ini tidak seperti yang ada pada preview.
<p>
Pada fungsi satuAB saya lakukan fork dua kali sehingga menghasilkan tiga proccess. Tiga proccess ini nantinya akan melakukan download, ekstrak, dan pindah secara berurut.</p>

```c
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
```
satuBCD akan mendownload, ekstrak, lalu memindahkan file ke folder yang telah dibuat di 1.a. Disini saya bagi menjadi tiga kondisi untuk memisahkan dalam memproses file film, foto, dan musik.
