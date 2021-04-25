# soal-shift-sisop-modul-2-B11-2021

Anggota kelompok :
* 05111940000181 - Cliffton Delias Perangin Angin
* 05111940000095 - Fuad Elhasan Irfani
* 05111940000107 - Sabrina Lydia Simanjuntak

## Soal 1
#### Sebelum ke 1a buat daemon dahulu agar program berjalan di background
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

### 1.a
#### Buat folder "Musyik" untuk mp3, "Fylm" untuk mp4, dan "Pyoto" untuk jpg.
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

### 1.b,c,d. 
#### Download zip untuk film, musik, dan foto dari link yang tersedia; lalu ekstrak zip yang telah didownload; kemudian pindahkan ke folder yang telah dibuat di 1.a
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

### 1.e.
#### Jalankan 1.a - 1.d secara otomatis 6 jam sebelum ulang tahun Stevany
Pada penjelasan 1.a terdapat code dibawah ini
```c
        if (time(NULL) == 1617960120){
            child_id = fork();
        }
```
Jika waktu telah masuk 6 jam sebelum ulang tahun maka akan dilakukan fork. 1617960120 adalah unix epoch time untuk 9 April 2021 16.22. Jadi program belum melakukan fork sebelum waktu tersebut. Tepat pada waktu tersebut program akan melakukan fork lalu pada child process dilakukan fungsi satuA (untuk mengerjakan 1.a sampai 1.d).

![bcde](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots/Screenshot%20from%202021-04-09%2016-22-47.png)

### 1.f.
#### Pada waktu ulang tahun folder akan dizip dengan nama Lopyu_Stevany.zip dan semua folder akan di delete (sehingga hanya menyisakan .zip)
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

Kendala soal 1:
- Pemindahan semua file didalam folder hasil ekstrak tidak bisa menggunakan exec mv dengan source misalkan ```FILM/*```. Solusinya saya menggunakan find lalu mv untuk memindahkan file dengan ekstensi tertentu.

## Soal 2
Pada soal nomor 2 kita diminta untuk men-download file bernama `pets.zip`. Untuk memproses file ini, kami menggunakan fork, exec, dan wait.

### 2a
Pada soal 2a, kita diminta untuk mengekstrak file `pets.zip` ke folder `/home/[user]/modul2/petshop` dan hanya memproses file-file yang diperlukan saja

```c
        if (child_id == 0) {
            char *argv[] = {"unzip", "pets.zip", "*.jpg", "-d", "petshop", NULL};
            execv("/bin/unzip", argv);
        } 
```
Jadi di sini dilakukan exec untuk melakukan unzip file `pets.zip`, lalu `*.jpg` digunakan untuk memproses file yang berformat jpg saja (file penting). `-d` digunakan untuk mengekstrak file tersebut di folder yang bernama `petshop`

### 2b
Pada soal 2b, kita diminta untuk membuat folder sesuai dengan setiap jenis peliharaan yang ada di file zip.
```c
	else {
            while(wait(&status) > 0);
            listFilesRecursively("petshop");
        }
```
Di sini kami memanggil fungsi yang bernama `listFilesRecursively` dengan input berupa nama folder tempat file-file tadi di ekstrak yaitu `petshop`
```c
void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    char *token;

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char nama[1000];
            char *str;
            str = dp->d_name;
            
            snprintf(nama, sizeof nama, "%s", dp->d_name);
            token  = strtok(nama, ";_");

            
            char *info[2][3];
            int banyak=0;
            while(token != NULL){
                int data = 0;
                while(data<3){
                    info[banyak][data] = token;
                    token = strtok(NULL, ";_");
                    data++;
                }
                banyak++;
            }
            char *usia;
            for (int i = 0; i < banyak; i++) {
                createFolder(info[i][0]);
                copyFiles(info[i][0], info[i][1], str);
                createKeterangan(info[i][0], info[i][1], info[i][2]);
            }
            deleteFiles(str);
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}
```
Fungsi ini merupakan template yang ada di modul 2 yang kami modifikasi. Di sini, kami menggunakan `strtok` untuk membagi nama file menjadi beberapa bagian, untuk mengambil data yang sesuai dengan yang dibutuhkan untuk proses selanjutnya. Lalu, data-data tersebut akan dimasukkan ke two dimensional array untuk memudahkan pemisahan data dari file yang berisi dua hewan di dalamnya, yaitu `info[0][data]` untuk hewan pertama dan `info[1][data]` untuk hewan kedua. Lalu disini dipanggilah fungsi `createFolder`
```c
void createFolder(char *nameFolder){
    int status = 0;
    if(fork()==0){
        char buf1[256];
        snprintf(buf1, sizeof buf1, "petshop/%s", nameFolder);
        char *argv[] = {"mkdir", "-p", buf1, NULL};
        execv("/bin/mkdir", argv);
    }
    while(wait(&status)>0);
}
```
Fungsi ini merupakan fungsi untuk membuat folder-foldernya. Di sini dilakukan `sprintf`untuk melakukan printf nama folder dan lokasinya ke `buf1`, lalu di exec untuk membuat foldernya.

