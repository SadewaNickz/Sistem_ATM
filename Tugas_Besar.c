#include <stdio.h>
#include <string.h>
hgghgh
#define MAX_USERS 100
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
    } else {
        printf("Penarikan tunai gagal. Saldo tidak mencukupi atau jumlah tidak valid.\n");
    }
}

// Fungsi untuk melakukan penyetoran tunai
void setorTunai(float jumlah) {
    if (jumlah > 0 && currentUser != NULL) {
        currentUser->saldo += jumlah;
        printf("Setoran tunai berhasil. Saldo sekarang: %.2f\n", currentUser->saldo);
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

int main() {
    int pilihan;
    float jumlah;

    do {
        // Tampilkan menu
        printf("\n1. Daftar\n");
        printf("2. Login\n");
        printf("3. Tarik Tunai\n");
        printf("4. Setor Tunai\n");
        printf("5. Cek Saldo\n");
        printf("6. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                // Daftar user
                registerUser();
                break;
            case 2:
                // Login
                loginUser();
                break;
            case 3:
                // Tarik Tunai
                printf("Masukkan jumlah penarikan: ");
                scanf("%f", &jumlah);
                tarikTunai(jumlah);
                break;
            case 4:
                // Setor Tunai
                printf("Masukkan jumlah setoran: ");
                scanf("%f", &jumlah);
                setorTunai(jumlah);
                break;
            case 5:
                // Cek Saldo
                cekSaldo();
                break;
            case 6:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);

    return 0;
}
