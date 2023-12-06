#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    float saldo;
};

struct User users[MAX_USERS];
int userCount = 0;
struct User *currentUser = NULL;

//Untuk menyimpan data pengguna ke dalam file
void saveUsersToFile() {
    FILE *file = fopen("datauser.txt", "w");
    if (file == NULL) {
        printf("Error: Gagal membuka file untuk penyimpanan data pengguna.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s\t\t%s\t\t%.2f\n", users[i].username, users[i].password, users[i].saldo);
    }

    fclose(file);
}

// Fungsi untuk memuat data pengguna dari file
void loadUsersFromFile() {
    FILE *file = fopen("datauser.txt", "r");
    if (file == NULL) {
        printf("File data pengguna tidak ditemukan. Membuat file baru.\n");
        return;
    }

    while (fscanf(file, "%s %s %f", users[userCount].username, users[userCount].password, &users[userCount].saldo) == 3) {
        userCount++;
        if (userCount >= MAX_USERS) {
            break;
        }
    }

    fclose(file);
}

// Fungsi untuk mendaftarkan pengguna baru
void registerUser() {
    if (userCount < MAX_USERS) {
        printf("Masukkan username: ");
        scanf("%s", users[userCount].username);

        printf("Masukkan password: ");
        scanf("%s", users[userCount].password);

        users[userCount].saldo = 0;

        userCount++;

        printf("Pendaftaran berhasil!\n");

        saveUsersToFile();
    } else {
        printf("Batas maksimal pengguna telah tercapai.\n");
    }
}

// Fungsi untuk melakukan login
void loginUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Masukkan username: ");
    scanf("%s", username);

    printf("Masukkan password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            currentUser = &users[i];
            printf("Login berhasil! Selamat datang, %s.\n", currentUser->username);
            return;
        }
    }

    printf("Login gagal. Periksa kembali username dan password.\n");
}

// Fungsi untuk melakukan penarikan tunai
void tarikTunai(float jumlah) {
    if (jumlah > 0 && currentUser != NULL && currentUser->saldo >= jumlah) {
        currentUser->saldo -= jumlah;
        printf("Penarikan tunai berhasil. Saldo sekarang: %.2f\n", currentUser->saldo);
        saveUsersToFile();
    } else {
        printf("Penarikan tunai gagal. Saldo tidak mencukupi atau jumlah tidak valid.\n");
    }
}

// Fungsi untuk melakukan penyetoran tunai
void setorTunai(float jumlah) {
    if (jumlah > 0 && currentUser != NULL) {
        currentUser->saldo += jumlah;
        printf("Setoran tunai berhasil. Saldo sekarang: %.2f\n", currentUser->saldo);
        saveUsersToFile();
    } else {
        printf("Silahkan Login Terlebih dahulu.\n");
    }
}

// Fungsi untuk menampilkan saldo
void cekSaldo() {
    if (currentUser != NULL) {
        printf("Saldo Anda, %s: %.2f\n", currentUser->username, currentUser->saldo);
    } else {
        printf("Silahkan login terlebih dahulu.\n");
    }
}

void transfer(float jumlah, const char *tujuan) {
    if (currentUser == NULL) {
        printf("Silahkan login terlebih dahulu.\n");
        return;
    }

    if (jumlah > 0 && currentUser->saldo >= jumlah) {
        // Cari penerima transfer berdasarkan username
        struct User *penerima = NULL;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(tujuan, users[i].username) == 0) {
                penerima = &users[i];
                break;
            }
        }

        if (penerima != NULL) {
            // Lakukan transfer
            currentUser->saldo -= jumlah;
            penerima->saldo += jumlah;
            printf("Transfer berhasil ke %s. Saldo Anda sekarang: %.2f\n", penerima->username, currentUser->saldo);
            saveUsersToFile();
        } else {
            printf("Penerima transfer dengan username %s tidak ditemukan.\n", tujuan);
        }
    } else {
        printf("Transfer gagal. Saldo tidak mencukupi atau jumlah tidak valid.\n");
    }
}


int main() {

    loadUsersFromFile();
    int pilihan;
    float jumlah;

    do {
        // Tampilkan menu sesuai dengan status login
        if (currentUser == NULL) {
            // Tampilan untuk pengguna belum login
            printf("==========================================================\n");
            printf("#\t\tSelamat datang di Mini Bank\t\t#\n");
            printf("==========================================================\n");
            printf("#\t\t\t1. Daftar\t\t\t#\n");
            printf("#\t\t\t2. Login\t\t\t#\n");
            printf("#\t\t\t3. Keluar\t\t\t#\n");
            printf("==========================================================\n");
        } else {
            // Tampilan untuk pengguna yang sudah login
            printf("==========================================================\n");
            printf("#\t\tLayanan di Mini Bank\t\t\t#\n");
            printf("==========================================================\n");
            printf("#\t\t 1. Tarik Tunai\t\t\t\t#\n");
            printf("#\t\t 2. Setor Tunai\t\t\t\t#\n");
            printf("#\t\t 3. Cek Saldo\t\t\t\t#\n");
            printf("#\t\t 4. Transfer\t\t\t\t#\n");
            printf("#\t\t 5. Kembali ke menu login\t\t#\n");
            printf("#\t\t 6. Keluar\t\t\t\t#\n");
            printf("==========================================================\n");
        }

        // Pilihan menu
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                // Daftar atau tarik tunai tergantung pada status login
                if (currentUser == NULL) {
                    registerUser();
                } else {
                    // Tarik Tunai
                    printf("Masukkan jumlah penarikan: ");
                    scanf("%f", &jumlah);
                    tarikTunai(jumlah);
                }
                break;
            case 2:
                // Login atau setor tunai tergantung pada status login
                if (currentUser == NULL) {
                    loginUser();
                } else {
                    // Setor Tunai
                    printf("Masukkan jumlah setoran: ");
                    scanf("%f", &jumlah);
                    setorTunai(jumlah);
                }
                break;
            case 3:
                // Cek Saldo atau keluar tergantung pada status login
                if (currentUser == NULL) {
                    // Keluar dari program
                    printf("Keluar dari program.\n");
                    return 0;
                } else {
                    // Cek Saldo
                    cekSaldo();
                }
                break;
            case 4:
                //Transfer
                if (currentUser != NULL) {
                    char tujuan[MAX_USERNAME_LENGTH];
                    printf("Masukkan username penerima transfer: ");
                    scanf("%s", tujuan);

                    printf("Masukkan Jumlah Transfer: ");
                    scanf("%f", &jumlah);

                    transfer(jumlah, tujuan);
                } else {
                    printf("Silahkan login dahulu\n");
                }
                break;
            case 5:
                //Kembali ke menu login
                currentUser = NULL;
                printf("Kembali ke menu login\n");
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak ada.\n");
        }
    } while (pilihan != 6);

    return 0;
}