###2c dan 2d
Pada soal 2c dan 2d kita diminta untuk memidahkan file-file di `petshop` ke folder sesuai jenis hewan masing-masing, lalu mengganti nama filenya sesuai dengan nama perliharaannya. Namun pada soal nomor 2d, file yang berisikan lebih dari satu hewan, dipindahkan ke folder-folder sesuai dengan hewan-hewan yang ada di dalam file tersebut.
```c
 char *info[2][3];
            int banyak=0;
            while(token != NULL){
                int data = 0;
                while(data<3){
                    info[banyak][data] = token;
                    token = strtok(NULL, ";_");
                    data++;
                }
                banyak++;
            }
```
Untuk nomor 2d kita kembali ke fungsi `listFilesRecursively` bagian ini, sepeti yang telah dijelaskan di nomor 2a. Dimana, data-data yang telah menjadi token-token akan dimasukkan ke two dimensional array untuk memudahkan pemisahan data dari file yang berisi dua hewan di dalamnya, yaitu `info[0][data]` untuk hewan pertama dan `info[1][data]` untuk hewan kedua.

```c
void copyFiles(char *namaFolder, char *nama, char *namaFile){
    int status = 0;
    char buf1[1000];
    char buf2[1000];
    
    snprintf(buf1, sizeof buf1, "petshop/%s", namaFile);
    snprintf(buf2, sizeof buf2, "petshop/%s/%s.jpg", namaFolder, nama);
    
    if(fork()==0){
        char *argv[] = {"cp", buf1, buf2, NULL};
        execv("/bin/cp", argv);
    }
    while(wait(&status)>0);
}
```
Ini merupakan fungsi untuk meng-copy file. Jadi di sini ada 2 buah `snprintf`, dimana yang pertama untuk mengeprint nama file awal dan lokasinya ke buf1, dan yang kedua untuk mengeprint nama file baru dan lokasi barunya yang sesuai dengan foldernya ke buf2. Lalu dilakuka `exec` untuk mengcopy dari bu1 ke buf2.
```c
void deleteFiles(char *namaFiles){
    if(fork()==0){
        chdir("/home/sabrina/modul2/petshop");
        char *argv[] = {"rm", namaFiles, NULL};
        execv("/bin/rm", argv);
    }
}
```
Setelah dicopy, lalu file semula akan di delete menggunakan fungsi `deleteFiles` ini. Jadi program akan menuju ke directory, yaitu folder `petshop`, lalu melakukan exec untuk mengahpus setiap file di situ.

###2e
Pada soal 2e, kita diminta untuk membuat file `keterangan.txt` yang berisikan nama dan umur dari setiap peliharaan yang ada di folder tersebut.
```c
void createKeterangan(char *folder, char *namaHewan, char *umurHewan){
    char *umur;
    int status = 0;
    
    umur = umurHewan;
    
    char buf1[10000];
    snprintf(buf1, sizeof buf1, "petshop/%s/keterangan.txt", folder);
   
    FILE *keterangan;
    keterangan = fopen(buf1, "a+");
    fprintf(keterangan, "nama : %s", namaHewan);
    fprintf(keterangan, "\n");
    fprintf(keterangan, "umur : %s tahun", umur);
    fprintf(keterangan, "\n\n");
    fclose(keterangan);    
}
```
Jadi di sini dibuat fungsi `createKeterangan`, dimana dilakukan `snprintf` untuk mengeprint nama file, yaitu `keterangan.txt` beserta lokasinya, yaitu di folder yang sesuaike buf1. Lalu dilakukan `fopen` untuk membuka file buf1, dimana jika file tersebut belum ada maka akan terbuat secara otomatis. Lalu dilakukan `fprintf` untuk mengeprint nama dan umur setiap hewan di folder tersebut. 

