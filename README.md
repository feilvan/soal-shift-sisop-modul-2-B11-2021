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
Karena nantinya di 1.e. diminta agar program bisa menjalankan task pada waktu tertentu, maka disini saya buat fork. Child akan menjalankan 1.a sampai 1.d dan parent akan menjalankan 1.f.
```c
        chdir("/home/xa/modul2/soal1/");
        pid_t child_id;
        int status;
        if (time(NULL) == 1617960120){ // untuk 1.e. akan dijelaskan di penjelasan nomor tersebut
            child_id = fork();
        }
        if (child_id < 0){
            exit(EXIT_FAILURE);
        }
        if (child_id == 0){
            satuA();
        }
        else if (time(NULL) == 1617981720){ // untuk 1.f. akan dijelaskan di penjelasan nomor tersebut
            while ((wait(&status)) > 0);
            satuF();
        }
```
Di satuA saya fork lalu child processnya membuat folder, sedangkan parent processnya lanjut ke tahap selanjutnya
```c
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
```

Membuat folder
```c
char *argv[] = {"mkdir", "Musyik", "Pyoto", "Fylm", NULL};
execv("/bin/mkdir", argv);
```

![a](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots/Screenshot%20from%202021-04-22%2015-27-17.png)

soal1 akan berjalan pada background

![a](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots/Screenshot%20from%202021-04-22%2015-27-40.png)

Di parent process dilakukan fork dua kali agar bisa menjalankan tiga process. Tiap process ini akan melakukan satuBCD dimana disini akan download, ekstrak, dan memindahkan file (soal b, c, dan d)

#### 1.b,c,d. Download zip untuk film, musik, dan foto dari link yang tersedia; lalu ekstrak zip yang telah didownload; kemudian pindahkan ke folder yang telah dibuat di 1.a
B, C, dan D saya gabung jadi satu process karena berdasarkan preview yang ada pada soal setelah zip terdownload langsung diekstrak dan dipindah sebelum download zip selanjutnya. Jika B, C, dan D dipisah maka program akan mendownload semua zip terlebih dahulu, lalu mengekstrak semuanya, dan memindahkannya ke folder. Langkah ini tidak seperti yang ada pada preview.
<p>Fungsi satuBCD akan mendownload, ekstrak, lalu memindahkan file ke folder yang telah dibuat di 1.a. Disini saya bagi menjadi tiga kondisi untuk memisahkan antara file film, foto, dan musik.</p>
<p>Untuk nama file dan url disimpan di char agar pada penulisan argument tidak terlalu panjang</p>

```c
    char fileMusik[] = {"Musik_for_Stevany.zip"};
    char fileFilm[] = {"Film_for_Stevany.zip"};
    char fileFoto[] = {"Foto_for_Stevany.zip"};
    char urlMusik[] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"};
    char urlFilm[] = {"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
    char urlFoto[] = {"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
```
<p>Agar download, ekstrak, dan pemindahan berjalan berurutan, dibuat fork lalu pada childnya dikukan fork lagi sehingga ada tiga process (untuk download, ekstrak, dan pindah), kemudian diberi wait pada parent2nya.</p>

```c
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
```
<p>Download</p>

```c
char *argv[] = {"wget", "-q", "-nc", "--no-check-certificate", urlFilm, "-O", fileFilm, NULL};
execv("/usr/bin/wget", argv);
```
<p>Extract</p>

```c
char *argv[] = {"unzip", fileFilm, NULL};
execv("/usr/bin/unzip", argv);
```
<p>Pindah (dengan find format file lalu pindahkan ke folder tujuan)</p>

```c
char *argv[] = {"find", ".", "-name", "*.mp4", "-exec", "mv", "{}", "/home/xa/modul2/soal1/Fylm/", ";", NULL};
execv("/usr/bin/find", argv);
```
<p>Ulangi process yang sama untuk foto dan musik. Namun untuk foto perlu ada penyesuaian pada saat memindahkan file karena ternyata ada tiga format foto. Jadi perlu dilakukan find tiga kali untuk setiap format foto.</p>

#### 1.e. Jalankan 1.a - 1.d secara otomatis 6 jam sebelum ulang tahun Stevany
Pada penjelasan 1.a terdapat code dibawah ini
```c
        if (time(NULL) == 1617960120){
            child_id = fork();
        }
```
Jika waktu telah masuk 6 jam sebelum ulang tahun maka akan dilakukan fork. 1617960120 adalah unix epoch time untuk 9 April 2021 16.22. Jadi program belum melakukan fork sebelum waktu tersebut. Tepat pada waktu tersebut program akan melakukan fork lalu pada child process dilakukan fungsi satuA (untuk mengerjakan 1.a sampai 1.d).

![bcde](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots/Screenshot%20from%202021-04-09%2016-22-47.png)

#### 1.f. Pada waktu ulang tahun folder akan dizip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete (sehingga hanya menyisakan .zip)
Pada parent process hasil dari fork sebelumnya, dilakukan hal yang sama seperti 1.e. Program akan menunggu sampai waktu ulang tahun untuk menjalankan langkah selanjutnya
```c
        else if (time(NULL) == 1617981720){
            while ((wait(&status)) > 0);
            satuF();
        }
```
Pada satuF dilakukan fork lalu pada child processnya melakukan zip, sedangkan pada parent processnya melakukan penghapusan folder
<p>Zip</p>

```c
char *argv[] = {"zip", "-r", "Lopyu_Stevany", "Fylm/", "Musyik/", "Pyoto/", NULL};
execv("/usr/bin/zip", argv);
```
<p>Hapus folder</p>

```c
char *argv[] = {"rm", "-r", "FILM", "MUSIK", "FOTO", "Fylm", "Musyik", "Pyoto", NULL};
execv("/usr/bin/rm", argv);
```

![f](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots/Screenshot%20from%202021-04-09%2022-22-17.png)

## Soal 2

## Soal 3