### Hasil Run
Berikut merupakan hasil runnya. Dimana di dalam folder `petshop` terdapat folder-folder sesuai dengan jenis hewannya.
![image](https://user-images.githubusercontent.com/83162422/115994093-cbd66100-a5ff-11eb-86f7-c5aa187d9051.png)

Dan di sini, di tiap folder berisikan file-file sesuai dengan jenisnya dan juga file `keterangan.txt`.
![image](https://user-images.githubusercontent.com/83162422/115994168-0b9d4880-a600-11eb-8b8d-65dced56ad2f.png)

### Kendala
Selama mengerjakan soal ini, kendala yang dialami ialah error dikarenakan program tidak diberi kondisi while `((wait(&status)) > 0)`. Selain itu kendala juga didapati ketika saat mengerjakan nomor 2c kami membuat fungsi seperti fungsi `listFilesRecursively` lagi, dan program malah menjadi membingungkan karena harus mengecek file sebanyak dua kali, sehingga diganti menjadi seperti yang sekarang.

## Soal 3

#### Caesar Cipher (C)
```c
// fungsi algoritma enkripsi caesar cipher yg dipakai di 3C
char caesarcipher(char *msg, int shift)
{
    int i;
    char word;
    for (int i = 0; msg[i] != '\0'; ++i) // membaca tiap huruf di kalimatnya
    {
        word = msg[i]; // pindah huruf ke "word"
        if (word >= 'A' && word <= 'Z') // untuk huruf Uppercase
        {
            word = word + shift; // huruf saat ini dishift
            if (word > 'Z') // jika saat shift melebihi Z
            {
                word = word - 'Z' + 'A' - 1; // shift ke awal (misal Y dishift 5 jadi D)
            }
            msg[i] = word; // setelah word dishift, dikembalikan ke kalimat awal
        }
        else if (word >= 'a' && word <= 'z') // untuk huruf lowercase
        {
            word = word + shift; // huruf saat ini dishift
            if (word > 'z') // jika saat shift melebihi z
            {
                word = word - 'z' + 'a' - 1; // shift ke awal (misal z dishift 5 jadi e)
            }
            msg[i] = word; // setelah word dishift, dikembalikan ke kalimat awal
        }
    }
}
```

#### Main

```c

    if (argc != 2)
    {
        exit(EXIT_FAILURE);
    }

    // mulai membuat daemon
    pid_t pid, sid; // Variabel untuk menyimpan PID

    pid = fork(); // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
	* (nilai variabel pid < 0) */
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
	* (nilai variabel pid adalah PID dari child process) */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    // selesai membuat daemon

    // 3E. Membuat mode Killer menggunakan bash
    char killername[100];
    strcpy(killername, "/home/cliffton/Documents/Modul/Modul 2/killer.sh"); // killername = /home/cliffton/Documents/Modul/Modul 2/killer.sh
    FILE *killer = fopen(killername, "w"); // buat file dan buka killer.sh di /home/cliffton/Documents/Modul/Modul 2/ (sesuai killername)(w = create empty file)

    if (strcmp(argv[1], "-z") == 0)
    { // jika ada argumen -z maka akan kill semua proses
        fprintf(killer, "#!/bin/bash\nkillall -9 soal3\nrm %s", killername);
    }
    else if (strcmp(argv[1], "-x") == 0)
    { // jika ada argumen -x maka akan kill program utama tapi proses lain masih berjalan
        fprintf(killer, "#!/bin/bash\nkill %d\nrm %s", getpid(), killername);
    }
    else
    { // jika tidak ada argumen, tutup killer
        fclose(killer);
        exit(EXIT_FAILURE);
    }

    pid_t pidk = fork(); // difork. child process menjalankan chmod
    if (pidk == 0) // child process
    {
        char *arg[] = {"chmod", "x", killername, NULL}; // chmod x agar file menjadi executable
        execv("/bin/chmod", arg);
    }
    fclose(killer); // tutup killer

    char pesan[120] = "Download Success"; // pesan yg nanti bakal dienkripsi dan masuk ke status.txt

    // masuk program utama
    while (1)
    {
        char foldername[100] = "/home/cliffton/Documents/Modul/Modul 2/"; // direktori utama
        char strtime[100];
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(strtime, sizeof(foldername), "%Y-%m-%d_%H:%M:%S", tm); // string timestamp sesuai format di soal (dipakai di 3A)
        strcat(foldername, strtime); // foldername = foldername awal + timestamp (dipakai di 3A)

        // inisialisasi fork
        pid_t pid1 = fork();
        int status1;
        if (pid1 == 0) // child process
        {
            // fork lagi
            pid_t pid2 = fork();
            int status2;
            if (pid2 == 0) // child process
            {   
                // 3A. membuat direktori file sesuai dengan 'foldername' tadi
                char *arg1[] = {"mkdir", foldername, NULL};
                execv("/bin/mkdir", arg1);
            }
            
            else // main process
            { // 3B. Mendownload 10 gambar
                while ((wait(&status2)) > 0); // menunggu child process selesai
                for (int i = 0; i < 10; i++)
                {
                    // fork lagi
                    pid_t pid3 = fork();
                    if (pid3 == 0) // child process
                    {
                        time_t t = time(NULL); // detik epoch unix
                        struct tm *tp = localtime(&t);

                        char filename[100];
                        strcpy(filename, foldername); // copy foldername yg tadi ke filename
                        strcat(filename, "/"); // filename = filename + /

                        char timefilename[100];
                        strftime(timefilename, sizeof(timefilename), "%Y-%m-%d_%H:%M:%S", tp); // format timestamp untuk nama file
                        strcat(filename, timefilename); // filename = filename + format timestamp

                        char link[100];
                        sprintf(link, "https://picsum.photos/%d", (((int)t) % 1000) + 50); // ukuran = ((detik epoch unix modulo 1000) + 50) pixel persegi

                        char *arg2[] = {"wget", "-qO", filename, link, NULL}; // download link di atas
                        execv("/usr/bin/wget", arg2);
                    }
                    sleep(5); // jalankan setiap 5 detik
                }

                //3C. Membuat file status.txt
                char status[120];
                sprintf(status, "%s/status.txt", foldername); // status = foldername/status.txt
                caesarcipher(pesan, 5); // enkripsi pesan (Download Success) dengan caesar cipher shift 5
                FILE *download = fopen(status, "w"); // buat file status
                fprintf(download, "%s", pesan); // print pesan yg sudah dienkripsi tadi
                fclose(download); // tutup file
                //3C. Melakukan zip file
                // fork
                pid_t pid4 = fork();
                int status4;
                if (pid4 == 0) // child process
                {
                    char zipname[120];
                    strcpy(zipname, foldername); // copy 'foldername' ke zipname
                    strcat(zipname, ".zip"); // zipname = 'zipname'.zip
                    char *arg3[] = {"zip", "-j", "-r", "-m", zipname, foldername, NULL}; // buat zip dengan nama 'zipname' yg berisi 'foldername'
                    // -j = junk path. karena char zipname ada direktori, maka harus diabaikan menggunakan -j dan menyisakan nama filenya saja
                    // -r = recursive. semua file termasuk di subfolders masuk di zip
                    // -m = move. hapus file yg dizip setelah zip selesai
                    execv("/usr/bin/zip", arg3);
                }
                // Menghapus folder
                else // main process
                {
                    while ((wait(&status4)) > 0);
                    char *arg4[] = {"rm", "-d", foldername, NULL}; // hapus folder 'foldername'
                    execv("/bin/rm", arg4);
                }
            }
        }
        sleep(40); // jalankan setiap 40 detik (soal 3A)
    }
}
```
#### D & E

```c
// 3 D & E. Membuat mode Killer menggunakan bash
    char killername[100];
    strcpy(killername, "/home/cliffton/Documents/Modul/Modul 2/killer.sh"); // killername = /home/cliffton/Documents/Modul/Modul 2/killer.sh
    FILE *killer = fopen(killername, "w"); // buat file dan buka killer.sh di /home/cliffton/Documents/Modul/Modul 2/ (sesuai killername)(w = create empty file)

    if (strcmp(argv[1], "-z") == 0)
    { // jika ada argumen -z maka akan kill semua proses
        fprintf(killer, "#!/bin/bash\nkillall -9 soal3\nrm %s", killername);
    }
    else if (strcmp(argv[1], "-x") == 0)
    { // jika ada argumen -x maka akan kill program utama tapi proses lain masih berjalan
        fprintf(killer, "#!/bin/bash\nkill %d\nrm %s", getpid(), killername);
    }
    else
    { // jika tidak ada argumen, tutup killer
        fclose(killer);
        exit(EXIT_FAILURE);
    }

    pid_t pidk = fork(); // difork. child process menjalankan chmod
    if (pidk == 0) // child process
    {
        char *arg[] = {"chmod", "x", killername, NULL}; // chmod x agar file menjadi executable
        execv("/bin/chmod", arg);
    }
    fclose(killer); // tutup killer
```

#### A

```c
char foldername[100] = "/home/cliffton/Documents/Modul/Modul 2/"; // direktori utama
        char strtime[100];
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(strtime, sizeof(foldername), "%Y-%m-%d_%H:%M:%S", tm); // string timestamp sesuai format di soal (dipakai di 3A)
        strcat(foldername, strtime); // foldername = foldername awal + timestamp (dipakai di 3A)

        // inisialisasi fork
        pid_t pid1 = fork();
        int status1;
        if (pid1 == 0) // child process
        {
            // fork lagi
            pid_t pid2 = fork();
            int status2;
            if (pid2 == 0) // child process
            {   
                // 3A. membuat direktori file sesuai dengan 'foldername' tadi
                char *arg1[] = {"mkdir", foldername, NULL};
                execv("/bin/mkdir", arg1);
            }
```

#### B

```c
else // main process
            { // 3B. Mendownload 10 gambar
                while ((wait(&status2)) > 0); // menunggu child process selesai
                for (int i = 0; i < 10; i++)
                {
                    // fork lagi
                    pid_t pid3 = fork();
                    if (pid3 == 0) // child process
                    {
                        time_t t = time(NULL); // detik epoch unix
                        struct tm *tp = localtime(&t);

                        char filename[100];
                        strcpy(filename, foldername); // copy foldername yg tadi ke filename
                        strcat(filename, "/"); // filename = filename + /

                        char timefilename[100];
                        strftime(timefilename, sizeof(timefilename), "%Y-%m-%d_%H:%M:%S", tp); // format timestamp untuk nama file
                        strcat(filename, timefilename); // filename = filename + format timestamp

                        char link[100];
                        sprintf(link, "https://picsum.photos/%d", (((int)t) % 1000) + 50); // ukuran = ((detik epoch unix modulo 1000) + 50) pixel persegi

                        char *arg2[] = {"wget", "-qO", filename, link, NULL}; // download link di atas
                        execv("/usr/bin/wget", arg2);
                    }
                    sleep(5); // jalankan setiap 5 detik
                }
```

#### C

```c
 //3C. Membuat file status.txt
                char status[120];
                sprintf(status, "%s/status.txt", foldername); // status = foldername/status.txt
                caesarcipher(pesan, 5); // enkripsi pesan (Download Success) dengan caesar cipher shift 5
                FILE *download = fopen(status, "w"); // buat file status
                fprintf(download, "%s", pesan); // print pesan yg sudah dienkripsi tadi
                fclose(download); // tutup file
                //3C. Melakukan zip file
                // fork
                pid_t pid4 = fork();
                int status4;
                if (pid4 == 0) // child process
                {
                    char zipname[120];
                    strcpy(zipname, foldername); // copy 'foldername' ke zipname
                    strcat(zipname, ".zip"); // zipname = 'zipname'.zip
                    char *arg3[] = {"zip", "-j", "-r", "-m", zipname, foldername, NULL}; // buat zip dengan nama 'zipname' yg berisi 'foldername'
                    // -j = junk path. karena char zipname ada direktori, maka harus diabaikan menggunakan -j dan menyisakan nama filenya saja
                    // -r = recursive. semua file termasuk di subfolders masuk di zip
                    // -m = move. hapus file yg dizip setelah zip selesai
                    execv("/usr/bin/zip", arg3);
                }
                // Menghapus folder
                else // main process
                {
                    while ((wait(&status4)) > 0);
                    char *arg4[] = {"rm", "-d", foldername, NULL}; // hapus folder 'foldername'
                    execv("/bin/rm", arg4);
                }
```

<p>Program dijalankan</p>

![3](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots3/Screenshot%20from%202021-04-25%2016-55-37.png)

<p>Isi file zip</p>

![3](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots3/Screenshot%20from%202021-04-25%2016-55-48.png)

<p>killer.sh saat argument -z. Semua proses di direktori berhenti.</p>

![3](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots3/Screenshot%20from%202021-04-25%2016-56-38.png)

<p>killer.sh saat argument -x. Program utama berhenti tapi semua proses tetap berjalan sampai selesai.</p>

![3](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots3/Screenshot%20from%202021-04-25%2016-58-46.png)

![3](https://raw.githubusercontent.com/feilvan/sisop-general/main/modul2/screenshots3/Screenshot%20from%202021-04-25%2016-59-18.png)
